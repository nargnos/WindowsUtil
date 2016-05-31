#pragma once
#include "PeImageFwd.h"
#include "ImageType.h"

namespace PeDecoder
{
	class PeImage
	{
	public:
		PeImage(void* ptr, bool isMapped);
		~PeImage() = default;
		// 是否是映射的
		bool IsMapped() const;
		bool IsPe() const;
		void* GetBase() const;
		ImageType GetImageType() const;

		// 必存在结构
		const unique_ptr<DosHeader>& GetDosHeader();
		const unique_ptr<NtHeader>& GetNtHeader();
		const unique_ptr<SectionHeaders>& GetSections();
		// 可存在结构，需要加判断
		const unique_ptr<ArchitectureDirectory>& GetArchitectureDirectory();
		const unique_ptr<BoundImportDirectory>& GetBoundImportDirectory();
		const unique_ptr<ComDescriptorDirectory>& GetComDescriptorDirectory();
		const unique_ptr<DebugDirectory>& GetDebugDirectory();
		const unique_ptr<DelayImportDirectory>& GetDelayImportDirectory();
		const unique_ptr<ExceptionDirectory>& GetExceptionDirectory();
		const unique_ptr<ExportDirectory>& GetExportDirectory();
		const unique_ptr<GlobalptrDirectory>& GetGlobalptrDirectory();
		const unique_ptr<IatDirectory>& GetIatDirectory();
		const unique_ptr<ImportDirectory>& GetImportDirectory();
		const unique_ptr<LoadConfigDirectory>& GetLoadConfigDirectory();
		const unique_ptr<RelocDirectory>& GetRelocDirectory();
		const unique_ptr<ResourceDirectory>& GetResourceDirectory();
		const unique_ptr<SecurityDirectory>& GetSecurityDirectory();
		const unique_ptr<TlsDirectory>& GetTlsDirectory();


		DWORD RvaToOffset(DWORD rva);
		ULONGLONG RvaToOffset(ULONGLONG rva);
		DWORD OffsetToRva(DWORD fileOffset);
		PVOID RvaToDataPtr(DWORD rva);
		PVOID RvaToDataPtr(ULONGLONG rva);
		static void* GetNtHeader(const PIMAGE_DOS_HEADER dosHeader);
	protected:
		PeImage(const PeImage&) = delete;
		PeImage& operator=(const PeImage&) = delete;


		unique_ptr<ArchitectureDirectory> architectureDirectory_;
		unique_ptr<BoundImportDirectory> boundImportDirectory_;
		unique_ptr<ComDescriptorDirectory> comDescriptorDirectory_;
		unique_ptr<DebugDirectory> debugDirectory_;
		unique_ptr<DelayImportDirectory> delayImportDirectory_;
		unique_ptr<DosHeader> dosHeader_;
		unique_ptr<ExceptionDirectory> exceptionDirectory_;
		unique_ptr<ExportDirectory> exportDirectory_;
		unique_ptr<GlobalptrDirectory> globalptrDirectory_;
		unique_ptr<IatDirectory> iatDirectory_;
		unique_ptr<ImportDirectory> importDirectory_;
		unique_ptr<LoadConfigDirectory> loadConfigDirectory_;
		unique_ptr<NtHeader> ntHeader_;
		unique_ptr<RelocDirectory> relocDirectory_;
		unique_ptr<ResourceDirectory> resourceDirectory_;
		unique_ptr<SectionHeaders> sectionHeaders_;
		unique_ptr<SecurityDirectory> securityDirectory_;
		unique_ptr<TlsDirectory> tlsDirectory_;

		unsigned char* base_;
		ImageType imageType_;
		bool isPe_;
		bool isMapped_;
		bool hasNtHeader32_;
	};

}  // namespace PeDecoder
