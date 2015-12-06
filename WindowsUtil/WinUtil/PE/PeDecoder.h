#pragma once
#include <cassert>
#include <Windows.h>
#include <WinBase.h>
#include <WinTrust.h>
#include <delayimp.h>
#include <memory>
#include "DosHeader\DosHeader.h"
#include "NtHeader\NtHeader.h"
#include "Section\Section.h"
#include "Reloc\RelocDirectory.h"
#include "Export\ExportDirectory.h"
#include "Import\ImportDirectory.h"

namespace PE
{
#define ALIGN_UP(value, alignment) ((UINT)(value + alignment - 1)&~(alignment - 1))

	// PE解析器, 这个用来读本地程序或文件
	// TODO: 数据目录解析只完成了导入导出表\资源\重定位\节的读取器
	class PeDecoder
	{

		PBYTE base;

		bool isMapped;
		bool isPE;
		bool hasNtHeader32;

		_STD shared_ptr<DosHeader<PeDecoder>> dosHeader;
		_STD shared_ptr<NtHeader<PeDecoder>> ntHeader;
		_STD shared_ptr<SectionHeaders<PeDecoder>> section;
		_STD shared_ptr<RelocDirectory<PeDecoder>> relocDirectory;

		_STD shared_ptr<ExportDirectory<PeDecoder>> exportDirectory;
		_STD shared_ptr<ImportDirectory<PeDecoder>> importDirectory;
	public:
		PeDecoder()
		{
			Clear();
		}
		~PeDecoder() = default;
		void Clear()
		{
			relocDirectory = NULL;
		}
		PeDecoder(PeDecoder& pe) = delete;
		bool LoadPEImage(PVOID base, bool isMapped);

		PVOID GetBase();
		inline _STD shared_ptr<DosHeader<PeDecoder>> GetDosHeader()
		{
			return dosHeader;
		}
		inline _STD shared_ptr<NtHeader<PeDecoder>> GetNtHeader()
		{
			return ntHeader;
		}
		inline _STD shared_ptr<SectionHeaders<PeDecoder>> GetSection()
		{
			return section;
		}
		inline _STD shared_ptr<RelocDirectory<PeDecoder>> GetReloc()
		{
			if (!relocDirectory)
			{
				relocDirectory = _STD make_shared<RelocDirectory<PeDecoder>>(*this);
			}
			return relocDirectory;
		}
		inline _STD shared_ptr<ExportDirectory<PeDecoder>> GetExport()
		{
			if (!exportDirectory)
			{
				exportDirectory = _STD make_shared<ExportDirectory<PeDecoder>>(*this);
			}
			return exportDirectory;
		}
		inline _STD shared_ptr<ImportDirectory<PeDecoder>> GetImport()
		{
			if (!importDirectory)
			{
				importDirectory = _STD make_shared<ImportDirectory<PeDecoder>>(*this);
			}
			return importDirectory;
		}

		bool IsMapped();
		bool HasNtHeader32()
		{
			return hasNtHeader32;
		}
		inline bool IsPE()
		{
			return isPE;
		}

		/*PIMAGE_SECTION_HEADER RvaToSection(DWORD rva);
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset);
		DWORD RvaToOffset(DWORD rva);
		DWORD OffsetToRva(DWORD fileOffset);*/

		//PIMAGE_EXPORT_DIRECTORY GetImageExport(PDWORD* size = NULL);
		//PIMAGE_IMPORT_DESCRIPTOR GetImageImport(PDWORD* size = NULL);
		//PIMAGE_RESOURCE_DIRECTORY GetImageResource(PDWORD* size = NULL);
		//PIMAGE_BASE_RELOCATION GetImageBasereloc(PDWORD* size = NULL);
		//PVOID GetImageIat(PDWORD* size = NULL); // 取iat头, 可能为32也可能为64, 作用不是读信息,所以直接返回指针
		///*PIMAGE_DELAYLOAD_DESCRIPTOR*/PImgDelayDescr GetImageDelayImport(PDWORD* size = NULL);

//
//#pragma region 这部分未完成reader
//		PIMAGE_DEBUG_DIRECTORY GetImageDebug(PDWORD* size = NULL);
//		PIMAGE_RUNTIME_FUNCTION_ENTRY GetImageException(PDWORD* size = NULL);
//		PVOID GetImageSecurity(PDWORD* size = NULL);
//		PIMAGE_ARCHITECTURE_HEADER GetImageArchitecture(PDWORD* size = NULL);
//		PIMAGE_TLS_DIRECTORY64 GetImageTls64(PDWORD* size = NULL);
//		PIMAGE_TLS_DIRECTORY32 GetImageTls32(PDWORD* size = NULL);
//		PIMAGE_LOAD_CONFIG_DIRECTORY64 GetImageLoadConfig64(PDWORD* size = NULL);
//		PIMAGE_LOAD_CONFIG_DIRECTORY32 GetImageLoadConfig32(PDWORD* size = NULL);
//		PIMAGE_BOUND_IMPORT_DESCRIPTOR GetImageBoundImport(PDWORD* size = NULL);
//		PIMAGE_COR20_HEADER GetImageComDescriptor(PDWORD* size = NULL);
//#pragma endregion	


