#include "PeStruct.h"

PE::PeStruct::PeStruct(PeDecoder & pe) :peDecoder(pe)
{
}

PE::PeDecoder& PE::PeStruct::GetPeDecoder()
{
	return peDecoder;
}

PE::PeStruct::~PeStruct()
{
}
