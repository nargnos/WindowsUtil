#pragma once
#include <Windows.h>
namespace PeDecoder
{
	class ExportDirectory;
	class ExportIteratorNode
	{
	public:
		friend class ExportDirectoryIterator;
		ExportIteratorNode(const ExportDirectory& directory, DWORD index);
		PDWORD FuncRva();
		PDWORD NameRva();
		PWORD NameOrdinals();
		void* FuncPtr();
		char* NamePtr();
		virtual ~ExportIteratorNode();
		ExportIteratorNode* operator->();
		const ExportIteratorNode* operator->() const;

	protected:
		const ExportDirectory* directory_;
		DWORD index_;
	};
}  // namespace PeDecoder
