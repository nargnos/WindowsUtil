#include "SectionReader.h"
namespace PE
{
	// ½Ú¶ÁÈ¡Æ÷
	SectionReader::SectionReader(PIMAGE_SECTION_HEADER firstSectionHeader, PIMAGE_SECTION_HEADER lastSectionHeader) :
		firstSectionHeader(firstSectionHeader),
		lastSectionHeader(lastSectionHeader)
	{
		Reset();
	}
	SectionReader::SectionReader(PIMAGE_SECTION_HEADER firstSectionHeader, WORD sectionCount) :
		SectionReader(firstSectionHeader, firstSectionHeader + sectionCount)
	{
	}
	SectionReader::SectionReader(PeDecoder& pe) : SectionReader(pe.GetFirstSectionHeader(), *pe.GetNumberOfSection())
	{
	}
	SectionReader::~SectionReader(){}
	PIMAGE_SECTION_HEADER SectionReader::Current()
	{
		return sectionPointer;
	}
	bool SectionReader::Next()
	{
		if (sectionPointer)
		{
			auto tmpSectionPointer = sectionPointer + 1;
			if (tmpSectionPointer != lastSectionHeader)
			{
				sectionPointer = tmpSectionPointer;
			}
			else
			{
				return false;
			}
		}
		else
		{
			sectionPointer = firstSectionHeader;
		}
		return true;
	}
	void SectionReader::Reset()
	{
		sectionPointer = NULL;
	}
}