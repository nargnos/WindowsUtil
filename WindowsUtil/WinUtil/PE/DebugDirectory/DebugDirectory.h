#pragma once
#include "../Common/Common.h"
namespace PE
{
	class DebugDirectory :
		public DataDirectory<DebugDirectory, PIMAGE_DEBUG_DIRECTORY, IMAGE_DIRECTORY_ENTRY_DEBUG>
	{
	public:
		explicit DebugDirectory(PeDecoder & pe);
		~DebugDirectory();
	};

}  // namespace PE
