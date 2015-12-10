#pragma once
#include "../Common/Common.h"
namespace PE
{
	class BoundImportDirectory :
		public DataDirectory<BoundImportDirectory, PIMAGE_BOUND_IMPORT_DESCRIPTOR, IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT>
	{
	public:
		BoundImportDirectory(PeDecoder& pe);
		~BoundImportDirectory();
	};

}