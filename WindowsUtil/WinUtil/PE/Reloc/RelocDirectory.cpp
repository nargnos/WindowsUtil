#include "RelocDirectory.h"

PE::RelocDirectory::RelocDirectory(PeDecoder* pe) :DataDirectoryBase(pe)
{
	canCreateIterator = true;
}

PE::RelocDirectory::~RelocDirectory()
{
}
