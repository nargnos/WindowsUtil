#pragma once
// PIMAGE_LOAD_CONFIG_DIRECTORY32 PIMAGE_LOAD_CONFIG_DIRECTORY64
#include "../Common/Common.h"
namespace PE
{
	class LoadConfigDirectory :
		public DataDirectory<LoadConfigDirectory, PVOID, IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG>
	{
	public:
		explicit LoadConfigDirectory(PeDecoder & pe);
		~LoadConfigDirectory();
	};

}  // namespace PE
