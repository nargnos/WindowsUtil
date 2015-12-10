#pragma once
#include "../Common/Common.h"
namespace PE
{
	class ResourceDirectory:
		public DataDirectory<ResourceDirectory, PIMAGE_RESOURCE_DIRECTORY, IMAGE_DIRECTORY_ENTRY_RESOURCE>
	{
	public:
		//friend class GetIteratorBase::Iterator;
		ResourceDirectory(PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}

		~ResourceDirectory()
		{
		}
	};

}