#pragma once
#include <cassert>
#include <Windows.h>
#include <WinBase.h>
#include <WinTrust.h>
#include <memory>
#include "DosHeader\DosHeader.h"
#include "NtHeader\NtHeader.h"
#include "Section\Section.h"
#include "Reloc\RelocDirectory.h"
#include "Export\ExportDirectory.h"
#include "Import\ImportDirectory.h"
#include "Resource\ResourceDirectory.h"
#include "EntryException\EntryExceptionDirectory.h"
#include "Security\SecurityDirectory.h"
#include "Architecture\ArchitectureDirectory.h"
#include "Globalptr\GlobalptrDirectory.h"
#include "BoundImport\BoundImportDirectory.h"
#include "ComDescriptor\ComDescriptorDirectory.h"
#include "DelayImport\DelayImportDirectory.h"
#include "Iat\IatDirectory.h"
#include "LoadConfig\LoadConfigDirectory.h"
#include "Tls\TlsDirectory.h"
#include "Debug\DebugDirectory.h"
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
		_STD shared_ptr<ResourceDirectory<PeDecoder>> resource;
		_STD shared_ptr<EntryExceptionDirectory<PeDecoder>> exception;
		_STD shared_ptr<SecurityDirectory<PeDecoder>> security;
		_STD shared_ptr<DebugDirectory<PeDecoder>> debug;
		_STD shared_ptr<ArchitectureDirectory<PeDecoder>> architecture;
		_STD shared_ptr<GlobalptrDirectory<PeDecoder>> globalptr;
		_STD shared_ptr<TlsDirectory<PeDecoder>> tls;
		_STD shared_ptr<LoadConfigDirectory<PeDecoder>> loadConfig;
		_STD shared_ptr<BoundImportDirectory<PeDecoder>> boundImport;
		_STD shared_ptr<IatDirectory<PeDecoder>> iat;
		_STD shared_ptr<DelayImportDirectory<PeDecoder>> delayImport;
		_STD shared_ptr<ComDescriptorDirectory<PeDecoder>> comDescriptor;

	public:
		PeDecoder();
		~PeDecoder() = default;
		void Clear();
		PeDecoder(PeDecoder& pe) = delete;
		bool LoadPEImage(PVOID base, bool isMapped);

		PVOID GetBase();
		_STD shared_ptr<DosHeader<PeDecoder>> GetDosHeader();
		_STD shared_ptr<NtHeader<PeDecoder>> GetNtHeader();
		_STD shared_ptr<SectionHeaders<PeDecoder>> GetSection();
		_STD shared_ptr<RelocDirectory<PeDecoder>> GetReloc();
		_STD shared_ptr<ExportDirectory<PeDecoder>> GetExport();
		_STD shared_ptr<ImportDirectory<PeDecoder>> GetImport();
		_STD shared_ptr<ResourceDirectory<PeDecoder>> GetResource();
		_STD shared_ptr<EntryExceptionDirectory<PeDecoder>> GetException();
		_STD shared_ptr<SecurityDirectory<PeDecoder>> GetSecurity();
		_STD shared_ptr<DebugDirectory<PeDecoder>> GetDebug();
		_STD shared_ptr<ArchitectureDirectory<PeDecoder>> GetArchitecture();
		_STD shared_ptr<GlobalptrDirectory<PeDecoder>> GetGlobalptr();
		_STD shared_ptr<TlsDirectory<PeDecoder>> GetTls();
		_STD shared_ptr<LoadConfigDirectory<PeDecoder>> GetLoadConfig();
		_STD shared_ptr<BoundImportDirectory<PeDecoder>> GetBoundImport();
		_STD shared_ptr<IatDirectory<PeDecoder>> GetIat();
		_STD shared_ptr<DelayImportDirectory<PeDecoder>> GetDelayImport();
		_STD shared_ptr<ComDescriptorDirectory<PeDecoder>> GetComDescriptor();
		bool IsMapped();
		bool HasNtHeader32();
		bool IsPE();
		PIMAGE_SECTION_HEADER RvaToSection(DWORD rva);
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset);
		DWORD RvaToOffset(DWORD rva);
		DWORD OffsetToRva(DWORD fileOffset);
		PVOID GetRvaData(DWORD rva);
		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index);
		PVOID DirectoryEntryToData(DWORD index, PDWORD* size);

	};

}