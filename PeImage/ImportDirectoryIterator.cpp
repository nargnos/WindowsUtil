#include "stdafx.h"
#include "ImportDirectoryIterator.h"
namespace PeDecoder
{
	ImportDirectoryIterator::ImportDirectoryIterator(ImportDirectory & importDirectory, PIMAGE_IMPORT_DESCRIPTOR ptr) :
		store_(importDirectory, ptr)
	{

	}
	bool ImportDirectoryIterator::Equal(const ImportDirectoryIterator & val) const
	{
		return val.GetStore().importDirectory_ == GetStore().importDirectory_ &&
			val.GetStore().dataPtr_ == GetStore().dataPtr_;
	}
	void ImportDirectoryIterator::Increment()
	{
		++GetStore().dataPtr_;
		if (GetStore().dataPtr_->FirstThunk == 0 || GetStore().dataPtr_->Name == 0)
		{
			// ½áÊø
			GetStore().dataPtr_ = nullptr;
		}
	}
	ImportDirectoryIterator::reference ImportDirectoryIterator::Dereference()
	{
		return GetStore();
	}
	ImportDescriptor & ImportDirectoryIterator::GetStore()
	{
		return store_;
	}
	const ImportDescriptor & ImportDirectoryIterator::GetStore() const
	{
		return store_;
	}
}  // namespace PeDecoder
