#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	class ExportDirectoryIterator;
	class ExportDirectory :
		public Detail::DirectoryBase<ExportDirectory, DataDirectoryEntryType::Export>
	{
	public:
		typedef ExportDirectoryIterator iterator;

		friend TBase;
		virtual ~ExportDirectory();
		const PDWORD GetFunctionsPtr() const;
		const PDWORD GetNamesPtr() const;
		const PWORD GetNameOrdinalsPtr() const;
		const PDWORD GetNumberOfFunctionsPtr() const;
		const PDWORD GetNumberOfNamesPtr() const;
		iterator begin();
		iterator end();
	protected:
		explicit ExportDirectory(const _STD shared_ptr<IPeImage>& util);
		PDWORD numberOfFunctions_;
		PDWORD numberOfNames_;
		PDWORD funcTable_;
		PDWORD nameTable_;
		PWORD nameOrdinalTable_;
	};
	
}  // namespace PeDecoder
