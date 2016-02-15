#pragma once

#include "../Common/Common.h"
namespace PE
{
	class EntryExceptionDirectory :
		public DataDirectory<EntryExceptionDirectory, PIMAGE_RUNTIME_FUNCTION_ENTRY, IMAGE_DIRECTORY_ENTRY_EXCEPTION>
	{
	public:
		explicit EntryExceptionDirectory(PeDecoder* pe);
		~EntryExceptionDirectory();
	};

}  // namespace PE
