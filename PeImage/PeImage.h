#pragma once
#include <windows.h>
#include <WinBase.h>
#include <cassert>
#include <memory>
#include <mutex>
#include "ImageType.h"
#include "IPeImage.h"
#include "IDosHeader.h"
#include "INtHeader.h"
#include "ISectionHeaders.h"

namespace PeDecoder
{
	// UNDONE: 等重定位的相关类完善后再写修改pe的部分，还需要补充那些不常用的解析类，写完再写载入pe运行的部分

	class PeImage :
		public IPeImage
	{
	public:
		static _STD shared_ptr<PeImage> Create(void* peptr, bool isMapped);

		static ImageType NtHeaderTypeToImageType(NtHeaderType type);

		virtual bool IsPe() const;
		explicit operator bool() const;
		virtual void* GetBase() const;
		// 必存在结构
		virtual const unique_ptr<IDosHeader>& GetDosHeader() const;
		virtual const unique_ptr<INtHeader>& GetNtHeader() const;
		virtual const unique_ptr<ISectionHeaders>& GetSections() const;

		virtual DWORD OffsetToRva(DWORD fileOffset) const;

		virtual bool HasDirectory(DataDirectoryEntryType index) const;

		virtual bool IsMapped() const override;
		virtual ImageType GetImageType() const override;
		virtual PIMAGE_DATA_DIRECTORY GetDirectoryEntry(DataDirectoryEntryType index) const override;

		virtual PVOID RvaToDataPtr(DWORD rva) const override;
		virtual PVOID RvaToDataPtr(ULONGLONG rva) const override;

	protected:
		PeImage(void* ptr, bool isMapped);
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
