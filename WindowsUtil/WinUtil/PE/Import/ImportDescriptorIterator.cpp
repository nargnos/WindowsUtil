#include "ImportDirectory.h"

PE::ImportDescriptorIterator::ImportDescriptorIterator(ImportDirectory & importDirectory) :importDirectory(importDirectory)
{

}

PE::ImportDescriptorIterator::~ImportDescriptorIterator() {}

bool PE::ImportDescriptorIterator::Next()
{
	if (importDirectory.size)
	{
		if (++currentIndex < *importDirectory.size)
		{
			auto checkResult = importDirectory.data[currentIndex];
			canCreateIterator = !(checkResult.Name == NULL || checkResult.FirstThunk == NULL);
			return canCreateIterator;
		}
	}
	canCreateIterator = false;
	return false;
}

void PE::ImportDescriptorIterator::Reset()
{
	currentIndex = -1;
}

PIMAGE_IMPORT_DESCRIPTOR PE::ImportDescriptorIterator::Current()
{
	assert(currentIndex > 0 && currentIndex < *importDirectory.size);
	return &importDirectory.data[currentIndex];
}
