#pragma once
#include "../Common/Common.h"
namespace PE
{
	//IMAGE_THUNK_DATA32 IMAGE_THUNK_DATA64
	template<typename _PeDecoder>
	class IatDirectory :
		public DataDirectory<_PeDecoder, PVOID, IMAGE_DIRECTORY_ENTRY_IAT>
	{
	public:

		IatDirectory(_PeDecoder& pe) :DataDirectory<_PeDecoder, PVOID, IMAGE_DIRECTORY_ENTRY_IAT>(pe)
		{
		}

		~IatDirectory()
		{
		}
	};

}
