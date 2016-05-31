#include "stdafx.h"
#include "ResourceEntry.h"
#include "ResourceUtil.h"
#include "ResourceDirectoryNode.h"
namespace PeDecoder
{
	ResourceEntry::ResourceEntry(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY ptr) :
		root_(root),
		ptr_(ptr)
	{
	}
	PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceEntry::GetPtr() const
	{
		return ptr_;
	}
	bool ResourceEntry::NameIsString() const
	{
		return GetPtr()->NameIsString;
	}
	PIMAGE_RESOURCE_DIR_STRING_U ResourceEntry::GetName() const
	{
		assert(NameIsString());
		return LocateEntryName(root_, GetPtr());
	}
	WORD ResourceEntry::GetID() const
	{
		return GetPtr()->Id;
	}
	PIMAGE_RESOURCE_DIRECTORY ResourceEntry::GetRoot() const
	{
		return root_;
	}
	PIMAGE_RESOURCE_DIRECTORY ResourceEntry::GetChildDirectoryPtr() const
	{
		assert(DataIsDirectory());
		return LocateResourceDirectory(GetRoot(), GetPtr());
	}
	PIMAGE_RESOURCE_DATA_ENTRY ResourceEntry::GetDataEntryPtr() const
	{
		assert(!DataIsDirectory());
		return LocateResourceDataEntry(GetRoot(), GetPtr());
	}
	bool ResourceEntry::DataIsDirectory() const
	{
		return GetPtr()->DataIsDirectory;
	}
	ResourceDirectoryNode ResourceEntry::GetChildDirectory()
	{
		return ResourceDirectoryNode(GetRoot(), GetChildDirectoryPtr());
	}
}  // namespace PeDecoder
