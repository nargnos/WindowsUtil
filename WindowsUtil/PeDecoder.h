#pragma once
#include <iostream>
#include <Windows.h>
#include <WinBase.h>
namespace PE{
	using namespace std;
	class PeDecoder
	{
	public:

		PeDecoder(PVOID pe, bool isMapped) :
			base((PCHAR)pe),
			isMapped(isMapped)
		{
			CheckImage();
		}
		bool Is32Image()
		{
			return (*imageType != IMAGE_NT_OPTIONAL_HDR64_MAGIC);
		}
		bool IsPE()
		{
			return isPE;
		}


		PIMAGE_DOS_HEADER DosHeader()
		{
			return reinterpret_cast<PIMAGE_DOS_HEADER>(base);
		}

		PIMAGE_NT_HEADERS32 NtHeader32()
		{
			if (!Is32Image())
			{
				return NULL;
			}
			return reinterpret_cast<PIMAGE_NT_HEADERS32>(NtHeader());
		}
		PIMAGE_NT_HEADERS64 NtHeader64()
		{
			if (Is32Image())
			{
				return NULL;
			}
			return reinterpret_cast<PIMAGE_NT_HEADERS64>(NtHeader());
		}
		PIMAGE_EXPORT_DIRECTORY ImageDirectoryEntryExport()
		{
			auto dir = &imageDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
			if (DataDirectoryExist(dir))
			{
				return dir->VirtualAddress
				//ptr
				//result->
			}
		}
		void ImageDirectoryEntryImport()
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
		}
		~PeDecoder()
		{
		}
	private:
		PCHAR base;
		PVOID ntHeader = NULL;
		PIMAGE_DATA_DIRECTORY imageDataDirectory = NULL;
		bool isMapped;
		bool isPE;
		PWORD imageType; //IMAGE_NT_OPTIONAL_HDR32_MAGIC IMAGE_NT_OPTIONAL_HDR64_MAGIC IMAGE_ROM_OPTIONAL_HDR_MAGIC
		void CheckImage()
		{
			if (DosHeader()->e_magic != IMAGE_DOS_SIGNATURE || NtHeader32()->Signature != IMAGE_NT_SIGNATURE)
			{
				isPE = false;
			}
			else
			{
				isPE = true;
			}
			imageType = &NtHeader32()->OptionalHeader.Magic;
			switch (*imageType)
			{
			case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
				imageDataDirectory = NtHeader32()->OptionalHeader.DataDirectory;
				break;
			case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
				imageDataDirectory = NtHeader64()->OptionalHeader.DataDirectory;
				break;
			default:
				// 第三种没见过
				break;
			}
		}
		bool DataDirectoryExist(PIMAGE_DATA_DIRECTORY dir)
		{
			return dir->VirtualAddress != NULL;
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