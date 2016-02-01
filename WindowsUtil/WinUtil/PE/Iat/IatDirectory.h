#pragma once
#include "../Common/Common.h"
namespace PE
{
	//IMAGE_THUNK_DATA32 IMAGE_THUNK_DATA64
	class IatDirectory :
		public DataDirectory<IatDirectory, PVOID, IMAGE_DIRECTORY_ENTRY_IAT>
	{
	public:
		explicit IatDirectory(PeDecoder& pe);
		~IatDirectory();
	};

}
