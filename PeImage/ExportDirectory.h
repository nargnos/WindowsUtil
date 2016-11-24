#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	class ExportDirectoryIterator;
	class ExportDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Export>
	{
	public:
		typedef ExportDirectoryIterator iterator;

		ExportDirectory(IDataDirectoryUtil& util);
		virtual ~ExportDirectory();
		const PDWORD GetFunctionsPtr() const;
		const PDWORD GetNamesPtr() const;
		const PWORD GetNameOrdinalsPtr() const;
		const PDWORD GetNumberOfFunctionsPtr() const;
		const PDWORD GetNumberOfNamesPtr() const;
		iterator begin();
		iterator end();
	protected:
		PDWORD numberOfFunctions_;
		PDWORD numberOfNames_;
		PDWORD funcTable_;
		PDWORD nameTable_;
		PWORD nameOrdinalTable_;
	};
	
}  // namespace PeDecoder
