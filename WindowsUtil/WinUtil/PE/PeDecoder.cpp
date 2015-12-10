#include "Common\Common.h"
namespace PE
{
#define ALIGN_UP(value, alignment) ((UINT)(value + alignment - 1)&~(alignment - 1))

	bool PeDecoder::IsMapped()
	{
		return isMapped;
	}
	bool PeDecoder::LoadPEImage(PVOID base, bool isMapped)
	{
		isPE = false;
		Clear();
		if (!base)
		{
			return false;
		}

		this->base = reinterpret_cast<PBYTE>(base);
		this->isMapped = isMapped;
		// 载入头
		dosHeader = _STD make_shared<DosHeader>(*this);
		ntHeader = _STD make_shared<NtHeader>(*this);

		// 检查pe格式
		if (!dosHeader->VerifyDosSignature() || !ntHeader->VerifyNtSignature())
		{
			return false;
		}
		// 初始化nt头
		if (!ntHeader->Init())
		{
			return false;
		}
		this->hasNtHeader32 = ntHeader->HasNtHeader32();
		section = _STD make_shared<SectionHeaders>(*this);
		

		isPE = true;
		return true;
	}

	PVOID PeDecoder::GetBase()
	{
		return this->base;
	}
	PeDecoder::PeDecoder()
	{
		Clear();
	}
	void PeDecoder::Clear()
	{
		dosHeader = NULL;
		ntHeader = NULL;
		section = NULL;

		relocDirectory = NULL;
		exportDirectory = NULL;
		importDirectory = NULL;
		resource = NULL;
		exception = NULL;
		security = NULL;
		debug = NULL;
		architecture = NULL;
		globalptr = NULL;
		tls = NULL;
		loadConfig = NULL;
		boundImport = NULL;
		iat = NULL;
		delayImport = NULL;
		comDescriptor = NULL;
	}

	_STD shared_ptr<DosHeader> PeDecoder::GetDosHeader()
	{
		return dosHeader;
	}
	_STD shared_ptr<NtHeader> PeDecoder::GetNtHeader()
	{
		return ntHeader;
	}
	_STD shared_ptr<SectionHeaders> PeDecoder::GetSection()
	{
		return section;
	}
	_STD shared_ptr<RelocDirectory> PeDecoder::GetReloc()
	{
		if (!relocDirectory)
		{
			relocDirectory = _STD make_shared<RelocDirectory>(*this);
		}
		return relocDirectory;
	}
	_STD shared_ptr<ExportDirectory> PeDecoder::GetExport()
	{
		if (!exportDirectory)
		{
			exportDirectory = _STD make_shared<ExportDirectory>(*this);
		}
		return exportDirectory;
	}
	_STD shared_ptr<ImportDirectory> PeDecoder::GetImport()
	{
		if (!importDirectory)
		{
			importDirectory = _STD make_shared<ImportDirectory>(*this);
		}
		return importDirectory;
	}
	_STD shared_ptr<ResourceDirectory> PeDecoder::GetResource()
	{
		if (!resource)
		{
			resource = _STD make_shared<ResourceDirectory>(*this);
		}
		return resource;
	}
	_STD shared_ptr<EntryExceptionDirectory> PeDecoder::GetException()
	{
		if (!exception)
		{
			exception = _STD make_shared<EntryExceptionDirectory>(*this);
		}
		return exception;
	}
	_STD shared_ptr<SecurityDirectory> PeDecoder::GetSecurity()
	{
		if (!security)
		{
			security = _STD make_shared<SecurityDirectory>(*this);
		}
		return security;
	}
	_STD shared_ptr<DebugDirectory> PeDecoder::GetDebug()
	{
		if (!debug)
		{
			debug = _STD make_shared<DebugDirectory>(*this);
		}
		return debug;
	}
	_STD shared_ptr<ArchitectureDirectory> PeDecoder::GetArchitecture()
	{
		if (!architecture)
		{
			architecture = _STD make_shared<ArchitectureDirectory>(*this);
		}
		return architecture;
	}
	_STD shared_ptr<GlobalptrDirectory> PeDecoder::GetGlobalptr()
	{
		if (!globalptr)
		{
			globalptr = _STD make_shared<GlobalptrDirectory>(*this);
		}
		return globalptr;
	}
	_STD shared_ptr<TlsDirectory> PeDecoder::GetTls()
	{
		if (!tls)
		{
			tls = _STD make_shared<TlsDirectory>(*this);
		}
		return tls;
	}
	_STD shared_ptr<LoadConfigDirectory> PeDecoder::GetLoadConfig()
	{
		if (!loadConfig)
		{
			loadConfig = _STD make_shared<LoadConfigDirectory>(*this);
		}
		return loadConfig;
	}
	_STD shared_ptr<BoundImportDirectory> PeDecoder::GetBoundImport()
	{
		if (!boundImport)
		{
			boundImport = _STD make_shared<BoundImportDirectory>(*this);
		}
		return boundImport;
	}
	_STD shared_ptr<IatDirectory> PeDecoder::GetIat()
	{
		if (!iat)
		{
			iat = _STD make_shared<IatDirectory>(*this);
		}
		return iat;
	}

