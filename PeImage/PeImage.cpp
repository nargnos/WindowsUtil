#include "stdafx.h"
#include "PeImage.h"
//
#include "DataDirectoryEntries.h"
#include "NtHeader.h"
#include "DosHeader.h"
#include "SectionHeaders.h"
#include "ExportDirectory.h"
namespace PeDecoder
{
	PeImage::PeImage(void* ptr, bool isMapped) :
		base_(reinterpret_cast<unsigned char*>(ptr)),
		isMapped_(isMapped)
	{
		assert(ptr);
		dosHeader_ = make_unique<DosHeader>(reinterpret_cast<PIMAGE_DOS_HEADER>(base_));
		ntHeader_ = make_unique<NtHeader>(GetNtHeader(dosHeader_->GetPtr()));

		isPe_ = dosHeader_->IsValid() &&
			ntHeader_->IsValid() &&
			ntHeader_->GetHeaderType() != NtHeaderType::Rom &&
			ntHeader_->GetHeaderType() != NtHeaderType::UnKnown;

	}
	// ÊÇ·ñÊÇÓ³ÉäµÄ
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
	
	const unique_ptr<ExportDirectory>& PeImage::GetExportDirectory()
	{
		if (!exportDirectory_)
		{
			auto entry = GetNtHeader()->GetDataDirectoryEntries()->GetDirectoryEntry(DataDirectoryEntryType::Export);
			
		}
		return exportDirectory_;
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

	void * PeImage::GetNtHeader(const PIMAGE_DOS_HEADER dosHeader)
	{
		return reinterpret_cast<unsigned char*>(dosHeader) + dosHeader->e_lfanew;
	}

	PeImage::~PeImage()
	{
	}
}  // namespace PeDecoder
