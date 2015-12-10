#pragma once
#include "../Common/Common.h"
namespace PE
{
	class LanguageIterator;
	class ResourceDataIterator
	{
	public:
		ResourceDataIterator(LanguageIterator& resourceDirectoryLanguageIterator);
		~ResourceDataIterator();
	};

}