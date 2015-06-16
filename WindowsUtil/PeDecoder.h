#pragma once
#include <Windows.h>
#include <WinBase.h>
namespace PE{
	class PeDecoder
	{
	public:

		PeDecoder(PVOID pe, bool isMapped) :
			base((PCHAR)pe),
			isMapped(isMapped)
		{
			CheckImage();
		}

		bool HasNtHeader32()
		{
			return (*imageType == IMAGE_NT_OPTIONAL_HDR32_MAGIC);
		}
		bool IsPE()
		{
			return isPE;
		}

		PIMAGE_DOS_HEADER DosHeader()
		{
			return (PIMAGE_DOS_HEADER)base;
		}

		PIMAGE_NT_HEADERS32 NtHeader32()
		{
			if (*imageType != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
			{
				return NULL;
			}
			return (PIMAGE_NT_HEADERS32)NtHeader();
		}
		PIMAGE_NT_HEADERS64 NtHeader64()
		{
			if (*imageType != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
			{
				return NULL;
			}
			return (PIMAGE_NT_HEADERS64)NtHeader();
		}
		PIMAGE_ROM_HEADERS RomHeader()
		{
			if (*imageType == IMAGE_ROM_OPTIONAL_HDR_MAGIC)
			{
				return (PIMAGE_ROM_HEADERS)NtHeader();
			}
			return NULL;
		}
		PIMAGE_SECTION_HEADER RvaToSection(DWORD rva)
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
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset)
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
		DWORD RvaToOffset(DWORD rva)
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
		
		DWORD OffsetToRva(DWORD fileOffset)
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
		PIMAGE_EXPORT_DIRECTORY ImageDirectoryEntryExport()
		{
			auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_EXPORT);
			if (!dir)
			{
				return NULL;
			}
			return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}
		/*void ImageDirectoryEntryImport()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryResource()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryException()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntrySecurity()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryBasereloc()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryDebug()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryArchitecture()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryGlobalptr()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryTls()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_TLS];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryLoad_config()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryBound_import()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryIat()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_IAT];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryDelayImport()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT];
			if (DataDirectoryExist(result))
			{
			}
		}
		void ImageDirectoryEntryComDescriptor()
		{
			auto result = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR];
			if (DataDirectoryExist(result))
			{
			}
		}*/
		~PeDecoder()
		{
		}
	private:
		PCHAR base;
		PVOID ntHeader = NULL;
		PIMAGE_DATA_DIRECTORY imageDataDirectory = NULL;
		PDWORD imageDataDirectorySize = 0;
		PIMAGE_SECTION_HEADER firstSectionHeader = NULL;
		PIMAGE_SECTION_HEADER lastSectionHeader = NULL;
		PDWORD sectionAlignment = 0;
		PWORD sectionCount = 0;
		bool isMapped;
		bool isPE;
		PWORD imageType; //IMAGE_NT_OPTIONAL_HDR32_MAGIC IMAGE_NT_OPTIONAL_HDR64_MAGIC IMAGE_ROM_OPTIONAL_HDR_MAGIC

		UINT AlignUp(UINT value, UINT alignment)
		{
			return (value + alignment - 1)&~(alignment - 1);
		}

		void CheckImage()
		{
			//  32 64位共用一些字段, 所以可以用NtHeader32
			if (DosHeader()->e_magic != IMAGE_DOS_SIGNATURE || NtHeader32()->Signature != IMAGE_NT_SIGNATURE)
			{
				isPE = false;
			}
			else
			{
				isPE = true;
			}
			// 设置下面这个值后就禁止共用
			imageType = &NtHeader32()->OptionalHeader.Magic;
			
			switch (*imageType)
			{
			case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
				auto header32 = NtHeader32();
				imageDataDirectory = header32->OptionalHeader.DataDirectory;
				imageDataDirectorySize = &header32->OptionalHeader.NumberOfRvaAndSizes;
				sectionAlignment = &header32->OptionalHeader.SectionAlignment;
				firstSectionHeader = IMAGE_FIRST_SECTION(header32);
				sectionCount = &header32->FileHeader.NumberOfSections;	
				
				break;
			case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
				auto header64 = NtHeader64();
				imageDataDirectory = header64->OptionalHeader.DataDirectory;
				imageDataDirectorySize = &header64->OptionalHeader.NumberOfRvaAndSizes;
				sectionAlignment = &header64->OptionalHeader.SectionAlignment;
				firstSectionHeader = IMAGE_FIRST_SECTION(header64);
				sectionCount = &header64->FileHeader.NumberOfSections;
				break;
				
			case IMAGE_ROM_OPTIONAL_HDR_MAGIC:
				// 第三种没见过, 定义里没节和数据目录, 不做解析
				break;
			default:
				
				break;
			}
			lastSectionHeader = firstSectionHeader + *sectionCount;


		}
		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index)
		{			
			if (*imageDataDirectorySize > index && IMAGE_NUMBEROF_DIRECTORY_ENTRIES > index)
			{
				auto result = &imageDataDirectory[index];
				if (result->VirtualAddress != NULL)
				{
					return result;
				}
			}			
			return NULL;
		}

		
		PVOID NtHeader()
		{
			if (ntHeader == NULL)
			{
				ntHeader = base + DosHeader()->e_lfanew;
			}
			return ntHeader;
		}
		PVOID GetRvaData(DWORD rva)
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
	};
	class ExportDirectoryReader
	{
	public:
		ExportDirectoryReader(PIMAGE_EXPORT_DIRECTORY exportDirectory) :exportDirectory(exportDirectory)
		{
		
		}
		~ExportDirectoryReader(){}

	private:
		PIMAGE_EXPORT_DIRECTORY exportDirectory;
	};

}