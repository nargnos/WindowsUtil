#pragma once
#include "../Common/Common.h"
namespace PE
{
	class GlobalptrDirectory :
		public DataDirectory<GlobalptrDirectory, PVOID, IMAGE_DIRECTORY_ENTRY_GLOBALPTR>
	{
	public:
		GlobalptrDirectory(PeDecoder& pe);
		~GlobalptrDirectory();
	};

}