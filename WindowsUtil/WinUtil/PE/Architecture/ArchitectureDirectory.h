#pragma once
#include "../Common/Common.h"
namespace PE
{
	class ArchitectureDirectory :
		public DataDirectory<ArchitectureDirectory, PIMAGE_ARCHITECTURE_HEADER, IMAGE_DIRECTORY_ENTRY_ARCHITECTURE>
	{
	public:
		explicit ArchitectureDirectory(PeDecoder& pe);
		~ArchitectureDirectory();
	};

}