#pragma once
#include "PeImageFwd.h"

namespace PeDecoder
{
	class PeImage
	{
	public:
		PeImage(void* ptr, bool isMapped);
		~PeImage();
		// ÊÇ·ñÊÇÓ³ÉäµÄ
		bool IsMapped() const;
		bool IsPe() const;
		void* GetBase() const;
		const unique_ptr<DosHeader>& GetDosHeader();
		const unique_ptr<NtHeader>& GetNtHeader();
		const unique_ptr<SectionHeaders>& GetSections();
		const unique_ptr<ExportDirectory>& GetExportDirectory();
		DWORD RvaToOffset(DWORD rva);
		DWORD OffsetToRva(DWORD fileOffset);
		PVOID RvaToDataPtr(DWORD rva);
		static void* GetNtHeader(const PIMAGE_DOS_HEADER dosHeader);
	protected:
		PeImage(const PeImage&) = delete;
		PeImage& operator=(const PeImage&) = delete;
		


		bool isPe_;
		unsigned char* base_;
		bool isMapped_;
		bool hasNtHeader32_;
		unique_ptr<DosHeader> dosHeader_;
		unique_ptr<NtHeader> ntHeader_;
		unique_ptr<SectionHeaders> sectionHeaders_;
		unique_ptr<ExportDirectory> exportDirectory_;
	};

}  // namespace PeDecoder
