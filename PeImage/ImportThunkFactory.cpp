#include "stdafx.h"
#include "ImportThunkFactory.h"
#include "ImportDirectory.h"
#include "ImportThunkIterator.h"
#include "ImportThunk.h"
namespace PeDecoder
{
	using namespace std;
	ImportThunkIterator ImportThunkFactory::CreateThunkIterator(const IPeImage & util, const PIMAGE_IMPORT_DESCRIPTOR desc)
	{
		ImportThunkIterator result(util);
		if (desc != nullptr)
		{
			auto peType = util.GetImageType();
			switch (peType)
			{
			case PeDecoder::ImageType::PE32:
			{
				auto originalThunk = reinterpret_cast<PIMAGE_THUNK_DATA32>(util.RvaToDataPtr(desc->OriginalFirstThunk));
				auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA32>(util.RvaToDataPtr(desc->FirstThunk));
				result = CreateThunkIterator(util, thunk, originalThunk);
			}
			break;
			case PeDecoder::ImageType::PE64:
			{
				auto originalThunk = reinterpret_cast<PIMAGE_THUNK_DATA64>(util.RvaToDataPtr(desc->OriginalFirstThunk));
				auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA64>(util.RvaToDataPtr(desc->FirstThunk));
				result = CreateThunkIterator(util, thunk, originalThunk);
			}
			break;
			default:
				assert(false);
				break;
			}
		}
		return result;
	}
	ImportThunkIterator ImportThunkFactory::CreateDelayThunkIterator(const IPeImage & util, const PImgDelayDescr descr)
	{
		ImportThunkIterator result(util);
		if (descr != nullptr)
		{
			auto peType = util.GetImageType();
			switch (peType)
			{
			case PeDecoder::ImageType::PE32:
			{
				auto originalThunk = reinterpret_cast<PIMAGE_THUNK_DATA32>(util.RvaToDataPtr(descr->rvaINT));
				auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA32>(util.RvaToDataPtr(descr->rvaIAT));
				result = CreateThunkIterator(util, thunk, originalThunk);
			}
			break;
			case PeDecoder::ImageType::PE64:
			{
				auto originalThunk = reinterpret_cast<PIMAGE_THUNK_DATA64>(util.RvaToDataPtr(descr->rvaINT));
				auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA64>(util.RvaToDataPtr(descr->rvaIAT));
				result = CreateThunkIterator(util, thunk, originalThunk);
			}
			break;
			default:
				assert(false);
				break;
			}
		}
		return result;
	}
	ImportThunkIterator ImportThunkFactory::CreateThunkIterator(const IPeImage & util, PIMAGE_THUNK_DATA32 thunk, PIMAGE_THUNK_DATA32 originalThunk)
	{
		return ImportThunkIterator(util, thunk, originalThunk);
	}
	ImportThunkIterator ImportThunkFactory::CreateThunkIterator(const IPeImage & util, PIMAGE_THUNK_DATA64 thunk, PIMAGE_THUNK_DATA64 originalThunk)
	{
		return ImportThunkIterator(util, thunk, originalThunk);
	}
	std::unique_ptr<IImportThunk> ImportThunkFactory::CreateThunk(const IPeImage & util, PIMAGE_THUNK_DATA32 thunk, PIMAGE_THUNK_DATA32 originalThunk)
	{
		return make_unique<ImportThunk<PIMAGE_THUNK_DATA32>>(util, thunk, originalThunk);
	}

	std::unique_ptr<IImportThunk> ImportThunkFactory::CreateThunk(const IPeImage & util, PIMAGE_THUNK_DATA64 thunk, PIMAGE_THUNK_DATA64 originalThunk)
	{
		return make_unique<ImportThunk<PIMAGE_THUNK_DATA64>>(util, thunk, originalThunk);
	}

}  // namespace PeDecoder