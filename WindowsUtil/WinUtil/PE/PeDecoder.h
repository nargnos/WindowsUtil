#pragma once
#include <cassert>
#include <Windows.h>
#include <WinBase.h>
#include <WinTrust.h>
#include <memory>
namespace PE
{
	
	class DosHeader;
	class NtHeader;
	class SectionHeaders;
	class RelocDirectory;
	class ExportDirectory;
	class ImportDirectory;
	class ResourceDirectory;
	class EntryExceptionDirectory;
	class SecurityDirectory;
	class DebugDirectory;
	class ArchitectureDirectory;
	class GlobalptrDirectory;
	class TlsDirectory;
	class LoadConfigDirectory;
	class BoundImportDirectory;
	class IatDirectory;
	class DelayImportDirectory;
	class ComDescriptorDirectory;

	// PE解析器, 这个用来读本地程序或文件
	// TODO: 数据目录解析只完成了导入导出表\资源\重定位\节的读取器
	class PeDecoder
	{
		PBYTE base;

		bool isMapped;
		bool isPE;
		bool hasNtHeader32;

		_STD shared_ptr<DosHeader> dosHeader;
		_STD shared_ptr<NtHeader> ntHeader;
		_STD shared_ptr<SectionHeaders> section;
		_STD shared_ptr<RelocDirectory> relocDirectory;

		_STD shared_ptr<ExportDirectory> exportDirectory;
		_STD shared_ptr<ImportDirectory> importDirectory;
		_STD shared_ptr<ResourceDirectory> resource;
		_STD shared_ptr<EntryExceptionDirectory> exception;
		_STD shared_ptr<SecurityDirectory> security;
		_STD shared_ptr<DebugDirectory> debug;
		_STD shared_ptr<ArchitectureDirectory> architecture;
		_STD shared_ptr<GlobalptrDirectory> globalptr;
		_STD shared_ptr<TlsDirectory> tls;
		_STD shared_ptr<LoadConfigDirectory> loadConfig;
		_STD shared_ptr<BoundImportDirectory> boundImport;
		_STD shared_ptr<IatDirectory> iat;
		_STD shared_ptr<DelayImportDirectory> delayImport;
		_STD shared_ptr<ComDescriptorDirectory> comDescriptor;

	public:
		PeDecoder();
		~PeDecoder() = default;
		void Clear();
		PeDecoder(PeDecoder& pe) = delete;
		bool LoadPEImage(PVOID base, bool isMapped);

		PVOID GetBase();
		_STD shared_ptr<DosHeader> GetDosHeader();
		_STD shared_ptr<NtHeader> GetNtHeader();
		_STD shared_ptr<SectionHeaders> GetSection();
		_STD shared_ptr<RelocDirectory> GetReloc();
		_STD shared_ptr<ExportDirectory> GetExport();
		_STD shared_ptr<ImportDirectory> GetImport();
		_STD shared_ptr<ResourceDirectory> GetResource();
		_STD shared_ptr<EntryExceptionDirectory> GetException();
		_STD shared_ptr<SecurityDirectory> GetSecurity();
		_STD shared_ptr<DebugDirectory> GetDebug();
		_STD shared_ptr<ArchitectureDirectory> GetArchitecture();
		_STD shared_ptr<GlobalptrDirectory> GetGlobalptr();
		_STD shared_ptr<TlsDirectory> GetTls();
		_STD shared_ptr<LoadConfigDirectory> GetLoadConfig();
		_STD shared_ptr<BoundImportDirectory> GetBoundImport();
		_STD shared_ptr<IatDirectory> GetIat();
		_STD shared_ptr<DelayImportDirectory> GetDelayImport();
		_STD shared_ptr<ComDescriptorDirectory> GetComDescriptor();
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