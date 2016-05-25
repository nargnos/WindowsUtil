#pragma once
#include "PeImageFwd.h"
#include "DataPtr.h"

namespace PeDecoder
{
	class DosHeader:
		public DataPtr<PIMAGE_DOS_HEADER>
	{
	public:
		explicit DosHeader(TDataPtr ptr);
		~DosHeader() = default;
		bool IsValid() const;
		const unique_ptr<DosStub>& GetDosStub();
		
	protected:
		unique_ptr<DosStub> dosStub_;
	};
}  // namespace PeDecoder
