#pragma once

#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class EntryExceptionDirectory :
		public DataDirectory<_PeDecoder, PIMAGE_RUNTIME_FUNCTION_ENTRY, IMAGE_DIRECTORY_ENTRY_EXCEPTION>
	{
	public:

		EntryExceptionDirectory(_PeDecoder& pe) :DataDirectory<_PeDecoder, PIMAGE_RUNTIME_FUNCTION_ENTRY, IMAGE_DIRECTORY_ENTRY_EXCEPTION>(pe)
		{
		}

		~EntryExceptionDirectory()
		{
		}
	};

}