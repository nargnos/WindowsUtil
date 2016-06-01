#include "stdafx.h"
#include "BaseRelocation.h"
#include "TypeOffsetIterator.h"
#include "RelocDirectory.h"
#include "GetRelocPtr.h"
namespace PeDecoder
{
	BaseRelocation::BaseRelocation(RelocDirectory & relocDirectory, PIMAGE_BASE_RELOCATION ptr) :
		relocDirectory_(&relocDirectory),
		ptr_(ptr)
	{
	}

	
	BaseRelocation::interator BaseRelocation::begin()
	{
		return interator(relocDirectory_->GetPe(), ptr_, GetBeginPtr(ptr_));
	}

	BaseRelocation::interator BaseRelocation::end()
	{
		return interator(relocDirectory_->GetPe(), ptr_, GetEndPtr(ptr_));
	}
	PIMAGE_BASE_RELOCATION BaseRelocation::GetPtr() const
	{
		return ptr_;
	}
	DWORD BaseRelocation::GetCount() const
	{
		return GetRelocCount(GetPtr()->SizeOfBlock);
	}
}  // namespace PeDecoder
