#include "stdafx.h"
#include "DelayImportDirectory.h"
#include "DelayImportDirectoryIterator.h"
namespace PeDecoder
{
	DelayImportDirectory::DelayImportDirectory(PeImage & pe, TDataPtr ptr, TSizePtr sizePtr) :
		DirectoryBase(pe, ptr, sizePtr)
	{
	}
	DelayImportDirectory::iterator DelayImportDirectory::begin()
	{
		return iterator(*this, GetPtr());
	}
	DelayImportDirectory::iterator DelayImportDirectory::end()
	{
		return iterator(*this, nullptr);
	}
}  // namespace PeDecoder
