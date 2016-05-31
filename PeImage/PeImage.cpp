#include "stdafx.h"
#include "PeImage.h"
// 
#include "NtHeader.h"
#include "DosHeader.h"
#include "SectionHeaders.h"
#include "ExportDirectory.h"
#include "ArchitectureDirectory.h"
#include "BoundImportDirectory.h"
#include "ComDescriptorDirectory.h"
#include "DebugDirectory.h"
#include "DelayImportDirectory.h"
#include "ExceptionDirectory.h"
#include "ExportDirectory.h"
#include "GlobalptrDirectory.h"
#include "IatDirectory.h"
#include "ImportDirectory.h"
#include "LoadConfigDirectory.h"
#include "RelocDirectory.h"
#include "ResourceDirectory.h"
#include "SecurityDirectory.h"
#include "TlsDirectory.h"

#include "DataDirectoryEntries.h"
#include "DosStub.h"
namespace PeDecoder
{
	template<DataDirectoryEntryType index, typename TResultType>
	void MakeDataDirectory(PeImage& pe, unique_ptr<TResultType>& output)
	{
		auto entry = pe.GetNtHeader()->GetDataDirectoryEntries()->GetDirectoryEntry(index);
		if (entry->VirtualAddress != 0)
		{
			auto addr = entry->VirtualAddress;
			auto ptr = reinterpret_cast<typename DataDirectoryEntryTypeTrait<index>::Type>(pe.RvaToDataPtr(addr));
			output = make_unique<TResultType>(pe, ptr, &entry->Size);
		}
	}

	PeImage::PeImage(void* ptr, bool isMapped) :
		base_(reinterpret_cast<unsigned char*>(ptr)),
		isMapped_(isMapped)
	{
		assert(ptr);
		isPe_ = false;
		imageType_ = ImageType::UnKnown;

		// 验证dosheader
		dosHeader_ = make_unique<DosHeader>(reinterpret_cast<PIMAGE_DOS_HEADER>(base_));
		if (!dosHeader_->IsValid())
		{
			return;
		}
		// 验证ntheader
		ntHeader_ = make_unique<NtHeader>(GetNtHeader(dosHeader_->GetPtr()));
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


	const unique_ptr<ExportDirectory>& PeImage::GetExportDirectory()
	{
		if (!exportDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Export>(*this, exportDirectory_);
		}
		return exportDirectory_;
	}

	const unique_ptr<ArchitectureDirectory>& PeImage::GetArchitectureDirectory()
	{
		if (!architectureDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Architecture>(*this, architectureDirectory_);
		}
		return architectureDirectory_;
	}

	const unique_ptr<BoundImportDirectory>& PeImage::GetBoundImportDirectory()
	{
		if (!boundImportDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::BoundImport>(*this, boundImportDirectory_);
		}
		return boundImportDirectory_;
	}

	const unique_ptr<ComDescriptorDirectory>& PeImage::GetComDescriptorDirectory()
	{
		if (!comDescriptorDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::ComDescriptor>(*this, comDescriptorDirectory_);
		}
		return comDescriptorDirectory_;
	}

	const unique_ptr<DebugDirectory>& PeImage::GetDebugDirectory()
	{
		if (!debugDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Debug>(*this, debugDirectory_);
		}
		return debugDirectory_;
	}

	const unique_ptr<DelayImportDirectory>& PeImage::GetDelayImportDirectory()
	{
		if (!delayImportDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::DelayImport>(*this, delayImportDirectory_);
		}
		return delayImportDirectory_;
	}

	const unique_ptr<ExceptionDirectory>& PeImage::GetExceptionDirectory()
	{
		if (!exceptionDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Exception>(*this, exceptionDirectory_);
		}
		return exceptionDirectory_;
	}

	const unique_ptr<GlobalptrDirectory>& PeImage::GetGlobalptrDirectory()
	{
		if (!globalptrDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Globalptr>(*this, globalptrDirectory_);
		}
		return globalptrDirectory_;
	}

	const unique_ptr<IatDirectory>& PeImage::GetIatDirectory()
	{
		if (!iatDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Iat>(*this, iatDirectory_);
		}
		return iatDirectory_;
	}

	const unique_ptr<ImportDirectory>& PeImage::GetImportDirectory()
	{
		if (!importDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Import>(*this, importDirectory_);
		}
		return importDirectory_;
	}

	const unique_ptr<LoadConfigDirectory>& PeImage::GetLoadConfigDirectory()
	{
		if (!loadConfigDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::LoadConfig>(*this, loadConfigDirectory_);
		}
		return loadConfigDirectory_;
	}

	const unique_ptr<RelocDirectory>& PeImage::GetRelocDirectory()
	{
		if (!relocDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::BaseReloc>(*this, relocDirectory_);
		}
		return relocDirectory_;
	}

	const unique_ptr<ResourceDirectory>& PeImage::GetResourceDirectory()
	{
		if (!resourceDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Resource>(*this, resourceDirectory_);
		}
		return resourceDirectory_;
	}

	const unique_ptr<SecurityDirectory>& PeImage::GetSecurityDirectory()
	{
		if (!securityDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Security>(*this, securityDirectory_);
		}
		return securityDirectory_;
	}

	const unique_ptr<TlsDirectory>& PeImage::GetTlsDirectory()
	{
		if (!tlsDirectory_)
		{
			MakeDataDirectory<DataDirectoryEntryType::Tls>(*this, tlsDirectory_);
		}
		return tlsDirectory_;
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
	void * PeImage::GetNtHeader(const PIMAGE_DOS_HEADER dosHeader)
	{
		return reinterpret_cast<unsigned char*>(dosHeader) + dosHeader->e_lfanew;
	}

}  // namespace PeDecoder
