#pragma once
// PIMAGE_TLS_DIRECTORY32 PIMAGE_TLS_DIRECTORY64

#include "../Common/Common.h"
namespace PE
{
	
	class TlsDirectory :
		public DataDirectory<TlsDirectory, PVOID, IMAGE_DIRECTORY_ENTRY_TLS>
	{
	public:
		explicit TlsDirectory(PeDecoder& pe);
		~TlsDirectory();
	};

}