	_STD shared_ptr<DelayImportDirectory> PeDecoder::GetDelayImport()
	{
		if (!delayImport)
		{
			delayImport = _STD make_shared<DelayImportDirectory>(*this);
		}
		return delayImport;
	}

	_STD shared_ptr<ComDescriptorDirectory> PeDecoder::GetComDescriptor()
	{
		if (!comDescriptor)
		{
			comDescriptor = _STD make_shared<ComDescriptorDirectory>(*this);
		}
		return comDescriptor;
	}
	bool PeDecoder::HasNtHeader32()
	{
		return hasNtHeader32;
	}
	bool PeDecoder::IsPE()
	{
		return isPE;
	}

	PIMAGE_SECTION_HEADER PeDecoder::RvaToSection(DWORD rva)
	{
		auto currentSection = section->firstSectionHeader;
		while (currentSection < section->lastSectionHeader)
		{
			if (rva < currentSection->VirtualAddress +
				ALIGN_UP((UINT)(currentSection->Misc.VirtualSize), (UINT)(*section->sectionAlignment)))
			{
				return rva < currentSection->VirtualAddress ? NULL : currentSection;
			}
			currentSection++;
		}
		return NULL;
	}
	PIMAGE_SECTION_HEADER PeDecoder::OffsetToSection(DWORD fileOffset)
	{
		auto currentSection = section->firstSectionHeader;
		while (currentSection < section->lastSectionHeader)
		{
			if (fileOffset < currentSection->PointerToRawData + currentSection->SizeOfRawData)
			{
				return fileOffset < currentSection->PointerToRawData ? NULL : currentSection;
			}
			currentSection++;
		}
		return NULL;
	}
	DWORD PeDecoder::RvaToOffset(DWORD rva)
	{
		if (!rva)
		{
			return 0;
		}
		IMAGE_SECTION_HEADER *section = RvaToSection(rva);
		if (section == NULL)
		{
			return rva;
		}
		return rva - section->VirtualAddress + section->PointerToRawData;
	}

	DWORD PeDecoder::OffsetToRva(DWORD fileOffset)
	{
		if (fileOffset)
		{
			IMAGE_SECTION_HEADER *section = OffsetToSection(fileOffset);
			if (section != NULL)
			{
				return fileOffset - section->PointerToRawData + section->VirtualAddress;
			}
		}
		return 0;
	}
	PVOID PeDecoder::GetRvaData(DWORD rva)
	{
		return base + (isMapped ? rva : RvaToOffset(rva));
	}




	PIMAGE_DATA_DIRECTORY PeDecoder::GetDataDirectory(DWORD index)
	{
		if (*ntHeader->imageDataDirectorySize > index && IMAGE_NUMBEROF_DIRECTORY_ENTRIES > index)
		{
			return &ntHeader->imageDataDirectoryEntry[index];
		}
		return NULL;
	}

	PVOID PeDecoder::DirectoryEntryToData(DWORD index, PDWORD* size)
	{
		auto dir = GetDataDirectory(index);
		if (!dir || dir->VirtualAddress == NULL)
		{
			return NULL;
		}
		if (size)
		{
			*size = &dir->Size;
		}
		return GetRvaData(dir->VirtualAddress);
	}
}