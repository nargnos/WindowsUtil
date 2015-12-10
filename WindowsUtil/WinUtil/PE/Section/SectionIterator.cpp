#include "Section.h"

PE::SectionIterator::SectionIterator(SectionHeaders & section) :section(section)
{
	Reset();
}

PIMAGE_SECTION_HEADER PE::SectionIterator::Current()
{
	return currentSectionPointer;
}
PIMAGE_SECTION_HEADER PE::SectionIterator::operator[](int index)
{
	auto result = firstSectionHeader + index;
	if (result < lastSectionHeader)
	{
		return result;
	}
	return NULL;
}
bool PE::SectionIterator::Next()
{
	if (currentSectionPointer)
	{
		if (++currentSectionPointer == lastSectionHeader)
		{
			return false;
		}
	}
	else
	{
		if (!firstSectionHeader || lastSectionHeader == firstSectionHeader)
		{
			return false;
		}
		currentSectionPointer = firstSectionHeader;
	}
	return true;
}

void PE::SectionIterator::Reset()
{
	currentSectionPointer = NULL;
	firstSectionHeader = section.firstSectionHeader;
	lastSectionHeader = section.lastSectionHeader;
}
