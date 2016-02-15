#include "ImportDirectory.h"

PE::ImportDirectory::ImportDirectory(PeDecoder* pe) :DataDirectoryBase(pe)
{
	canCreateIterator = true;
}

PE::ImportDirectory::~ImportDirectory()
{
}
