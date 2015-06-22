#pragma once
#include <Windows.h>
#include <WinBase.h>
namespace PE
{
	// PE解析器
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
		PVOID GetBase()
		{
			return base;
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

		PIMAGE_EXPORT_DIRECTORY GetImageExport()
		{
			auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_EXPORT);
			if (!dir)
			{
				return NULL;
			}
			return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}

		PIMAGE_IMPORT_DESCRIPTOR GetImageImport()
		{
			auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_IMPORT);
			if (!dir)
			{
				return NULL;
			}
			return (PIMAGE_IMPORT_DESCRIPTOR)GetRvaData(dir->VirtualAddress);
		}
		PIMAGE_RESOURCE_DIRECTORY GetImageResource()
		{
			auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_RESOURCE);
			if (!dir)
			{
				return NULL;
			}
			return (PIMAGE_RESOURCE_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}
		/*void ImageDirectoryEntryException()
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_EXCEPTION);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}*/
		/*void ImageDirectoryEntrySecurity()
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_SECURITY);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}*/
		PIMAGE_RELOCATION GetImageBasereloc()
		{
			auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_BASERELOC);
			if (!dir)
			{
				return NULL;
			}
			return (PIMAGE_RELOCATION)GetRvaData(dir->VirtualAddress);
		}
		/*void ImageDirectoryEntryDebug()
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_DEBUG);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}
		void ImageDirectoryEntryArchitecture()
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}
		void ImageDirectoryEntryGlobalptr()
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_GLOBALPTR);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}*/

		/*void ImageDirectoryEntryTls() // 这个有32 64区分
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_TLS);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}*/
		//void ImageDirectoryEntryLoadConfig() //PIMAGE_LOAD_CONFIG_DIRECTORY64
		//{
		//	auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG);
		//	if (!dir)
		//	{
		//		return NULL;
		//	}
		//	return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		//}
		/*void ImageDirectoryEntryBoundImport()
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}*/
		/*DWORD ImageDirectoryEntryIat()
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_IAT);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}*/
		/*
		void ImageDirectoryEntryDelayImport()
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}
		void ImageDirectoryEntryComDescriptor()
		{
		auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR);
		if (!dir)
		{
		return NULL;
		}
		return (PIMAGE_EXPORT_DIRECTORY)GetRvaData(dir->VirtualAddress);
		}*/
		~PeDecoder()
		{
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
		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index)
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
		PIMAGE_SECTION_HEADER GetFirstSectionHeader()
		{
			return firstSectionHeader;
		}
		PWORD GetNumberOfSection()
		{
			return sectionCount;
		}
	private:
		PCHAR base;
		PVOID ntHeader;
		PIMAGE_DATA_DIRECTORY imageDataDirectoryEntry;
		PDWORD imageDataDirectorySize;
		PIMAGE_SECTION_HEADER firstSectionHeader;
		PIMAGE_SECTION_HEADER lastSectionHeader;
		PDWORD sectionAlignment;
		PWORD sectionCount;


		bool isMapped;
		bool isPE;
		PWORD imageType; //IMAGE_NT_OPTIONAL_HDR32_MAGIC IMAGE_NT_OPTIONAL_HDR64_MAGIC IMAGE_ROM_OPTIONAL_HDR_MAGIC

		UINT AlignUp(UINT value, UINT alignment)
		{
			return (value + alignment - 1)&~(alignment - 1);
		}

		void CheckImage()
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



		PVOID NtHeader()
		{
			if (ntHeader == NULL)
			{
				ntHeader = base + DosHeader()->e_lfanew;
			}
			return ntHeader;
		}

	};



	// 导入表Descriptor结构读取器
	class ImportDescriptorReader
	{
	public:
		ImportDescriptorReader(PeDecoder& pe)
		{

			descriptor = pe.GetImageImport();
			if (descriptor)
			{
				descriptorLength = &pe.GetDataDirectory(IMAGE_DIRECTORY_ENTRY_IMPORT)->Size;
			}
			else
			{
				descriptorLength = 0;
			}
			Reset();
		}
		~ImportDescriptorReader(){}
		bool Next()
		{
			if (descriptorLength)
			{
				if (++currentIndex < *descriptorLength)
				{
					auto checkResult = descriptor[currentIndex];
					if (checkResult.Name == NULL || checkResult.FirstThunk == NULL)
					{
						return false;
					}
					return true;
				}
			}
			return false;
		}
		PIMAGE_IMPORT_DESCRIPTOR Current()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &descriptor[currentIndex];
		}

		void Reset()
		{
			currentIndex = -1;
		}
	private:
		PDWORD descriptorLength;
		DWORD currentIndex;
		PIMAGE_IMPORT_DESCRIPTOR descriptor;
	};

	// 导入表Thunk结构读取器
