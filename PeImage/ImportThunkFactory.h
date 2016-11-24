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
		static ImportThunkIterator CreateThunkIterator(const IDataDirectoryUtil & util, const PIMAGE_IMPORT_DESCRIPTOR desc);
		static ImportThunkIterator CreateDelayThunkIterator(const IDataDirectoryUtil & util, const PImgDelayDescr descr);
		static ImportThunkIterator CreateThunkIterator(const IDataDirectoryUtil & util, PIMAGE_THUNK_DATA32 thunk, PIMAGE_THUNK_DATA32 originalThunk);
		static ImportThunkIterator CreateThunkIterator(const IDataDirectoryUtil & util, PIMAGE_THUNK_DATA64 thunk, PIMAGE_THUNK_DATA64 originalThunk);
		static _STD unique_ptr<IImportThunk> CreateThunk(const IDataDirectoryUtil& util, PIMAGE_THUNK_DATA32 thunk, PIMAGE_THUNK_DATA32 originalThunk);
		static _STD unique_ptr<IImportThunk> CreateThunk(const IDataDirectoryUtil& util, PIMAGE_THUNK_DATA64 thunk, PIMAGE_THUNK_DATA64 originalThunk);

	private:
		ImportThunkFactory() = delete;
		~ImportThunkFactory() = delete;
	};

}  // namespace PeDecoder