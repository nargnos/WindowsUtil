#pragma once
#include "PeDecoder.h"

namespace PE
{
	// ½Ú¶ÁÈ¡Æ÷
	class SectionReader
	{
	public:
		SectionReader(PIMAGE_SECTION_HEADER firstSectionHeader, PIMAGE_SECTION_HEADER lastSectionHeader);
		SectionReader(PIMAGE_SECTION_HEADER firstSectionHeader, WORD sectionCount);
		SectionReader(PeDecoder& pe);
		~SectionReader();
		PIMAGE_SECTION_HEADER Current();
		bool Next();
		void Reset();
	private:
		PIMAGE_SECTION_HEADER firstSectionHeader;
		PIMAGE_SECTION_HEADER lastSectionHeader;
		PIMAGE_SECTION_HEADER sectionPointer;
	};
}