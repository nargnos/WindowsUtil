#pragma once
#include <cassert>
#include <Windows.h>
#include <WinBase.h>
#include <WinTrust.h>
#include <delayimp.h>
#include "PeDecoder.h"
#pragma region 友元用的一些预定义
namespace Process
{
	namespace Hook
	{
		PVOID HookEat(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc, PDWORD oldFuncRva);
		PVOID HookIat(LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress);
	}
}
namespace PE
{
	class PeDecoder;
	namespace Import
	{
		class ImportThunkReader;
		PVOID GetProcImportThunkAddress(PeDecoder& pe, LPCSTR dllName, LPCSTR procName);
	}
	namespace DelayLoad
	{
		PVOID GetDelayLoadAddressTableAddress(PeDecoder& pe, LPCSTR dllName, LPCSTR procName);
	}
	namespace Section
	{
		class SectionReader;
	}
	namespace Export
	{
		FARPROC GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName));
		PDWORD GetProcExportFuncTableAddress(PeDecoder& pe, LPCSTR lpProcName);
	}
}
#pragma endregion
namespace PE
{
#define ALIGN_UP(value, alignment) ((UINT)(value + alignment - 1)&~(alignment - 1))
	
	// PE解析器, 这个用来读本地程序或文件
	// TODO: 数据目录解析只完成了导入导出表\资源\重定位\节的读取器
	class PeDecoder
	{
	public:
		friend class Section::SectionReader;
		friend class Import::ImportThunkReader;
		friend PVOID DelayLoad::GetDelayLoadAddressTableAddress(PeDecoder& pe, LPCSTR dllName, LPCSTR procName);
		friend PVOID Import::GetProcImportThunkAddress(PeDecoder& pe, LPCSTR dllName, LPCSTR procName);
		friend PVOID Process::Hook::HookEat(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc, PDWORD oldFuncRva);
		friend PVOID Process::Hook::HookIat(LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress);
		friend FARPROC Export::GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName));
		friend PDWORD Export::GetProcExportFuncTableAddress(PeDecoder& pe, LPCSTR lpProcName);

		PeDecoder()=default;
		~PeDecoder() = default;
		PeDecoder(PeDecoder& pe)=delete;
		bool LoadPEImage(PVOID base, bool isMapped);
		PVOID GetBase();
		bool IsMapped();
		PIMAGE_DOS_HEADER DosHeader();
		PIMAGE_NT_HEADERS32 NtHeader32();
		PIMAGE_NT_HEADERS64 NtHeader64();
		bool HasNtHeader32();

		PIMAGE_SECTION_HEADER RvaToSection(DWORD rva);
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset);
		DWORD RvaToOffset(DWORD rva);
		DWORD OffsetToRva(DWORD fileOffset);

		PIMAGE_EXPORT_DIRECTORY GetImageExport(PDWORD* size = NULL);
		PIMAGE_IMPORT_DESCRIPTOR GetImageImport(PDWORD* size = NULL);
		PIMAGE_RESOURCE_DIRECTORY GetImageResource(PDWORD* size = NULL);
		PIMAGE_BASE_RELOCATION GetImageBasereloc(PDWORD* size = NULL);
		PVOID GetImageIat(PDWORD* size = NULL); // 取iat头, 可能为32也可能为64, 作用不是读信息,所以直接返回指针
		/*PIMAGE_DELAYLOAD_DESCRIPTOR*/PImgDelayDescr GetImageDelayImport(PDWORD* size = NULL);


#pragma region 这部分未完成reader
		PIMAGE_DEBUG_DIRECTORY GetImageDebug(PDWORD* size = NULL);
		PIMAGE_RUNTIME_FUNCTION_ENTRY GetImageException(PDWORD* size = NULL);
		PVOID GetImageSecurity(PDWORD* size = NULL);
		PIMAGE_ARCHITECTURE_HEADER GetImageArchitecture(PDWORD* size = NULL);
		PIMAGE_TLS_DIRECTORY64 GetImageTls64(PDWORD* size = NULL);
		PIMAGE_TLS_DIRECTORY32 GetImageTls32(PDWORD* size = NULL);
		PIMAGE_LOAD_CONFIG_DIRECTORY64 GetImageLoadConfig64(PDWORD* size = NULL);
		PIMAGE_LOAD_CONFIG_DIRECTORY32 GetImageLoadConfig32(PDWORD* size = NULL);
		PIMAGE_BOUND_IMPORT_DESCRIPTOR GetImageBoundImport(PDWORD* size = NULL);
		PIMAGE_COR20_HEADER GetImageComDescriptor(PDWORD* size = NULL);
#pragma endregion	
		

		PVOID GetRvaData(DWORD rva);
		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index);
	private:
		
		PBYTE base;
		PIMAGE_DOS_HEADER dosHeader;
		PIMAGE_NT_HEADERS32 ntHeader;
		
		bool isMapped;
		bool isPE;
		bool hasNtHeader32;
		PWORD imageType; //IMAGE_NT_OPTIONAL_HDR32_MAGIC IMAGE_NT_OPTIONAL_HDR64_MAGIC IMAGE_ROM_OPTIONAL_HDR_MAGIC
		PVOID DirectoryEntryToData(DWORD index, PDWORD* size); // 可根据需要获取size指针, size为NULL则不取值,返回为NULL时不改变size指针的值
		
		PIMAGE_DATA_DIRECTORY imageDataDirectoryEntry;
		PDWORD imageDataDirectorySize;
		PIMAGE_SECTION_HEADER firstSectionHeader;
		PIMAGE_SECTION_HEADER lastSectionHeader;
		PDWORD sectionAlignment;
		PWORD sectionCount;
	};

}