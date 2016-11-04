#include "stdafx.h"
#include "ImportDescriptor.h"
#include "ImportDirectory.h"
#include "PeImage.h"
#include "ImportThunk.h"

namespace PeDecoder
{
	ImportDescriptor::ImportDescriptor(ImportDirectory & importDirectory, PIMAGE_IMPORT_DESCRIPTOR ptr) :
		importDirectory_(&importDirectory),
		dataPtr_(ptr)
	{
	}
	ImportDescriptor::Thunk32 ImportDescriptor::GetThunk32() const
	{
		assert(GetPtr());
		auto& util = importDirectory_->GetUtil();
		auto peType = util.GetImageType();
		assert(peType == ImageType::PE32);
		auto originalThunk = reinterpret_cast<PIMAGE_THUNK_DATA32>(util.RvaToDataPtr(GetPtr()->OriginalFirstThunk));
		auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA32>(util.RvaToDataPtr(GetPtr()->FirstThunk));

		return Thunk32(importDirectory_->GetUtil(),thunk, originalThunk);
	}
	ImportDescriptor::Thunk64 ImportDescriptor::GetThunk64() const
	{
		assert(GetPtr());
		auto& util = importDirectory_->GetUtil();
		auto peType = util.GetImageType();
		assert(peType == ImageType::PE64);
		auto originalThunk = reinterpret_cast<PIMAGE_THUNK_DATA64>(util.RvaToDataPtr(GetPtr()->OriginalFirstThunk));
		auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA64>(util.RvaToDataPtr(GetPtr()->FirstThunk));

		return Thunk64(importDirectory_->GetUtil(),thunk, originalThunk);
	}
	PCHAR ImportDescriptor::GetName() const
	{
		assert(GetPtr());
		return reinterpret_cast<PCHAR>(importDirectory_->GetUtil().RvaToDataPtr(GetPtr()->Name));
	}
	PIMAGE_IMPORT_DESCRIPTOR ImportDescriptor::GetPtr() const
	{
		return dataPtr_;
	}
}  // namespace PeDecoder

