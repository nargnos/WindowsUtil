#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class ResourceDirectory:
		public DataDirectory<_PeDecoder, PIMAGE_RESOURCE_DIRECTORY, IMAGE_DIRECTORY_ENTRY_RESOURCE>
	{
	public:

		ResourceDirectory(_PeDecoder& pe) :DataDirectory<_PeDecoder, PIMAGE_RESOURCE_DIRECTORY, IMAGE_DIRECTORY_ENTRY_RESOURCE>(pe)
		{
		}

		~ResourceDirectory()
		{
		}
	};

}