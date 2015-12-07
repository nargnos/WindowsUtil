#pragma once

#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class ArchitectureDirectory :
		public DataDirectory<_PeDecoder, PIMAGE_ARCHITECTURE_HEADER, IMAGE_DIRECTORY_ENTRY_ARCHITECTURE>
	{
	public:

		ArchitectureDirectory(_PeDecoder& pe) :DataDirectory<_PeDecoder, PIMAGE_ARCHITECTURE_HEADER, IMAGE_DIRECTORY_ENTRY_ARCHITECTURE>(pe)
		{
		}

		~ArchitectureDirectory()
		{
		}
	};

}