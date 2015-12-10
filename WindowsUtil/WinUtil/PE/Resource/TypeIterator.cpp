#include "ResourceDirectory.h"

PE::TypeIterator::TypeIterator(ResourceDirectory& resourceDirectory)
{
	firstTypeDirectoryEntry = resourceDirectory.LocateFirstEntry(resourceDirectory.data);
	lastTypeDirectoryEntry = firstTypeDirectoryEntry + resourceDirectory.GetNumberOfEntries(resourceDirectory.data);
}

PE::TypeIterator::~TypeIterator()
{
}

PIMAGE_RESOURCE_DIRECTORY_ENTRY PE::TypeIterator::Current()
{
	return currentTypeDirectoryEntry;
}

bool PE::TypeIterator::Next()
{
	if (currentTypeDirectoryEntry)
	{
		if (++currentTypeDirectoryEntry < lastTypeDirectoryEntry)
		{
			canCreateIterator = true;
			return true;
		}

	}
	else
	{
		if (firstTypeDirectoryEntry)
		{
			currentTypeDirectoryEntry = firstTypeDirectoryEntry;
			canCreateIterator = true;

			return true;
		}
	}
	canCreateIterator = false;
	return false;
}

void PE::TypeIterator::Reset()
{
	currentTypeDirectoryEntry = NULL;
	canCreateIterator = false;
}

PIMAGE_RESOURCE_DIRECTORY PE::TypeIterator::GetValue()
{
	return NULL;// ResourceDirectory::LocateResourceDirectory()
}
