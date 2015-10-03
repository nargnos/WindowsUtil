#include "PeDecoder.h"
namespace PE
{
	
	PIMAGE_NT_HEADERS32 PeDecoder::NtHeader32()
	{
		return (PIMAGE_NT_HEADERS32)ntHeader;
	}
	PIMAGE_NT_HEADERS64 PeDecoder::NtHeader64()
	{
		return (PIMAGE_NT_HEADERS64)ntHeader;
	}
	bool PeDecoder::IsMapped()
	{
		return isMapped;
	}
	PIMAGE_DOS_HEADER PeDecoder::DosHeader()
	{
		return dosHeader;
	}
	bool PeDecoder::HasNtHeader32()
	{
		return hasNtHeader32;
	}
	PIMAGE_SECTION_HEADER PeDecoder::RvaToSection(DWORD rva)
	{
		auto section = firstSectionHeader;
		while (section < lastSectionHeader)
		{
			if (rva < section->VirtualAddress + 
				ALIGN_UP((UINT)(section->Misc.VirtualSize), (UINT)(*sectionAlignment)))
			{
				return rva < section->VirtualAddress? NULL: section;
			}
			section++;
		}
		return NULL;
	}
	PIMAGE_SECTION_HEADER PeDecoder::OffsetToSection(DWORD fileOffset)
	{
		auto section = firstSectionHeader;
		while (section < lastSectionHeader)
		{
			if (fileOffset < section->PointerToRawData + section->SizeOfRawData)
			{
				return fileOffset < section->PointerToRawData ? NULL : section;
			}
			section++;
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
		return rva - (section->VirtualAddress) + (section->PointerToRawData);
	}

	DWORD PeDecoder::OffsetToRva(DWORD fileOffset)
	{
		if (fileOffset)
		{
			IMAGE_SECTION_HEADER *section = OffsetToSection(fileOffset);
			if (section != NULL)
			{
				return fileOffset - (section->PointerToRawData) + (section->VirtualAddress);
			}
		}
		return 0;
	}
	PVOID PeDecoder::DirectoryEntryToData(DWORD index, PDWORD* size)
	{
		auto dir = GetDataDirectory(index);
		if (!dir)
		{
			return NULL;
		}
		if (size)
		{
			*size = &dir->Size;
		}
		return GetRvaData(dir->VirtualAddress);
	}
	PIMAGE_EXPORT_DIRECTORY PeDecoder::GetImageExport(PDWORD* size)
	{
		return (PIMAGE_EXPORT_DIRECTORY)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_EXPORT, size);
	}

