#pragma once
#include "ImageType.h"
#include "IDataDirectoryUtil.h"
#include "DosHeader.h"
#include "DosStub.h"
#include "NtHeader.h"
#include "NtHeader32.h"
#include "NtHeader64.h"
#include "SectionHeaders.h"

namespace PeDecoder
{
	class PeImage :
		public IDataDirectoryUtil
	{
	public:
		PeImage(void* ptr, bool isMapped);
		static ImageType NtHeaderTypeToImageType(NtHeaderType type);
		// 是否是映射的
		
		bool IsPe() const;
		explicit operator bool() const;
		void* GetBase() const;
		// 必存在结构
		const unique_ptr<DosHeader>& GetDosHeader() const;
		const unique_ptr<NtHeader>& GetNtHeader() const;
		const unique_ptr<SectionHeaders>& GetSections() const;
		unique_ptr<DosStub> GetDosStub() const;

		DWORD OffsetToRva(DWORD fileOffset) const;

		bool HasDirectory(DataDirectoryEntryType index) const;

		virtual bool IsMapped() const override;
		virtual ImageType GetImageType() const override;
		virtual PIMAGE_DATA_DIRECTORY GetDirectoryEntry(DataDirectoryEntryType index) const override;

		virtual PVOID RvaToDataPtr(DWORD rva) const override;
		virtual PVOID RvaToDataPtr(ULONGLONG rva) const override;

	protected:
		PeImage(const PeImage&) = delete;
		PeImage& operator=(const PeImage&) = delete;

		DWORD RvaToOffset(DWORD rva) const;
		ULONGLONG RvaToOffset(ULONGLONG rva) const;

		bool LoadDosHeader(PIMAGE_DOS_HEADER ptr);
		bool CheckDosHeader() const;

		bool LoadNtHeader();
		bool CheckNtHeader() const;


		unsigned char* Base() const;

		unique_ptr<DosHeader> dosHeader_;
		unique_ptr<NtHeader> ntHeader_;
		unique_ptr<SectionHeaders> sectionHeaders_;

		bool isMapped_;
	};

}  // namespace PeDecoder
