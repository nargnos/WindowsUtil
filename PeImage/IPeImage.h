#pragma once
#include <memory>
#include "ImageType.h"
#include "IDirectoryManager.h"
#include "IRvaConverter.h"

namespace PeDecoder
{
	class DosHeader;
	class DosStub;
	class NtHeader;
	class SectionHeaders;

	struct IPeImage :
		public IRvaConverter, public IDirectoryManager
	{
		virtual bool IsMapped() const = 0;
		virtual bool IsPe() const = 0;
		virtual void* GetBase() const = 0;
		virtual ImageType GetImageType() const = 0;

		virtual const unique_ptr<DosHeader>& GetDosHeader() const = 0;
		virtual unique_ptr<DosStub> GetDosStub() const = 0;
		virtual const unique_ptr<NtHeader>& GetNtHeader() const = 0;
		virtual const unique_ptr<SectionHeaders>& GetSections() const = 0;
		explicit operator bool() const;
		virtual ~IPeImage() = default;
	};
}  // namespace PeDecoder