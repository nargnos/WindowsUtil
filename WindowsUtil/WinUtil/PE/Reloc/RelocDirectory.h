#pragma once
#include "../Common/Common.h"
#include "BaseRelocationIterator.h"
namespace PE
{
	template<typename _PeDecoder>
	class RelocDirectory :
		public GetIterator<BaseRelocationIterator<RelocDirectory<_PeDecoder>>,RelocDirectory<_PeDecoder>>,
		public DataDirectory<_PeDecoder, PIMAGE_BASE_RELOCATION, IMAGE_DIRECTORY_ENTRY_BASERELOC>
	{
	public:
		friend BaseRelocationIterator<RelocDirectory<_PeDecoder>>;
		RelocDirectory(_PeDecoder& pe):DataDirectory<_PeDecoder, PIMAGE_BASE_RELOCATION, IMAGE_DIRECTORY_ENTRY_BASERELOC>(pe)
		{
			canCreateIterator = true;
		}

		~RelocDirectory()
		{
		}


	};

}