#include "RelocDirectory.h"

PE::BaseRelocationIterator::BaseRelocationIterator(RelocDirectory* reloc)
{
	assert(reloc != NULL);
	Reset();
	startReloc = reloc->data;
	endReloc = startReloc + *reloc->size / sizeof(IMAGE_BASE_RELOCATION);
}

PE::BaseRelocationIterator::~BaseRelocationIterator() {}

bool PE::BaseRelocationIterator::Next()
{
	if (!startReloc)
	{
		canCreateIterator = false;
		return false;
	}
	if (currentReloc)
	{
		auto tmpReloc = PIMAGE_BASE_RELOCATION((PUINT8)currentReloc + currentReloc->SizeOfBlock);
		if (tmpReloc < endReloc)
		{
			currentReloc = tmpReloc;
			canCreateIterator = true;
			return true;
		}
	}
	else
	{
		currentReloc = startReloc;
		canCreateIterator = true;
		return true;
	}
	canCreateIterator = false;
	return false;
}

PIMAGE_BASE_RELOCATION PE::BaseRelocationIterator::Current()
{
	return currentReloc;
}

void PE::BaseRelocationIterator::Reset()
{
	currentReloc = NULL;
}
