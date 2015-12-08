#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class ResourceDirectory:
		public DataDirectory<ResourceDirectory< _PeDecoder>, _PeDecoder, PIMAGE_RESOURCE_DIRECTORY, IMAGE_DIRECTORY_ENTRY_RESOURCE>
	{
	public:
		//friend GetIteratorBase::Iterator;
		ResourceDirectory(_PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}

		~ResourceDirectory()
		{
		}
	};

}