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
	ExportDirectory::~ExportDirectory()
	{
		numberOfFunctions_ = nullptr;
		numberOfNames_ = nullptr;
		funcTable_ = nullptr;
		nameTable_ = nullptr;
		nameOrdinalTable_ = nullptr;
	}
	const PDWORD ExportDirectory::GetFunctionsPtr() const
	{
		assert(funcTable_);
		return funcTable_;
	}
	const PDWORD ExportDirectory::GetNamesPtr() const
	{
		assert(nameTable_);
		return nameTable_;
	}
	const PWORD ExportDirectory::GetNameOrdinalsPtr() const
	{
		assert(nameOrdinalTable_);
		return nameOrdinalTable_;
	}
	const PDWORD ExportDirectory::GetNumberOfFunctionsPtr() const
	{
		assert(numberOfFunctions_);
		return numberOfFunctions_;
	}
	const PDWORD ExportDirectory::GetNumberOfNamesPtr() const
	{
		assert(numberOfNames_);
		return numberOfNames_;
	}

	ExportDirectoryIterator ExportDirectory::begin()
	{
		return ExportDirectoryIterator(*this, 0);
	}

	ExportDirectoryIterator ExportDirectory::end()
	{
		assert(GetNumberOfNamesPtr());
		return ExportDirectoryIterator(*this, *GetNumberOfNamesPtr());
	}


	

}  // namespace PeDecoder
