#include "SectionReader.h"
namespace PE
{
	namespace Section {

		// ½Ú¶ÁÈ¡Æ÷

		SectionReader::SectionReader(PIMAGE_SECTION_HEADER firstSectionHeader, WORD sectionCount) :
			firstSectionHeader(firstSectionHeader),
			lastSectionHeader(firstSectionHeader + sectionCount)
		{
			Reset();
		}
		SectionReader::SectionReader(PeDecoder& pe) : SectionReader(pe.firstSectionHeader, *pe.sectionCount)
		{
		}
		PIMAGE_SECTION_HEADER SectionReader::Current()
		{
			return currentSectionPointer;
		}

		PIMAGE_SECTION_HEADER SectionReader::operator[](int index)
		{
			auto result = firstSectionHeader + index;
			if (result < lastSectionHeader)
			{
				return result;
			}
			return NULL;
		}

		bool SectionReader::Next()
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
		void SectionReader::Reset()
		{
			currentSectionPointer = NULL;
		}

	}
}