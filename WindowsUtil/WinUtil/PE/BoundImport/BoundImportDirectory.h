#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class BoundImportDirectory :
		public DataDirectory<BoundImportDirectory<_PeDecoder>,_PeDecoder, PIMAGE_BOUND_IMPORT_DESCRIPTOR, IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT>
	{
	public:

		BoundImportDirectory(_PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}

		~BoundImportDirectory()
		{
		}
	};

}