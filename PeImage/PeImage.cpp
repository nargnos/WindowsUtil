#include "stdafx.h"
#include "PeImage.h"
// 
#include "NtHeader.h"
#include "DosHeader.h"
#include "SectionHeaders.h"
#include "DataDirectoryEntries.h"

namespace PeDecoder
{
	PeImage::PeImage(void* ptr, bool isMapped) :
		base_(reinterpret_cast<unsigned char*>(ptr)),
		isMapped_(isMapped),
		isPe_(false),
		imageType_(ImageType::UnKnown)
	{
		if (ptr == nullptr)
		{
			return;
		}
		auto dosHeaderPtr = reinterpret_cast<PIMAGE_DOS_HEADER>(base_);

		// 验证dosheader		
		if (!DosHeader::Valid(dosHeaderPtr))
		{
			return;
		}
		dosHeader_ = make_unique<DosHeader>(dosHeaderPtr);

		// 验证ntheader
		auto ntHeaderPtr = reinterpret_cast<PIMAGE_NT_HEADERS32>(DosHeader::GetNtHeaderPtr(dosHeaderPtr));
		if (!NtHeader::Valid(ntHeaderPtr))
		{
			return;
		}
		ntHeader_ = make_unique<NtHeader>(ntHeaderPtr);

		// 设置映像类型
		static const ImageType imageTypeTable[]{ ImageType::UnKnown,ImageType::UnKnown,ImageType::PE32,ImageType::PE64 };

		auto ntHeaderType = static_cast<unsigned char>(NtHeader::GetHeaderType(ntHeaderPtr));
		assert(ntHeaderType >= 0 && ntHeaderType < sizeof(imageTypeTable));

		imageType_ = imageTypeTable[ntHeaderType];

		// 检测成功
		isPe_ = imageType_ != ImageType::UnKnown;
	}
	// 是否是映射的
	bool PeImage::IsMapped() const
	{
		return isMapped_;
	}

	bool PeImage::IsPe() const
	{
		return isPe_;
	}

	void * PeImage::GetBase() const
	{
		return base_;
	}

	ImageType PeImage::GetImageType() const
	{
		return imageType_;
	}

	const unique_ptr<DosHeader>& PeImage::GetDosHeader() const
	{
		assert(IsPe());
		return dosHeader_;
	}

	const unique_ptr<NtHeader>& PeImage::GetNtHeader() const
	{
		assert(IsPe());
		return ntHeader_;
	}

	const unique_ptr<SectionHeaders>& PeImage::GetSections() const
	{
		assert(IsPe());
		if (!sectionHeaders_ && IsPe())
		{
			_STD call_once(sectionInit_, [this]()
			{
				sectionHeaders_ = make_unique<SectionHeaders>(*this);
			});
		}
		return sectionHeaders_;
	}

	bool PeImage::HasDirectory(DataDirectoryEntryType index)
	{
		return GetNtHeader()->GetDataDirectoryEntries()->HasDirectory(index);
	}

	PIMAGE_DATA_DIRECTORY PeImage::GetDirectoryEntry(DataDirectoryEntryType index)
	{
		return GetNtHeader()->GetDataDirectoryEntries()->GetDirectoryEntry(index);
	}

	DWORD PeImage::RvaToOffset(DWORD rva)
	{
		if (rva != 0)
		{
			auto section = GetSections()->RvaToSectionHeader(rva);
			if (section != nullptr)
			{
				return rva - section->VirtualAddress + section->PointerToRawData;
			}
		}
		return 0;
	}
	ULONGLONG PeImage::RvaToOffset(ULONGLONG rva)
	{
		if (rva != 0)
		{
			auto section = GetSections()->RvaToSectionHeader(rva);
			if (section != nullptr)
			{
				return rva - section->VirtualAddress + section->PointerToRawData;
			}
		}
		return 0;
	}

	DWORD PeImage::OffsetToRva(DWORD fileOffset)
	{
		if (fileOffset != 0)
		{
			auto section = GetSections()->OffsetToSectionHeader(fileOffset);
			if (section != nullptr)
			{
				return fileOffset - section->PointerToRawData + section->VirtualAddress;
			}
		}
		return 0;
	}

	PVOID PeImage::RvaToDataPtr(DWORD rva)
	{
		return base_ + (isMapped_ ? rva : RvaToOffset(rva));
	}
	PVOID PeImage::RvaToDataPtr(ULONGLONG rva)
	{
		return base_ + (isMapped_ ? rva : RvaToOffset(rva));
	}


}  // namespace PeDecoder
