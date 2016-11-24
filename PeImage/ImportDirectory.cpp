#include "stdafx.h"
#include "ImportDirectory.h"
#include "ImportDescriptorIterator.h"
namespace PeDecoder
{
	typename ImportDirectory::iterator ImportDirectory::begin()
	{
		return iterator(*this, GetPtr());
	}
	typename ImportDirectory::iterator ImportDirectory::end()
	{
		return iterator(*this, ImportDescriptorIterator::FindEndDescriptor(GetPtr()));
	}

}  // namespace PeDecoder
