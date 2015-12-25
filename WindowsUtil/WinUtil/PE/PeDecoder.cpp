#include "Common\Common.h"
namespace PE
{
#define ALIGN_UP(value, alignment) ((UINT)(value + alignment - 1)&~(alignment - 1))

	bool PeDecoder::IsMapped()
	{
		return isMapped;
	}
	bool PeDecoder::LoadPEImage(PVOID base, bool isMapped)
	{
		if (base == this->base)
		{
			return true;
		}
		isPE = false;
		Clear();
		if (!base)
		{
			return false;
		}

		this->base = reinterpret_cast<PBYTE>(base);
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
	PVOID PeDecoder::GetBase()
	{
		return this->base;
	}
	PeDecoder::PeDecoder()
	{
		isBinded = false;
		Clear();
	}
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

	bool PeDecoder::HasNtHeader32()
	{
		return hasNtHeader32;
	}
	bool PeDecoder::IsPE()
	{
		return isPE;
	}

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
	PVOID PeDecoder::GetRvaData(DWORD rva)
	{
		return base + (isMapped ? rva : RvaToOffset(rva));
	}




	PIMAGE_DATA_DIRECTORY PeDecoder::GetDataDirectory(DWORD index)
	{
		if (*GetNtHeader->imageDataDirectorySize > index && IMAGE_NUMBEROF_DIRECTORY_ENTRIES > index)
		{
			return &GetNtHeader->imageDataDirectoryEntry[index];
		}
		return NULL;
	}

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
}