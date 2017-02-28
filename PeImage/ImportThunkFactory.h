#pragma once
#include <memory>
#include "ImportThunkIterator.h"
#include "IImportThunk.h"
namespace PeDecoder
{
	class ImportDirectory;
	class ImportThunkFactory final
	{
	public:
		static ImportThunkIterator CreateThunkIterator(const IPeImage & util, const PIMAGE_IMPORT_DESCRIPTOR desc);
		static ImportThunkIterator CreateDelayThunkIterator(const IPeImage & util, const PImgDelayDescr descr);
		static ImportThunkIterator CreateThunkIterator(const IPeImage & util, PIMAGE_THUNK_DATA32 thunk, PIMAGE_THUNK_DATA32 originalThunk);
		static ImportThunkIterator CreateThunkIterator(const IPeImage & util, PIMAGE_THUNK_DATA64 thunk, PIMAGE_THUNK_DATA64 originalThunk);
		static _STD unique_ptr<IImportThunk> CreateThunk(const IPeImage& util, PIMAGE_THUNK_DATA32 thunk, PIMAGE_THUNK_DATA32 originalThunk);
		static _STD unique_ptr<IImportThunk> CreateThunk(const IPeImage& util, PIMAGE_THUNK_DATA64 thunk, PIMAGE_THUNK_DATA64 originalThunk);

	private:
		ImportThunkFactory() = delete;
		~ImportThunkFactory() = delete;
	};

}  // namespace PeDecoder