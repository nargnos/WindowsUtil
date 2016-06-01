#include "stdafx.h"
#include "DelayImportDescriptor.h"
#include "DelayImportDirectory.h"
#include "PeImage.h"
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
		auto& pe = delayImportDirectory_->GetPe();
		auto addressTable =reinterpret_cast<PIMAGE_THUNK_DATA32>( pe.RvaToDataPtr(GetPtr()->rvaIAT));
		auto nameTable = reinterpret_cast<PIMAGE_THUNK_DATA32>(pe.RvaToDataPtr(GetPtr()->rvaINT));

		return Thunk32(delayImportDirectory_->GetPe(), addressTable, nameTable);
	}
	DelayImportDescriptor::Thunk64 DelayImportDescriptor::GetThunk64() const
	{
		auto& pe = delayImportDirectory_->GetPe();
		auto addressTable = reinterpret_cast<PIMAGE_THUNK_DATA64>(pe.RvaToDataPtr(GetPtr()->rvaIAT));
		auto nameTable = reinterpret_cast<PIMAGE_THUNK_DATA64>(pe.RvaToDataPtr(GetPtr()->rvaINT));

		return Thunk64(delayImportDirectory_->GetPe(), addressTable, nameTable);
	}
	PCHAR DelayImportDescriptor::GetName()
	{
		assert(GetPtr());
		return reinterpret_cast<PCHAR>(delayImportDirectory_->GetPe().RvaToDataPtr(GetPtr()->rvaDLLName));
	}
	PImgDelayDescr DelayImportDescriptor::GetPtr() const
	{
		return dataPtr_;
	}
}  // namespace PeDecoder
