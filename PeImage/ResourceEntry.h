#pragma once
#include <Windows.h>
namespace PeDecoder
{

	// Resource Directory (root) (resource 类型分组->RDE)
	//			|-> Resource Directory Entry （每个类型分组的入口->RD,紧跟前面的结构）

	//						|-> Resource Directory (按元素ID分组->RDE)
	//									|-> Resource Directory Entry （元素ID分组入口->RD）

	//												|-> Resource Directory （语言分组->Data）
	//															|-> 数据入口

	class ResourceDirectoryNode;
	class ResourceEntry
	{
	public:
		friend class ResourceEntryIterator;
		ResourceEntry(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY ptr);
		PIMAGE_RESOURCE_DIRECTORY_ENTRY GetPtr() const;
		bool NameIsString() const;
		PIMAGE_RESOURCE_DIR_STRING_U GetName() const;
		WORD GetID() const;

		PIMAGE_RESOURCE_DIRECTORY GetRoot() const;
		PIMAGE_RESOURCE_DIRECTORY GetChildDirectoryPtr() const;
		PIMAGE_RESOURCE_DATA_ENTRY GetDataEntryPtr()const;
		bool DataIsDirectory() const;
		ResourceDirectoryNode GetChildDirectory();

	protected:
		
		PIMAGE_RESOURCE_DIRECTORY root_;
		PIMAGE_RESOURCE_DIRECTORY_ENTRY ptr_;
	};


}  // namespace PeDecoder
