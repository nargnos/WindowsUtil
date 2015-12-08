#pragma once
#include <Windows.h>
#include "../Common/PeStruct.h"
#include "IGetValue.h"
#include "InitStruct.h"
namespace PE
{
	// 从Index取出PIMAGE_DATA_DIRECTORY，并把rva指向数据存储在data中
	template<typename _Child, typename _PeDecoder, typename DataType, int Index>
	class DataDirectory :public PeStruct<_PeDecoder>
	{
	protected:
		PIMAGE_DATA_DIRECTORY dataDirectory;
		DataType data;
		PDWORD size;
		PVOID DirectoryEntryToData()
		{
			if (!dataDirectory || dataDirectory->VirtualAddress == NULL)
			{
				return NULL;
			}
			return peDecoder.GetRvaData(dataDirectory->VirtualAddress);
		}
	public:
		typedef DataDirectory<_Child, _PeDecoder, DataType, Index> DataDirectoryBase;
		DataDirectory(_PeDecoder& pe) :PeStructBase(pe)
		{
			dataDirectory=peDecoder.GetDataDirectory(Index);
			if (dataDirectory)
			{
				size = &dataDirectory->Size;
				_Child* child = static_cast<_Child*>(this);
				data = reinterpret_cast<DataType>(child->DirectoryEntryToData());
			}			
			else
			{
				size = NULL;
				data = NULL;
			}
		}
		// 需要先判断结构存在才能进行下一步操作
		bool IsExist()
		{
			return data != NULL;
		}
		virtual ~DataDirectory()
		{
		}


	};
}
