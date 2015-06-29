#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <WinTrust.h>
namespace PE
{
	// PE解析器
	// TODO: 数据目录解析只完成了导入导出表\资源\重定位\节的读取器
	class PeDecoder
	{
	public:

		PeDecoder(PVOID pe, bool isMapped);
		~PeDecoder();
		bool HasNtHeader32();
		bool IsPE();
		bool IsMapped();
		PVOID GetBase();
		PIMAGE_DOS_HEADER DosHeader();

		PIMAGE_NT_HEADERS32 NtHeader32();
		PIMAGE_NT_HEADERS64 NtHeader64();
		PIMAGE_ROM_HEADERS RomHeader();
		PIMAGE_SECTION_HEADER RvaToSection(DWORD rva);
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset);
		DWORD RvaToOffset(DWORD rva);
		DWORD OffsetToRva(DWORD fileOffset);
		PIMAGE_EXPORT_DIRECTORY GetImageExport();
		PIMAGE_IMPORT_DESCRIPTOR GetImageImport();
		PIMAGE_RESOURCE_DIRECTORY GetImageResource();
		PIMAGE_BASE_RELOCATION GetImageBasereloc();
		PVOID ImageIat(); // 取iat头, 可能为32也可能为64, 作用不是读信息,所以直接返回指针


#pragma region 这部分未完成reader
		PIMAGE_DEBUG_DIRECTORY ImageDebug();
		PIMAGE_RUNTIME_FUNCTION_ENTRY ImageException();
		PVOID ImageSecurity();
		PIMAGE_ARCHITECTURE_HEADER ImageArchitecture();
		PIMAGE_TLS_DIRECTORY64 ImageTls64();
		PIMAGE_TLS_DIRECTORY32 ImageTls32();
		PIMAGE_LOAD_CONFIG_DIRECTORY64 ImageLoadConfig64();
		PIMAGE_LOAD_CONFIG_DIRECTORY32 ImageLoadConfig32();
		PIMAGE_DELAYLOAD_DESCRIPTOR ImageDelayImport();
		PIMAGE_BOUND_IMPORT_DESCRIPTOR ImageBoundImport();
		PIMAGE_COR20_HEADER ImageComDescriptor();
#pragma endregion	
		

		PVOID GetRvaData(DWORD rva);
		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index);
		PIMAGE_SECTION_HEADER GetFirstSectionHeader();
		PWORD GetNumberOfSection();
	private:
		PUINT8 base;
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
		UINT AlignUp(UINT value, UINT alignment);
		void CheckImage();
		PVOID NtHeader();

	};
}