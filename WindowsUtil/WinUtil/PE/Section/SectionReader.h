#pragma once
#include "..\PeDecoder.h"
namespace PE
{
	namespace Section 
	{
		// ½Ú¶ÁÈ¡Æ÷
		class SectionReader
		{
		public:
			SectionReader(PIMAGE_SECTION_HEADER firstSectionHeader, WORD sectionCount);
			SectionReader(PeDecoder& pe);
			SectionReader(SectionReader& sr) = delete;
			~SectionReader() = default;
			PIMAGE_SECTION_HEADER Current();
			PIMAGE_SECTION_HEADER operator[](int index);
			bool Next();
			void Reset();

		private:
			PIMAGE_SECTION_HEADER firstSectionHeader;
			PIMAGE_SECTION_HEADER lastSectionHeader;
			PIMAGE_SECTION_HEADER currentSectionPointer;
		};
	}
}