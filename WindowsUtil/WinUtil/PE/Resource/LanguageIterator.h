#pragma once
#include "ResourceDataIterator.h"
namespace PE
{
	class ResourceNameIterator;
	class LanguageIterator
	{
	public:

		LanguageIterator(ResourceNameIterator& resourceDirectoryResourceNameIterator);

		~LanguageIterator();
	};
}
