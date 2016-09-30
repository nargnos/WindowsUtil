#pragma once
#include <mutex>
#include "PeImageFwd.h"
#include "ImageType.h"
#include "DataDirectoryEntryType.h"
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
		const unique_ptr<DosHeader>& GetDosHeader() const;
		const unique_ptr<NtHeader>& GetNtHeader() const;
		const unique_ptr<SectionHeaders>& GetSections() const;

		bool HasDirectory(DataDirectoryEntryType index);
		PIMAGE_DATA_DIRECTORY GetDirectoryEntry(DataDirectoryEntryType index);
		DWORD RvaToOffset(DWORD rva);
		ULONGLONG RvaToOffset(ULONGLONG rva);
		DWORD OffsetToRva(DWORD fileOffset);
		PVOID RvaToDataPtr(DWORD rva);
		PVOID RvaToDataPtr(ULONGLONG rva);
		

	protected:
		PeImage(const PeImage&) = delete;
		PeImage& operator=(const PeImage&) = delete;

		mutable unique_ptr<DosHeader> dosHeader_;
		mutable unique_ptr<NtHeader> ntHeader_;
		mutable unique_ptr<SectionHeaders> sectionHeaders_;

		unsigned char* base_;
		mutable _STD once_flag sectionInit_;
		ImageType imageType_;
		bool isPe_;
		bool isMapped_;
		bool hasNtHeader32_;
	};

}  // namespace PeDecoder
