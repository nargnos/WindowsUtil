#include "ResourceDirectory.h"

PE::ResourceNameIterator::ResourceNameIterator(TypeIterator& resourceDirectoryTypeIterator)
{
}

PE::ResourceNameIterator::~ResourceNameIterator()
{
}

PIMAGE_RESOURCE_DIRECTORY_ENTRY PE::ResourceNameIterator::Current()
{
	return currentResourceNameDirectoryEntry;
}

bool PE::ResourceNameIterator::Next()
{
	if (currentResourceNameDirectoryEntry)
	{
		if (++currentResourceNameDirectoryEntry < lastResourceNameDirectoryEntry)
		{
			return true;
		}
	}
	else
	{
		if (firstResourceNameDirectoryEntry)
		{
			currentResourceNameDirectoryEntry = firstResourceNameDirectoryEntry;
			return true;
		}
	}
	return false;
}

void PE::ResourceNameIterator::Reset()
{
	currentResourceNameDirectoryEntry = NULL;
}
