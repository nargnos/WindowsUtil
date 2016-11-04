#include "stdafx.h"
#include "DelayImportDescriptor.h"
#include "DelayImportDirectory.h"
#include "IDataDirectoryUtil.h"
#include "ImportThunk.h"

namespace PeDecoder
{
	DelayImportDescriptor::DelayImportDescriptor(DelayImportDirectory & delayImportDirectory, PImgDelayDescr ptr) :
		delayImportDirectory_(&delayImportDirectory),
		dataPtr_(ptr)
	{
	}
	DelayImportDescriptor::Thunk32 DelayImportDescriptor::GetThunk32() const
	{
		auto& util = delayImportDirectory_->GetUtil();
		auto addressTable =reinterpret_cast<PIMAGE_THUNK_DATA32>( util.RvaToDataPtr(GetPtr()->rvaIAT));
		auto nameTable = reinterpret_cast<PIMAGE_THUNK_DATA32>(util.RvaToDataPtr(GetPtr()->rvaINT));

		return Thunk32(delayImportDirectory_->GetUtil(), addressTable, nameTable);
	}
	DelayImportDescriptor::Thunk64 DelayImportDescriptor::GetThunk64() const
	{
		auto& util = delayImportDirectory_->GetUtil();
		auto addressTable = reinterpret_cast<PIMAGE_THUNK_DATA64>(util.RvaToDataPtr(GetPtr()->rvaIAT));
		auto nameTable = reinterpret_cast<PIMAGE_THUNK_DATA64>(util.RvaToDataPtr(GetPtr()->rvaINT));

		return Thunk64(delayImportDirectory_->GetUtil(), addressTable, nameTable);
	}
	PCHAR DelayImportDescriptor::GetName()
	{
		assert(GetPtr());
		return reinterpret_cast<PCHAR>(delayImportDirectory_->GetUtil().RvaToDataPtr(GetPtr()->rvaDLLName));
	}
	PImgDelayDescr DelayImportDescriptor::GetPtr() const
	{
		return dataPtr_;
	}
}  // namespace PeDecoder
