#pragma once
#include "../Common/Common.h"
namespace PE
{
	class ComDescriptorDirectory :
		public DataDirectory<ComDescriptorDirectory, PIMAGE_COR20_HEADER, IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR>
	{
	public:
		ComDescriptorDirectory(PeDecoder& pe);
		~ComDescriptorDirectory();
	};

}