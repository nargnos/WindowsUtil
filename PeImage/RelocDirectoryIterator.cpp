#include "stdafx.h"
#include "RelocDirectoryIterator.h"
#include "RelocDirectory.h"
namespace PeDecoder
{
	RelocDirectoryIterator::RelocDirectoryIterator(RelocDirectory & relocDirectory, PIMAGE_BASE_RELOCATION ptr) :
		store_(relocDirectory, ptr)
	{
	}

	bool RelocDirectoryIterator::equal(const RelocDirectoryIterator & val) const
	{
		return &val.GetStore().relocDirectory_ == &GetStore().relocDirectory_ &&
			GetStore().ptr_ == val.GetStore().ptr_;
	}

	void RelocDirectoryIterator::increment()
	{
		assert(InRange());
		GetStore().ptr_ = PIMAGE_BASE_RELOCATION((unsigned char*)GetStore().ptr_ + GetStore().ptr_->SizeOfBlock);
	}

	RelocDirectoryIterator::reference RelocDirectoryIterator::dereference() const
	{
		assert(InRange());
		return const_cast<reference>(GetStore());
	}

	bool RelocDirectoryIterator::InRange() const
	{
		auto beginPtr = GetStore().relocDirectory_.GetPtr();
		auto endPtr = beginPtr + GetStore().relocDirectory_.GetSize() / sizeof(IMAGE_BASE_RELOCATION);
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
