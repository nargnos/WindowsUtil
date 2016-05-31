#include "stdafx.h"
#include "ResourceDirectoryNode.h"
#include "ResourceEntryIterator.h"
#include "ResourceUtil.h"
namespace PeDecoder
{
	ResourceDirectoryNode::ResourceDirectoryNode(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY nodePtr) :
		root_(root),
		nodePtr_(nodePtr)
	{
	}

	ResourceEntryIterator ResourceDirectoryNode::begin()
	{
		return ResourceEntryIterator(root_, GetFirstEntry());
	}

	ResourceEntryIterator ResourceDirectoryNode::end()
	{
		return ResourceEntryIterator(root_, GetFirstEntry() + GetEntryCount());
	}
	DWORD ResourceDirectoryNode::GetEntryCount() const
	{
		return GetNumberOfEntries(nodePtr_);
	}
	PIMAGE_RESOURCE_DIRECTORY ResourceDirectoryNode::GetPtr()
	{
		return nodePtr_;
	}
	PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryNode::GetFirstEntry()
	{
		return LocateFirstEntry(nodePtr_);
	}
}  // namespace PeDecoder