#define CONVERT_THUNK_POINTER(thunkPointer, x) ((PIMAGE_THUNK_DATA##x)thunkPointer)
	class ImportThunkReader
	{
	public:
		ImportThunkReader(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR importDescriptor) :
			importDescriptor(importDescriptor),
			pe(pe)
		{
			is32 = pe.HasNtHeader32();
			originalThunk = pe.GetRvaData(importDescriptor->OriginalFirstThunk);
			thunk = pe.GetRvaData(importDescriptor->FirstThunk);
			Reset();
		}

		PIMAGE_THUNK_DATA32 CurrentThunk32()
		{
			if (is32)
			{
				return CONVERT_THUNK_POINTER(thunk, 32);
			}
			return NULL;
		}
		PIMAGE_THUNK_DATA32 CurrentOriginalThunk32()
		{
			if (is32)
			{
				return CONVERT_THUNK_POINTER(originalThunk, 32);
			}
			return NULL;
		}
		PIMAGE_THUNK_DATA64 CurrentThunk64()
		{
			if (is32)
			{
				return NULL;
			}
			return CONVERT_THUNK_POINTER(thunk, 64);
		}

		PIMAGE_THUNK_DATA64 CurrentOriginalThunk64()
		{
			if (is32)
			{
				return NULL;
			}
			return CONVERT_THUNK_POINTER(originalThunk, 64);
		}

		bool IsSnapByOrdinal(PIMAGE_THUNK_DATA32 thunk)
		{			
			return IMAGE_SNAP_BY_ORDINAL32(thunk->u1.Ordinal);
		}
		bool IsSnapByOrdinal(PIMAGE_THUNK_DATA64 thunk)
		{
			return IMAGE_SNAP_BY_ORDINAL64(thunk->u1.Ordinal);
		}
		ULONGLONG GetOrdinal(PIMAGE_THUNK_DATA64 thunk)
		{
			return IMAGE_ORDINAL64(thunk->u1.Ordinal);
		}
		DWORD GetOrdinal(PIMAGE_THUNK_DATA32 thunk)
		{
			return IMAGE_ORDINAL32(thunk->u1.Ordinal);
		}
		PIMAGE_IMPORT_BY_NAME GetImportByNameStruct(PIMAGE_THUNK_DATA32 thunk)
		{
			return (PIMAGE_IMPORT_BY_NAME)pe.GetRvaData(thunk->u1.AddressOfData);
		}
		PIMAGE_IMPORT_BY_NAME GetImportByNameStruct(PIMAGE_THUNK_DATA64 thunk)
		{
			return (PIMAGE_IMPORT_BY_NAME)pe.GetRvaData(thunk->u1.AddressOfData);
		}
		bool Next()
		{
#define CHECK_THUNK(x) auto tmpThunk = CONVERT_THUNK_POINTER(currentThunk, x) + 1;\
			if (CONVERT_THUNK_POINTER(currentThunk,x)->u1.AddressOfData == NULL)\
			{\
				return false;\
			}\
			currentThunk = tmpThunk;\
			currentOriginalThunk = CONVERT_THUNK_POINTER(currentOriginalThunk, x) + 1;


			if (is32)
			{
				CHECK_THUNK(32);
			}
			else
			{
				CHECK_THUNK(64);
			}


			return true;
		}
		void Reset()
		{
			currentThunk = thunk;
			currentOriginalThunk = originalThunk;
		}
		~ImportThunkReader(){}

	private:
		PIMAGE_IMPORT_DESCRIPTOR importDescriptor;
		bool is32;
		PVOID currentThunk;
		PVOID currentOriginalThunk;
		PeDecoder& pe;
		PVOID originalThunk;
		PVOID thunk;

	};



	// 导出表读取器 TODO: 添加一个c++函数名称翻译器,或找一下系统里面有没有现成函数
	class ExportReader
	{
	public:
		ExportReader(PeDecoder& pe) :ExportReader(pe, pe.GetImageExport())
		{
		}
		ExportReader(PeDecoder& pe, PIMAGE_EXPORT_DIRECTORY exportDirectory)
		{
			this->exportDirectory = exportDirectory;
			if (exportDirectory)
			{
				numberOfFunctions = &exportDirectory->NumberOfFunctions;
				funcs = (PDWORD)pe.GetRvaData(exportDirectory->AddressOfFunctions);
				names = (PDWORD)pe.GetRvaData(exportDirectory->AddressOfNames);
				nameOrdinals = (PWORD)pe.GetRvaData(exportDirectory->AddressOfNameOrdinals);
			}
			else
			{
				numberOfFunctions = NULL;
			}
			Reset();
		}
		~ExportReader(){}
		PIMAGE_EXPORT_DIRECTORY GetExportDirectory()
		{
			return exportDirectory;
		}
		PDWORD CurrentFuncRva()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &funcs[nameOrdinals[currentIndex]];
		}
		PDWORD CurrentNameRva()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &names[nameOrdinals[currentIndex]];
		}
		PWORD CurrentNameOrdinals()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &nameOrdinals[currentIndex];
		}
		bool Next()
		{
			if (numberOfFunctions)
			{
				if (++currentIndex < *numberOfFunctions)
				{
					return true;
				}
			}
			return false;
		}
		void Reset()
		{
			currentIndex = -1;
		}
	private:
		PIMAGE_EXPORT_DIRECTORY exportDirectory;
		PDWORD numberOfFunctions;
		PDWORD funcs;
		PDWORD names;
		PWORD nameOrdinals;
		DWORD currentIndex;
	};

	// 节读取器
	class SectionReader
	{
	public:
		
		SectionReader(PIMAGE_SECTION_HEADER firstSectionHeader, PIMAGE_SECTION_HEADER lastSectionHeader):
			firstSectionHeader(firstSectionHeader),
			lastSectionHeader(lastSectionHeader)
		{
			Reset();
		}
		SectionReader(PIMAGE_SECTION_HEADER firstSectionHeader, WORD sectionCount):
			SectionReader(firstSectionHeader, firstSectionHeader + sectionCount)
		{
		}
		SectionReader(PeDecoder& pe) :SectionReader(pe.GetFirstSectionHeader(), *pe.GetNumberOfSection())
		{
		}
		~SectionReader(){}
		PIMAGE_SECTION_HEADER Current()
		{
			return sectionPointer;
		}
		bool Next()
		{
			if (sectionPointer)
			{
				auto tmpSectionPointer = sectionPointer + 1;
				if (tmpSectionPointer != lastSectionHeader)
				{
					sectionPointer = tmpSectionPointer;
				}
				else
				{
					return false;
				}
			}
			else
			{
				sectionPointer = firstSectionHeader;
			}
			return true;
		}
		void Reset()
		{
			sectionPointer = NULL;
		}
	private:
		PIMAGE_SECTION_HEADER firstSectionHeader;
		PIMAGE_SECTION_HEADER lastSectionHeader;
		PIMAGE_SECTION_HEADER sectionPointer;
	};


}