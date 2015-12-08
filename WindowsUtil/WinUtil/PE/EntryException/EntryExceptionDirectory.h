#pragma once

#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class EntryExceptionDirectory :
		public DataDirectory<EntryExceptionDirectory<_PeDecoder>,_PeDecoder, PIMAGE_RUNTIME_FUNCTION_ENTRY, IMAGE_DIRECTORY_ENTRY_EXCEPTION>
	{
	public:

		EntryExceptionDirectory(_PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}

		~EntryExceptionDirectory()
		{
		}
	};

}