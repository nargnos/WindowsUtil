#pragma once
#include "PeImageFwd.h"
namespace PeDecoder
{
	class DelayImportDescriptor
	{
	public:
		using Thunk32 = ImportThunk<PIMAGE_THUNK_DATA32>;
		using Thunk64 = ImportThunk<PIMAGE_THUNK_DATA64>;

		friend class DelayImportDirectoryIterator;
		DelayImportDescriptor(DelayImportDirectory& delayImportDirectory, PImgDelayDescr ptr);

		Thunk32 GetThunk32() const;
		Thunk64 GetThunk64() const;
		PCHAR GetName();
		PImgDelayDescr GetPtr() const;
	private:
		PImgDelayDescr dataPtr_;
		DelayImportDirectory* delayImportDirectory_;
	};
}  // namespace PeDecoder

