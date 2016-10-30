#include "stdafx.h"
#include "RelocDirectoryIterator.h"
#include "RelocDirectory.h"
namespace PeDecoder
{
	RelocDirectoryIterator::RelocDirectoryIterator(RelocDirectory & relocDirectory, PIMAGE_BASE_RELOCATION ptr) :
		store_(relocDirectory, ptr)
	{
	}

	bool RelocDirectoryIterator::Equal(const RelocDirectoryIterator & val) const
	{
		return val.GetStore().relocDirectory_ == GetStore().relocDirectory_ &&
			GetStore().ptr_ == val.GetStore().ptr_;
	}

	void RelocDirectoryIterator::Increment()
	{
		assert(InRange());
		GetStore().ptr_ = PIMAGE_BASE_RELOCATION((unsigned char*)GetStore().ptr_ + GetStore().ptr_->SizeOfBlock);
	}

	RelocDirectoryIterator::reference RelocDirectoryIterator::Dereference()
	{
		assert(InRange());
		return GetStore();
	}

	bool RelocDirectoryIterator::InRange() const
	{
		auto beginPtr = GetStore().relocDirectory_->GetPtr();
		auto endPtr = reinterpret_cast<PIMAGE_BASE_RELOCATION>(reinterpret_cast<char*>(beginPtr) + GetStore().relocDirectory_->GetSize());
		return GetStore().ptr_ >= beginPtr && GetStore().ptr_ < endPtr;
	}

	const BaseRelocation & RelocDirectoryIterator::GetStore() const
	{
		return store_;
	}

	BaseRelocation & RelocDirectoryIterator::GetStore()
	{
		return store_;
	}

}  // namespace PeDecoder
