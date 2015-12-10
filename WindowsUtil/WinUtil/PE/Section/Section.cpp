#include "Section.h"

PE::SectionHeaders::SectionHeaders(PeDecoder & pe) :PeStructBase(pe)
{
	assert(peDecoder.GetNtHeader()->IsInit());
	if (peDecoder.GetNtHeader()->HasNtHeader32())
	{
		auto header32 = peDecoder.GetNtHeader()->GetNtHeader32();
		sectionAlignment = &header32->OptionalHeader.SectionAlignment;
		firstSectionHeader = IMAGE_FIRST_SECTION(header32);
		sectionCount = &header32->FileHeader.NumberOfSections;
	}
	else
	{
		auto header64 = peDecoder.GetNtHeader()->GetNtHeader64();
		sectionAlignment = &header64->OptionalHeader.SectionAlignment;
		firstSectionHeader = IMAGE_FIRST_SECTION(header64);
		sectionCount = &header64->FileHeader.NumberOfSections;
	}
	lastSectionHeader = firstSectionHeader + *sectionCount;
	canCreateIterator = true;
}

PE::SectionHeaders::~SectionHeaders()
{
}
