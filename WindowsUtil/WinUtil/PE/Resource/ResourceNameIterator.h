#pragma once
#include "LanguageIterator.h"
namespace PE
{
	class TypeIterator;
	class ResourceNameIterator:
		public IIterator<PIMAGE_RESOURCE_DIRECTORY_ENTRY>
	{
		PIMAGE_RESOURCE_DIRECTORY_ENTRY firstResourceNameDirectoryEntry;
		PIMAGE_RESOURCE_DIRECTORY_ENTRY lastResourceNameDirectoryEntry;
		PIMAGE_RESOURCE_DIRECTORY_ENTRY currentResourceNameDirectoryEntry;
	public:

		ResourceNameIterator(TypeIterator& resourceDirectoryTypeIterator);

		~ResourceNameIterator();

		// Í¨¹ý IIterator ¼Ì³Ð
		virtual PIMAGE_RESOURCE_DIRECTORY_ENTRY Current() override;
		virtual bool Next() override;
		virtual void Reset() override;
	};
}
