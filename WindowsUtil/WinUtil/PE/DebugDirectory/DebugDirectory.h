#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class DebugDirectory :
		public DataDirectory<_PeDecoder,PIMAGE_DEBUG_DIRECTORY, IMAGE_DIRECTORY_ENTRY_DEBUG>
	{
	public:

		DebugDirectory(_PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}

		~DebugDirectory()
		{
		}
	};

}
