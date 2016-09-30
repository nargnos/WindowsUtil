#pragma once
#include "PeImageFwd.h"
#include "DataPtr.h"
#include "DosStub.h"
namespace PeDecoder
{
	class DosHeader :
		public Detail::DataPtr<PIMAGE_DOS_HEADER>
	{
	public:
		using DataPtr::DataPtr;
		~DosHeader() = default;
		static bool Valid(const TDataPtr ptr);
		static void* GetNtHeaderPtr(const PIMAGE_DOS_HEADER dosHeader);
		const unique_ptr<DosStub>& GetDosStub();

	protected:
		unique_ptr<DosStub> dosStub_;
	};
}  // namespace PeDecoder
