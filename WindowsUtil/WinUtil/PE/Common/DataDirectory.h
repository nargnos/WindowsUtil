#pragma once
#include <Windows.h>
#include "..\Common\PeStruct.h"
namespace PE
{
	class DataDirectoryBase :public PeStruct
	{
	protected:
		PIMAGE_DATA_DIRECTORY dataDirectory;
		PDWORD size;
	public:
		DataDirectoryBase(PeDecoder& pe);
		PVOID DirectoryEntryToData();
	};
	template<typename DataDirectoryChild, typename DataType>
	class DataDirectory_DataType :public DataDirectoryBase
	{
	protected:
		typedef DataDirectory_DataType<DataDirectoryChild, DataType> OverloadDirectoryEntryToData;
		DataType data;
		virtual void Init()
		{
			if (dataDirectory)
			{
				size = &dataDirectory->Size;
				DataDirectoryChild* child = static_cast<DataDirectoryChild*>(this);
				data = reinterpret_cast<DataType>(child->DirectoryEntryToData()); // 执行子类的
			}
			else
			{
				size = NULL;
				data = NULL;
			}
		}
	public:
		// 需要先判断结构存在才能进行下一步操作
		bool IsExist()
		{
			return data != NULL;
		}
		DataDirectory_DataType(PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}
	};
	// 从Index取出PIMAGE_DATA_DIRECTORY，并把rva指向数据存储在data中
	template<typename DataDirectoryChild, typename DataType, int Index>
	class DataDirectory :public DataDirectory_DataType<DataDirectoryChild, DataType>
	{
		friend DataDirectoryChild;
	public:
		typedef DataDirectory<DataDirectoryChild, DataType, Index> DataDirectoryBase;

		DataDirectory(PeDecoder& pe) :DataDirectory_DataType<DataDirectoryChild, DataType>(pe)
		{
			dataDirectory = peDecoder.GetDataDirectory(Index);
			Init();
		}


	};
}
