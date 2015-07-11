#include "PeDecoder.h"
namespace PE
{
	PeDecoder::PeDecoder(PVOID pe, bool isMapped) :
		base((PUINT8)pe),
		isMapped(isMapped)
	{
		assert(pe);
		CheckImage();
	}

	bool PeDecoder::HasNtHeader32()
	{
		return (*imageType == IMAGE_NT_OPTIONAL_HDR32_MAGIC);
	}
	bool PeDecoder::IsPE()
	{
		return isPE;
	}
	bool PeDecoder::IsMapped()
	{
		return isMapped;
	}
	PVOID PeDecoder::GetBase()
	{
		return base;
	}
	PIMAGE_DOS_HEADER PeDecoder::DosHeader()
	{
		return (PIMAGE_DOS_HEADER)base;
	}

	PIMAGE_NT_HEADERS32 PeDecoder::NtHeader32()
	{
		if (*imageType != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
		{
			return NULL;
		}
		return (PIMAGE_NT_HEADERS32)NtHeader();
	}
	PIMAGE_NT_HEADERS64 PeDecoder::NtHeader64()
	{
		if (*imageType != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
		{
			return NULL;
		}
		return (PIMAGE_NT_HEADERS64)NtHeader();
	}
	PIMAGE_ROM_HEADERS PeDecoder::RomHeader()
	{
		if (*imageType == IMAGE_ROM_OPTIONAL_HDR_MAGIC)
		{
			return (PIMAGE_ROM_HEADERS)NtHeader();
		}
		return NULL;
	}
	PIMAGE_SECTION_HEADER PeDecoder::RvaToSection(DWORD rva)
	{
		auto section = firstSectionHeader;
		while (section < lastSectionHeader)
		{
			if (rva < section->VirtualAddress + AlignUp((UINT)(section->Misc.VirtualSize), (UINT)(*sectionAlignment)))
			{
				if (rva < (section->VirtualAddress))
				{
					return NULL;
				}
				else
				{
					return section;
				}
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
				if (fileOffset < section->PointerToRawData)
				{
					return NULL;
				}
				else
				{
					return section;
				}
			}
			section++;
		}

		return NULL;
	}
	DWORD PeDecoder::RvaToOffset(DWORD rva)
	{
		if (rva > 0)
		{
			IMAGE_SECTION_HEADER *section = RvaToSection(rva);
			if (section == NULL)
			{
				return rva;
			}

			return rva - (section->VirtualAddress) + (section->PointerToRawData);
		}
		return 0;
	}

	DWORD PeDecoder::OffsetToRva(DWORD fileOffset)
	{
		if (fileOffset > 0)
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
		return (base + dir->VirtualAddress);
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
		if (!HasNtHeader32())
		{
			return NULL;
		}
		return (PIMAGE_TLS_DIRECTORY32)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_TLS, size);
	}
	PIMAGE_TLS_DIRECTORY64 PeDecoder::ImageTls64(PDWORD* size)
	{
		if (HasNtHeader32())
		{
			return NULL;
		}
		return (PIMAGE_TLS_DIRECTORY64)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_TLS, size);
	}

	PIMAGE_LOAD_CONFIG_DIRECTORY32 PeDecoder::ImageLoadConfig32(PDWORD* size)
	{
		if (!HasNtHeader32())
		{
			return NULL;
		}
		return (PIMAGE_LOAD_CONFIG_DIRECTORY32)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, size);
	}
	PIMAGE_LOAD_CONFIG_DIRECTORY64 PeDecoder::ImageLoadConfig64(PDWORD* size)
	{
		if (HasNtHeader32())
		{
			return NULL;
		}
		return (PIMAGE_LOAD_CONFIG_DIRECTORY64)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, size);
	}

	PIMAGE_BOUND_IMPORT_DESCRIPTOR PeDecoder::ImageBoundImport(PDWORD* size)
	{
		return (PIMAGE_BOUND_IMPORT_DESCRIPTOR)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT, size);
	}
	PVOID PeDecoder::ImageIat(PDWORD* size)
	{
		return /*(IMAGE_THUNK_DATA32)*/DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_IAT, size);
	}
	
	PIMAGE_DELAYLOAD_DESCRIPTOR PeDecoder::ImageDelayImport(PDWORD* size)
	{
		return (PIMAGE_DELAYLOAD_DESCRIPTOR)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT, size);
	}
	
	PIMAGE_COR20_HEADER PeDecoder::ImageComDescriptor(PDWORD* size)
	{
		return (PIMAGE_COR20_HEADER)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR, size);
	}
	PeDecoder::~PeDecoder()
	{
	}
	PVOID PeDecoder::GetRvaData(DWORD rva)
	{
		DWORD offset;
		if (isMapped)
		{
			offset = rva;
		}
		else
		{
			offset = RvaToOffset(rva);
		}
		return base + offset;
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
	PIMAGE_SECTION_HEADER PeDecoder::GetFirstSectionHeader()
	{
		return firstSectionHeader;
	}
	PWORD PeDecoder::GetNumberOfSection()
	{
		return sectionCount;
	}
	UINT PeDecoder::AlignUp(UINT value, UINT alignment)
	{
		return (value + alignment - 1)&~(alignment - 1);
	}

	void PeDecoder::CheckImage()
	{
		// 设置初始值
		ntHeader = NULL;
		imageDataDirectoryEntry = NULL;
		imageDataDirectorySize = NULL;
		firstSectionHeader = NULL;
		lastSectionHeader = NULL;
		sectionAlignment = NULL;
		sectionCount = NULL;


		//  32 64位共用一些字段, 所以可以用NtHeader32
		if (DosHeader()->e_magic != IMAGE_DOS_SIGNATURE || ((PIMAGE_NT_HEADERS32)NtHeader())->Signature != IMAGE_NT_SIGNATURE)
		{
			isPE = false;
			return;
		}
		else
		{
			isPE = true;
		}
		// 设置下面这个值后就禁止共用
		imageType = &((PIMAGE_NT_HEADERS32)NtHeader())->OptionalHeader.Magic;

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
		}
		break;

		case IMAGE_ROM_OPTIONAL_HDR_MAGIC:
			// 第三种没见过, 定义里没节和数据目录, 不做解析
			break;
		default:

			break;
		}
		lastSectionHeader = firstSectionHeader + *sectionCount;

	}
	PVOID PeDecoder::NtHeader()
	{
		if (ntHeader == NULL)
		{
			ntHeader = base + DosHeader()->e_lfanew;
		}
		return ntHeader; 
	}
}