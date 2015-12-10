#pragma once
#include "../Common/Common.h"
namespace PE
{
	class SecurityDirectory :
		public DataDirectory<SecurityDirectory, PVOID, IMAGE_DIRECTORY_ENTRY_SECURITY>
	{
	protected:
		PVOID DirectoryEntryToData();
	public:
		friend class DataDirectoryBase;
		friend class OverloadDirectoryEntryToData;
		SecurityDirectory(PeDecoder& pe);

		~SecurityDirectory();
	};

}