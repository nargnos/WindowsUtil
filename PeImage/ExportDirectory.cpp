#include "stdafx.h"
#include "ExportDirectory.h"
#include "ExportDirectoryIterator.h"
namespace PeDecoder
{
	ExportDirectory::ExportDirectory(IDataDirectoryUtil& util) :
		DirectoryBase(util)
	{
		numberOfNames_ = &GetPtr()->NumberOfNames;
		numberOfFunctions_ = &GetPtr()->NumberOfFunctions;
		funcTable_ = reinterpret_cast<PDWORD>(util.RvaToDataPtr(GetPtr()->AddressOfFunctions));
		nameTable_ = reinterpret_cast<PDWORD>(util.RvaToDataPtr(GetPtr()->AddressOfNames));
		nameOrdinalTable_ = reinterpret_cast<PWORD>(util.RvaToDataPtr(GetPtr()->AddressOfNameOrdinals));
	}
	const PDWORD ExportDirectory::GetFunctionsPtr() const
	{
		return funcTable_;
	}
	const PDWORD ExportDirectory::GetNamesPtr() const
	{
		return nameTable_;
	}
	const PWORD ExportDirectory::GetNameOrdinalsPtr() const
	{
		return nameOrdinalTable_;
	}
	const PDWORD ExportDirectory::GetNumberOfFunctionsPtr() const
	{
		return numberOfFunctions_;
	}
	const PDWORD ExportDirectory::GetNumberOfNamesPtr() const
	{
		return numberOfNames_;
	}

	ExportDirectoryIterator ExportDirectory::begin()
	{
		return ExportDirectoryIterator(*this, 0);
	}

	ExportDirectoryIterator ExportDirectory::end()
	{
		return ExportDirectoryIterator(*this, *GetNumberOfNamesPtr());
	}


	

}  // namespace PeDecoder
