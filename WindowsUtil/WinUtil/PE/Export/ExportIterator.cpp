#include "ExportDirectory.h"

PE::ExportIterator::ExportIterator(ExportDirectory & exportDir) :exportDir(exportDir)
{
	Reset();
}

PE::ExportIterator::~ExportIterator() {}

PDWORD PE::ExportIterator::CurrentFuncRva()
{
	if (currentIndex == -1)
	{
		return NULL;
	}
	return &exportDir.funcTable[exportDir.nameOrdinalTable[currentIndex]];
}

PDWORD PE::ExportIterator::CurrentNameRva()
{
	if (currentIndex == -1)
	{
		return NULL;
	}
	return &exportDir.nameTable[currentIndex];
}

PWORD PE::ExportIterator::CurrentNameOrdinals()
{
	if (currentIndex == -1)
	{
		return NULL;
	}
	return &exportDir.nameOrdinalTable[currentIndex];
}

bool PE::ExportIterator::Next()
{
	if (exportDir.numberOfNames)
	{
		if (++currentIndex < *exportDir.numberOfNames)
		{
			return true;
		}
	}
	return false;
}

void PE::ExportIterator::Reset()
{
	currentIndex = -1;
}
