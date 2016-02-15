#include "Common\Common.h"
namespace PE
{
#define ALIGN_UP(value, alignment) ((UINT)(value + alignment - 1)&~(alignment - 1))

	// 判断文件是否映射（值由外部传入）
	bool PeDecoder::IsMapped() const
	{
		return isMapped;
	}

	// 附加到指针
	bool PeDecoder::Attach(PVOID base, bool isMapped)
	{
		if (base == NULL)
		{
			return false;
		}
		if (base == this->base)
		{
			return true;
		}
		
		// 初始化数据
		isPE = false;
		Clear();
		isAttached = true;

		this->base = (PBYTE)(base);
		this->isMapped = isMapped;
		// 绑定结构
		BindPtr();

		// 检查pe格式
		if (!GetDosHeader->VerifyDosSignature() || !GetNtHeader->VerifyNtSignature())
		{
			return false;
		}
		// 初始化nt头
		if (!GetNtHeader->Init())
		{
			return false;
		}
		this->hasNtHeader32 = GetNtHeader->HasNtHeader32();
		isPE = true;
		return true;
	}

	// 脱离，重置成员
	void PeDecoder::Dettach()
	{
		base = NULL;
		Clear();
		isAttached = false;
	}

	// 将延迟初始化结构绑定到自身
	void PeDecoder::BindPtr()
	{
		if (!isBinded)
		{
			isBinded = true;
			GetDosHeader.Bind(this);
			GetNtHeader.Bind(this);
			GetSection.Bind(this);
			GetReloc.Bind(this);
			GetExport.Bind(this);
			GetImport.Bind(this);
			GetResource.Bind(this);
			GetException.Bind(this);
			GetSecurity.Bind(this);
			GetDebug.Bind(this);
			GetArchitecture.Bind(this);
			GetGlobalptr.Bind(this);
			GetTls.Bind(this);
			GetLoadConfig.Bind(this);
			GetBoundImport.Bind(this);
			GetIat.Bind(this);
			GetDelayImport.Bind(this);
			GetComDescriptor.Bind(this);
		}
	}

	// 取基址
	PVOID PeDecoder::GetBase()
	{
		return this->base;
	}
	PeDecoder::PeDecoder()
	{
		isBinded = false;
		isAttached = false;
		Clear();
	}
	// 重置
	void PeDecoder::Clear()
	{
		GetDosHeader.Reset();
		GetNtHeader.Reset();
		GetSection.Reset();
		GetReloc.Reset();
		GetExport.Reset();
		GetImport.Reset();
		GetResource.Reset();
		GetException.Reset();
		GetSecurity.Reset();
		GetDebug.Reset();
		GetArchitecture.Reset();
		GetGlobalptr.Reset();
		GetTls.Reset();
		GetLoadConfig.Reset();
		GetBoundImport.Reset();
		GetIat.Reset();
		GetDelayImport.Reset();
		GetComDescriptor.Reset();
	}
	// 判断是否为32位程序，忽略了一种情况
	bool PeDecoder::HasNtHeader32() const
	{
		return hasNtHeader32;
	}
	// 判断是否是PE文件
	bool PeDecoder::IsPE() const
	{
		return isPE;
	}
	// 判断是否附加成功
	bool PeDecoder::IsAttached() const
	{
		return isAttached;
	}
	// 相对偏移找节地址
	PIMAGE_SECTION_HEADER PeDecoder::RvaToSection(DWORD rva)
	{
		auto currentSection = GetSection->firstSectionHeader;
		while (currentSection < GetSection->lastSectionHeader)
		{
			if (rva < currentSection->VirtualAddress +
				ALIGN_UP((UINT)(currentSection->Misc.VirtualSize), (UINT)(*GetSection->sectionAlignment)))
			{
				return rva < currentSection->VirtualAddress ? NULL : currentSection;
			}
			currentSection++;
		}
		return NULL;
	}
	// 文件偏移找节地址
	PIMAGE_SECTION_HEADER PeDecoder::OffsetToSection(DWORD fileOffset)
	{
		auto currentSection = GetSection->firstSectionHeader;
		while (currentSection < GetSection->lastSectionHeader)
		{
			if (fileOffset < currentSection->PointerToRawData + currentSection->SizeOfRawData)
			{
				return fileOffset < currentSection->PointerToRawData ? NULL : currentSection;
			}
			currentSection++;
		}
		return NULL;
	}
	// 相对偏移转成文件偏移
	DWORD PeDecoder::RvaToOffset(DWORD rva)
	{
		if (!rva)
		{
			return 0;
		}
		IMAGE_SECTION_HEADER *section = RvaToSection(rva);
		if (section == NULL)
		{
			return rva;
		}
		return rva - section->VirtualAddress + section->PointerToRawData;
	}
	// 文件偏移转成相对偏移
	DWORD PeDecoder::OffsetToRva(DWORD fileOffset)
	{
		if (fileOffset)
		{
			IMAGE_SECTION_HEADER *section = OffsetToSection(fileOffset);
			if (section != NULL)
			{
				return fileOffset - section->PointerToRawData + section->VirtualAddress;
			}
		}
		return 0;
	}
	// 取得相对偏移指向的数据
	PVOID PeDecoder::GetRvaData(DWORD rva)
	{
		return base + (isMapped ? rva : RvaToOffset(rva));
	}
	

	// 通过ID获取DataDirectoryEntry地址，失败返回NULL
	PIMAGE_DATA_DIRECTORY PeDecoder::GetDataDirectory(DWORD index)
	{
		if (*GetNtHeader->imageDataDirectorySize > index && IMAGE_NUMBEROF_DIRECTORY_ENTRIES > index)
		{
			return &GetNtHeader->imageDataDirectoryEntry[index];
		}
		return NULL;
	}
	// 取得DataDirectoryEntry指向的数据地址
	PVOID PeDecoder::DirectoryEntryToData(DWORD index, PDWORD* size)
	{
		auto dir = GetDataDirectory(index);
		if (!dir || dir->VirtualAddress == NULL)
		{
			return NULL;
		}
		if (size)
		{
			*size = &dir->Size;
		}
		return GetRvaData(dir->VirtualAddress);
	}
}  // namespace PE