		PIMAGE_SECTION_HEADER RvaToSection(DWORD rva)
		{
			auto currentSection = section->firstSectionHeader;
			while (currentSection < section->lastSectionHeader)
			{
				if (rva < currentSection->VirtualAddress +
					ALIGN_UP((UINT)(currentSection->Misc.VirtualSize), (UINT)(*section->sectionAlignment)))
				{
					return rva < currentSection->VirtualAddress ? NULL : currentSection;
				}
				currentSection++;
			}
			return NULL;
		}
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset)
		{
			auto currentSection = section->firstSectionHeader;
			while (currentSection < section->lastSectionHeader)
			{
				if (fileOffset < currentSection->PointerToRawData + currentSection->SizeOfRawData)
				{
					return fileOffset < currentSection->PointerToRawData ? NULL : currentSection;
				}
				currentSection++;
			}
			return NULL;
		}
		DWORD RvaToOffset(DWORD rva)
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

		DWORD OffsetToRva(DWORD fileOffset)
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
		PVOID GetRvaData(DWORD rva)
		{
			return base + (isMapped ? rva : RvaToOffset(rva));
		}


		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index)
		{
			if (*ntHeader->imageDataDirectorySize > index && IMAGE_NUMBEROF_DIRECTORY_ENTRIES > index)
			{
				return &ntHeader->imageDataDirectoryEntry[index];
			}
			return NULL;
		}




		PVOID DirectoryEntryToData(DWORD index, PDWORD* size)
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
			return NULL;
		}

		PIMAGE_RESOURCE_DIRECTORY GetImageResource(PDWORD* size = NULL)
		{
			return (PIMAGE_RESOURCE_DIRECTORY)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_RESOURCE, size);
		}
		PIMAGE_RUNTIME_FUNCTION_ENTRY GetImageException(PDWORD* size = NULL)
		{
			return (PIMAGE_RUNTIME_FUNCTION_ENTRY)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_EXCEPTION, size);
		}
		PVOID GetImageSecurity(PDWORD* size = NULL)
		{
			if (isMapped)
			{
				return NULL;
			}
			auto dir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_SECURITY);
			if (!dir || dir->VirtualAddress == NULL)
			{
				return NULL;
			}
			if (size)
			{
				*size = &dir->Size;
			}
			return base + dir->VirtualAddress;
		}
	
		PIMAGE_DEBUG_DIRECTORY GetImageDebug(PDWORD* size = NULL)
		{
			return (PIMAGE_DEBUG_DIRECTORY)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_DEBUG, size);
		}
		PIMAGE_ARCHITECTURE_HEADER GetImageArchitecture(PDWORD* size = NULL)
		{
			return (PIMAGE_ARCHITECTURE_HEADER)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE, size);
		}
		/*
		? ImageDirectoryEntryGlobalptr()
		{
		return (PIMAGE_EXPORT_DIRECTORY)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_GLOBALPTR, size);
		}*/

		PIMAGE_TLS_DIRECTORY32 GetImageTls32(PDWORD* size = NULL)
		{
			return hasNtHeader32 ? (PIMAGE_TLS_DIRECTORY32)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_TLS, size) : NULL;
		}
		PIMAGE_TLS_DIRECTORY64 GetImageTls64(PDWORD* size = NULL)
		{
			return hasNtHeader32 ? NULL : (PIMAGE_TLS_DIRECTORY64)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_TLS, size);
		}

		PIMAGE_LOAD_CONFIG_DIRECTORY32 GetImageLoadConfig32(PDWORD* size = NULL)
		{
			return hasNtHeader32 ? (PIMAGE_LOAD_CONFIG_DIRECTORY32)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, size) : NULL;
		}
		PIMAGE_LOAD_CONFIG_DIRECTORY64 GetImageLoadConfig64(PDWORD* size = NULL)
		{
			return hasNtHeader32 ? NULL : (PIMAGE_LOAD_CONFIG_DIRECTORY64)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, size);
		}

		PIMAGE_BOUND_IMPORT_DESCRIPTOR GetImageBoundImport(PDWORD* size = NULL)
		{
			return (PIMAGE_BOUND_IMPORT_DESCRIPTOR)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT, size);
		}
		PVOID GetImageIat(PDWORD* size)
		{
			return /*(IMAGE_THUNK_DATA32)*/DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_IAT, size);
		}

		PImgDelayDescr GetImageDelayImport(PDWORD* size = NULL)
		{
			return (PImgDelayDescr)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT, size);
		}

		PIMAGE_COR20_HEADER GetImageComDescriptor(PDWORD* size = NULL)
		{
			return (PIMAGE_COR20_HEADER)DirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR, size);
		}
	};

}