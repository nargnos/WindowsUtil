#pragma once
#include "../Common/Common.h"
#include "BaseRelocationIterator.h"
namespace PE
{
	template<typename _PeDecoder>
	class RelocDirectory :
		public DataDirectory< _PeDecoder, PIMAGE_BASE_RELOCATION, IMAGE_DIRECTORY_ENTRY_BASERELOC>,
		public GetIterator<BaseRelocationIterator<RelocDirectory<_PeDecoder>>,RelocDirectory<_PeDecoder>>
	{
	public:
		friend GetIteratorBase::Iterator;
		RelocDirectory(_PeDecoder& pe):DataDirectoryBase(pe)
		{
			canCreateIterator = true;
		}

		~RelocDirectory()
		{
		}


	};

}