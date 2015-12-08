#pragma once
// PIMAGE_LOAD_CONFIG_DIRECTORY32 PIMAGE_LOAD_CONFIG_DIRECTORY64
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class LoadConfigDirectory :
		public DataDirectory<LoadConfigDirectory< _PeDecoder>, _PeDecoder, PVOID, IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG>
	{
	public:

		LoadConfigDirectory(_PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}

		~LoadConfigDirectory()
		{
		}
	};

}