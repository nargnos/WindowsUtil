#pragma once
#include "../Common/Common.h"
namespace PE
{
	class LanguageIterator;
	class ResourceDataIterator
	{
	public:
		explicit ResourceDataIterator(LanguageIterator& resourceDirectoryLanguageIterator);
		~ResourceDataIterator();
	};

}  // namespace PE
