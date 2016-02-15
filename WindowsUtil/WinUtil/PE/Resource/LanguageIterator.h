#pragma once
#include "ResourceDataIterator.h"
namespace PE
{
	class ResourceNameIterator;
	class LanguageIterator
	{
	public:

		explicit LanguageIterator(ResourceNameIterator* resourceDirectoryResourceNameIterator);

		~LanguageIterator();
	};
}  // namespace PE
