#pragma once
#include "../Common/Common.h"
namespace PE
{
		// ½Ú¶ÁÈ¡Æ÷
		template<typename _Section>
		class SectionIterator:
			public IIterator<PIMAGE_SECTION_HEADER>
		{
			_Section& section;
			PIMAGE_SECTION_HEADER firstSectionHeader;
			PIMAGE_SECTION_HEADER lastSectionHeader;
			PIMAGE_SECTION_HEADER currentSectionPointer;
		public:
			SectionIterator(_Section& section):section(section)
			{
				Reset();
			}
			
			~SectionIterator() = default;

			PIMAGE_SECTION_HEADER Current()
			{
				return currentSectionPointer;
			}
			PIMAGE_SECTION_HEADER operator[](int index)
			{
				auto result = firstSectionHeader + index;
				if (result < lastSectionHeader)
				{
					return result;
				}
				return NULL;
			}
			bool Next()
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
			void Reset()
			{
				currentSectionPointer = NULL;
				firstSectionHeader = section.firstSectionHeader;
				lastSectionHeader = section.lastSectionHeader;
			}

		};
	
}