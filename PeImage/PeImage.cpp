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
		isMapped_(isMapped)
	{
		assert(ptr);
		isPe_ = false;
		imageType_ = ImageType::UnKnown;
		auto dosHeaderPtr = reinterpret_cast<PIMAGE_DOS_HEADER>(base_);
		// 验证dosheader
		dosHeader_ = make_unique<DosHeader>(dosHeaderPtr);
		if (!dosHeader_->IsValid())
		{
			return;
		}
		// 验证ntheader

		ntHeader_ = make_unique<NtHeader>(GetNtHeaderPtr(dosHeaderPtr));
		if (!ntHeader_->IsValid())
		{
			return;
		}

		// 设置映像类型
		switch (ntHeader_->GetHeaderType())
		{
		case PeDecoder::NtHeaderType::NtHeader32:
			imageType_ = ImageType::PE32;
			break;
		case PeDecoder::NtHeaderType::NtHeader64:
			imageType_ = ImageType::PE64;
			break;
		default:
			break;
		}
		// 检测成功
		isPe_ = true;
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

	const unique_ptr<DosHeader>& PeImage::GetDosHeader()
	{
		assert(IsPe());
		return dosHeader_;
	}

	const unique_ptr<NtHeader>& PeImage::GetNtHeader()
	{
		assert(IsPe());
		return ntHeader_;
	}

	const unique_ptr<SectionHeaders>& PeImage::GetSections()
	{
		assert(IsPe());
		if (!sectionHeaders_ && IsPe())
		{
			switch (ntHeader_->GetHeaderType())
			{
			case NtHeaderType::NtHeader32:
			{
				auto tmpHeader = ntHeader_->GetRawPtr32();
				sectionHeaders_ = make_unique<SectionHeaders>(
					IMAGE_FIRST_SECTION(tmpHeader),
					&tmpHeader->FileHeader.NumberOfSections,
					&tmpHeader->OptionalHeader.SectionAlignment
					);
			}
			break;
			case NtHeaderType::NtHeader64:
			{
				auto tmpHeader = ntHeader_->GetRawPtr64();
				sectionHeaders_ = make_unique<SectionHeaders>(
					IMAGE_FIRST_SECTION(tmpHeader),
					&tmpHeader->FileHeader.NumberOfSections,
					&tmpHeader->OptionalHeader.SectionAlignment
					);
			}
			break;
			default:
				assert(false);
				__assume(false);
				break;
			}
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
	void * PeImage::GetNtHeaderPtr(const PIMAGE_DOS_HEADER dosHeader)
	{
		return reinterpret_cast<unsigned char*>(dosHeader) + dosHeader->e_lfanew;
	}

}  // namespace PeDecoder