	PIMAGE_IMPORT_DESCRIPTOR PeDecoder::GetImageImport(PDWORD* size)
	{
		return (PIMAGE_IMPORT_DESCRIPTOR)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_IMPORT  , size);
	}
	PIMAGE_RESOURCE_DIRECTORY PeDecoder::GetImageResource(PDWORD* size)
	{
		return (PIMAGE_RESOURCE_DIRECTORY)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_RESOURCE, size);
	}
	PIMAGE_RUNTIME_FUNCTION_ENTRY PeDecoder::ImageException(PDWORD* size)
	{
		return (PIMAGE_RUNTIME_FUNCTION_ENTRY)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_EXCEPTION, size);
	}
	PVOID PeDecoder::ImageSecurity(PDWORD* size)
	{
		if (isMapped)
		{
			return NULL;
		}
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_SECURITY);
		if (!dir)
		{
			return NULL;
		}
		if (size)
		{
			*size = &dir->Size;
		}
		return base + dir->VirtualAddress;
	}
	PIMAGE_BASE_RELOCATION PeDecoder::GetImageBasereloc(PDWORD* size)
	{
		return (PIMAGE_BASE_RELOCATION)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_BASERELOC, size);
	}
	PIMAGE_DEBUG_DIRECTORY PeDecoder::ImageDebug(PDWORD* size)
	{
		return (PIMAGE_DEBUG_DIRECTORY)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_DEBUG, size);
	}
	PIMAGE_ARCHITECTURE_HEADER PeDecoder::ImageArchitecture(PDWORD* size)
	{
		return (PIMAGE_ARCHITECTURE_HEADER)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE, size);
	}
	/*
	? PeDecoder::ImageDirectoryEntryGlobalptr()
	{
	return (PIMAGE_EXPORT_DIRECTORY)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_GLOBALPTR, size);
	}*/

	PIMAGE_TLS_DIRECTORY32 PeDecoder::ImageTls32(PDWORD* size)
	{
		return hasNtHeader32?(PIMAGE_TLS_DIRECTORY32)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_TLS, size): NULL;
	}
	PIMAGE_TLS_DIRECTORY64 PeDecoder::ImageTls64(PDWORD* size)
	{
		return hasNtHeader32? NULL:(PIMAGE_TLS_DIRECTORY64)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_TLS, size);
	}

	PIMAGE_LOAD_CONFIG_DIRECTORY32 PeDecoder::ImageLoadConfig32(PDWORD* size)
	{
		return hasNtHeader32?(PIMAGE_LOAD_CONFIG_DIRECTORY32)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, size): NULL;
	}
	PIMAGE_LOAD_CONFIG_DIRECTORY64 PeDecoder::ImageLoadConfig64(PDWORD* size)
	{
		return hasNtHeader32? NULL:(PIMAGE_LOAD_CONFIG_DIRECTORY64)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, size);
	}

	PIMAGE_BOUND_IMPORT_DESCRIPTOR PeDecoder::ImageBoundImport(PDWORD* size)
	{
		return (PIMAGE_BOUND_IMPORT_DESCRIPTOR)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT, size);
	}
	PVOID PeDecoder::GetImageIat(PDWORD* size)
	{
		return /*(IMAGE_THUNK_DATA32)*/DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_IAT, size);
	}
	
	PImgDelayDescr PeDecoder::ImageDelayImport(PDWORD* size)
	{
		return (PImgDelayDescr)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT, size);
	}
	
	PIMAGE_COR20_HEADER PeDecoder::ImageComDescriptor(PDWORD* size)
	{
		return (PIMAGE_COR20_HEADER)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR, size);
	}
	
	PVOID PeDecoder::GetRvaData(DWORD rva)
	{
		return base + (isMapped? rva: RvaToOffset(rva));
	}
	PIMAGE_DATA_DIRECTORY PeDecoder::GetDataDirectory(DWORD index)
	{
		if (*imageDataDirectorySize > index && IMAGE_NUMBEROF_DIRECTORY_ENTRIES > index)
		{
			auto result = &imageDataDirectoryEntry[index];
			if (result->VirtualAddress != NULL)
			{			
				return result;
			}
		}
		return NULL;
	}

	bool PeDecoder::LoadPEImage(PVOID base, bool isMapped)
	{
		isPE = false;
		if (!base)
		{
			return false;
		}
		// 载入头
		dosHeader = (PIMAGE_DOS_HEADER)base;
		ntHeader = (PIMAGE_NT_HEADERS32)((PBYTE)dosHeader + dosHeader->e_lfanew);

		// 检查pe格式
		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE ||
			ntHeader->Signature != IMAGE_NT_SIGNATURE
			)
		{
			return false;
		}
		
		// 开始读取
		this->base = (PBYTE)base;
		this->isMapped = isMapped;

		//  32 64位共用一些字段, 所以可以用NtHeader32
		imageType = &(NtHeader32()->OptionalHeader.Magic);

		// 检查映像类型
		switch (*imageType)
		{
		case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
		{
			auto header32 = NtHeader32();
			imageDataDirectoryEntry = header32->OptionalHeader.DataDirectory;
			imageDataDirectorySize = &header32->OptionalHeader.NumberOfRvaAndSizes;
			sectionAlignment = &header32->OptionalHeader.SectionAlignment;
			firstSectionHeader = IMAGE_FIRST_SECTION(header32);
			sectionCount = &header32->FileHeader.NumberOfSections;
			hasNtHeader32 = true;
		}
		break;
		case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
		{
			auto header64 = NtHeader64();
			imageDataDirectoryEntry = header64->OptionalHeader.DataDirectory;
			imageDataDirectorySize = &header64->OptionalHeader.NumberOfRvaAndSizes;
			sectionAlignment = &header64->OptionalHeader.SectionAlignment;
			firstSectionHeader = IMAGE_FIRST_SECTION(header64);
			sectionCount = &header64->FileHeader.NumberOfSections;
			hasNtHeader32 = false;
		}
		break;
		default:
			// 第三种没见过, 定义里没节和数据目录, 不做解析
			return false;
		}
		lastSectionHeader = firstSectionHeader + *sectionCount;
		isPE = true;
		return true;
	}

}