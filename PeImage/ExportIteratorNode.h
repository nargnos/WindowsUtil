#pragma once
#include "PeImageFwd.h"
namespace PeDecoder
{
	class ExportIteratorNode
	{
	public:
		friend class ExportDirectoryIterator;
		ExportIteratorNode(ExportDirectory& directory, DWORD index);
		PDWORD FuncRva();
		PDWORD NameRva();
		PWORD NameOrdinals();
		void* FuncPtr();
		char* NamePtr();

	protected:
		ExportDirectory* directory_;
		DWORD index_;
	};
}  // namespace PeDecoder
