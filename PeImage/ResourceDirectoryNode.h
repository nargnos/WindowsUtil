#pragma once
#include <Windows.h>
namespace PeDecoder
{
	class ResourceEntryIterator;
	class ResourceDirectoryNode
	{
	public:

		ResourceDirectoryNode(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY nodePtr);
		ResourceEntryIterator begin();
		ResourceEntryIterator end();
		DWORD GetEntryCount() const;
		PIMAGE_RESOURCE_DIRECTORY GetPtr();
		PIMAGE_RESOURCE_DIRECTORY_ENTRY GetFirstEntry();
	protected:
		PIMAGE_RESOURCE_DIRECTORY root_;
		PIMAGE_RESOURCE_DIRECTORY nodePtr_;
	};

}  // namespace PeDecoder
