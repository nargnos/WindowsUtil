#include "DelayImportDirectory.h"

PE::DelayImportDirectory::DelayImportDirectory(PeDecoder & pe) :DataDirectoryBase(pe)
{
	canCreateIterator = true;
}

PE::DelayImportDirectory::~DelayImportDirectory()
{
}

PImgDelayDescr PE::DelayImportDirectory::GetValue()
{
	return data;
}
