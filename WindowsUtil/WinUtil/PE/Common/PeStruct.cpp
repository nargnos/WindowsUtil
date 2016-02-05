#include "PeStruct.h"

PE::PeStruct::PeStruct(PeDecoder & pe) :peDecoder(const_cast<PeDecoder&>(pe))
{
}

PE::PeDecoder& PE::PeStruct::GetPeDecoder()
{
	return peDecoder;
}

PE::PeStruct::~PeStruct()
{
}

