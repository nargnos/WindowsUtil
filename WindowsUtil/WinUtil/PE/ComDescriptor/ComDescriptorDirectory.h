#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class ComDescriptorDirectory :
		public DataDirectory<_PeDecoder, PIMAGE_COR20_HEADER, IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR>
	{
	public:

		ComDescriptorDirectory(_PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}

		~ComDescriptorDirectory()
		{
		}
	};

}