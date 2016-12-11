#pragma once
#include "ImageType.h"
#include "IDataDirectoryUtil.h"
#include "IDosHeader.h"
#include "INtHeader.h"
#include "ISectionHeaders.h"

namespace PeDecoder
{
	// UNDONE: 等重定位的相关类完善后再写修改pe的部分，还需要补充那些不常用的解析类，写完再写载入pe运行的部分

	class PeImage :
		public IDataDirectoryUtil
	{
	public:
		PeImage(void* ptr, bool isMapped);
		static ImageType NtHeaderTypeToImageType(NtHeaderType type);
		bool IsPe() const;
		explicit operator bool() const;
		void* GetBase() const;
		// 必存在结构
		const unique_ptr<IDosHeader>& GetDosHeader() const;
		const unique_ptr<INtHeader>& GetNtHeader() const;
		const unique_ptr<ISectionHeaders>& GetSections() const;

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

		unique_ptr<IDosHeader> dosHeader_;
		unique_ptr<INtHeader> ntHeader_;
		unique_ptr<ISectionHeaders> sectionHeaders_;

		bool isMapped_;
	};

}  // namespace PeDecoder
