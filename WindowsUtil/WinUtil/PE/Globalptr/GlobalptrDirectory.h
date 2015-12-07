#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class GlobalptrDirectory :
		public DataDirectory<_PeDecoder, PVOID, IMAGE_DIRECTORY_ENTRY_GLOBALPTR>
	{
	public:

		GlobalptrDirectory(_PeDecoder& pe) :DataDirectory<_PeDecoder, PVOID, IMAGE_DIRECTORY_ENTRY_GLOBALPTR>(pe)
		{
		}

		~GlobalptrDirectory()
		{
		}
	};

}