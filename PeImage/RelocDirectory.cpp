#include "stdafx.h"
#include "RelocDirectory.h"
#include "RelocDirectoryIterator.h"
namespace PeDecoder
{
	RelocDirectory::iterator RelocDirectory::begin()
	{
		return iterator(*this, GetPtr());
	}
	RelocDirectory::iterator RelocDirectory::end()
	{
		return iterator(*this, reinterpret_cast<PIMAGE_BASE_RELOCATION>(reinterpret_cast<char*>(GetPtr()) + GetSize()));
	}
}  // namespace PeDecoder
