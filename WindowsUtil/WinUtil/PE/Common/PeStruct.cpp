#include "PeStruct.h"
#include <assert.h>
PE::PeStruct::PeStruct(PeDecoder* pe) :peDecoder(pe)
{
	assert(pe != NULL);
}

PE::PeDecoder* PE::PeStruct::GetPeDecoder()
{
	return peDecoder;
}

PE::PeStruct::~PeStruct()
{
}

