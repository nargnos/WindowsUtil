#include "stdafx.h"
#include "PeImage.h"
#include "DosHeader.h"
#include "NtHeaderFactory.h"
#include "SectionHeaders.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{
	PeImage::PeImage(void* ptr, bool isMapped) :
		isMapped_(isMapped)
	{
		if (ptr == nullptr)
		{
			return;
		}

		if (!LoadDosHeader(reinterpret_cast<PIMAGE_DOS_HEADER>(ptr)))
		{
			return;
		}

		if (!LoadNtHeader())
		{
			return;
		}
		assert(ntHeader_->GetHeaderType() == NtHeaderType::NtHeader32 ||
			ntHeader_->GetHeaderType() == NtHeaderType::NtHeader64);

		sectionHeaders_ = SectionHeaders::Create(*this);
	}
	PeImage::operator bool() const
	{
		return IsPe();
	}
	// ÊÇ·ñÊÇÓ³ÉäµÄ
	bool PeImage::IsMapped() const
	{
		return isMapped_;
	}

	bool PeImage::IsPe() const
	{
		return CheckDosHeader() && CheckNtHeader();
	}

	void * PeImage::GetBase() const
	{
		return GetDosHeader()->RawPtr();
	}

	ImageType PeImage::GetImageType() const
	{
		assert(CheckDosHeader());
		assert(CheckNtHeader());

		return NtHeaderTypeToImageType(ntHeader_->GetHeaderType());
	}

	const unique_ptr<IDosHeader>& PeImage::GetDosHeader() const
	{
		assert(IsPe());
		return dosHeader_;
	}

	const unique_ptr<INtHeader>& PeImage::GetNtHeader() const
	{
		assert(IsPe());
		return ntHeader_;
	}

	const unique_ptr<ISectionHeaders>& PeImage::GetSections() const
	{
		assert(IsPe());
		return sectionHeaders_;
	}

	bool PeImage::HasDirectory(DataDirectoryEntryType index) const
	{
		return DataDirectoryEntries::HasDirectory(GetNtHeader()->GetDataDirectory(), index);
	}

	PIMAGE_DATA_DIRECTORY PeImage::GetDirectoryEntry(DataDirectoryEntryType index) const
	{
		return DataDirectoryEntries::GetDirectoryEntry(GetNtHeader()->GetDataDirectory(), index);
	}

	DWORD PeImage::RvaToOffset(DWORD rva) const
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
	ULONGLONG PeImage::RvaToOffset(ULONGLONG rva) const
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

	DWORD PeImage::OffsetToRva(DWORD fileOffset) const
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

	PVOID PeImage::RvaToDataPtr(DWORD rva) const
	{
		return Base() + (isMapped_ ? rva : RvaToOffset(rva));
	}
	PVOID PeImage::RvaToDataPtr(ULONGLONG rva) const
	{
		return Base() + (isMapped_ ? rva : RvaToOffset(rva));
	}

	bool PeImage::LoadDosHeader(PIMAGE_DOS_HEADER ptr)
	{
		dosHeader_ = DosHeader::Create(ptr);
		return CheckDosHeader();
	}

	bool PeImage::CheckDosHeader() const
	{
		return dosHeader_ && dosHeader_->IsValid();
	}

	bool PeImage::LoadNtHeader()
	{
		assert(CheckDosHeader());
		ntHeader_ = NtHeaderFactory::Create(*dosHeader_);
		return CheckNtHeader();
	}

	bool PeImage::CheckNtHeader() const
	{
		return ntHeader_ && ntHeader_->IsValid();
	}

	_STD shared_ptr<PeImage> PeImage::Create(void * peptr, bool isMapped)
	{
		_STD shared_ptr<PeImage> result(new PeImage(peptr, isMapped));
		if (!result->IsPe())
		{
			result = nullptr;
		}
		return result;
	}

	ImageType PeImage::NtHeaderTypeToImageType(NtHeaderType type)
	{
		static const ImageType imageTypeTable[]
		{ ImageType::UnKnown,ImageType::UnKnown,ImageType::PE32,ImageType::PE64 };

		auto ntHeaderType = static_cast<unsigned char>(type);
		assert(ntHeaderType >= 0 && ntHeaderType < sizeof(imageTypeTable));
		return imageTypeTable[ntHeaderType];
	}

	unsigned char * PeImage::Base() const
	{
		return reinterpret_cast<unsigned char*>(GetDosHeader()->RawPtr());
	}


}  // namespace PeDecoder
