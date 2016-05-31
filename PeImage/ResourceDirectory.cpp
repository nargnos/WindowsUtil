#include "stdafx.h"
#include "ResourceDirectory.h"
#include "ResourceEntryIterator.h"
#include "ResourceUtil.h"
namespace PeDecoder
{
	ResourceEntryIterator ResourceDirectory::begin()
	{
		return ResourceEntryIterator(GetPtr(), LocateFirstEntry(GetPtr()));
	}

	ResourceEntryIterator ResourceDirectory::end()
	{
		return ResourceEntryIterator(GetPtr(), LocateFirstEntry(GetPtr()) + GetNumberOfEntries(GetPtr()));
	}
}  // namespace PeDecoder
