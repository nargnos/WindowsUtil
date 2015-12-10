#include "ExportDirectory.h"

PE::ExportDirectory::ExportDirectory(PeDecoder & pe) :DataDirectoryBase(pe)
{
	auto exportDirectory = GetValue();
	if (exportDirectory)
	{
		numberOfNames = &exportDirectory->NumberOfNames;
		numberOfFunctions = &exportDirectory->NumberOfFunctions;
		funcsTable = reinterpret_cast<PDWORD>(peDecoder.GetRvaData(exportDirectory->AddressOfFunctions));
		namesTable = reinterpret_cast<PDWORD>(peDecoder.GetRvaData(exportDirectory->AddressOfNames));
		nameOrdinalsTable = reinterpret_cast<PWORD>(peDecoder.GetRvaData(exportDirectory->AddressOfNameOrdinals));
		canCreateIterator = true;
	}
	else
	{
		numberOfNames = NULL;
		numberOfFunctions = NULL;
		funcsTable = NULL;
		namesTable = NULL;
		nameOrdinalsTable = NULL;
	}
}

PE::ExportDirectory::~ExportDirectory() {}

PIMAGE_EXPORT_DIRECTORY PE::ExportDirectory::GetValue()
{
	return data;
}

const PDWORD PE::ExportDirectory::FuncTable()
{
	return funcsTable;
}

const PDWORD PE::ExportDirectory::NameTable()
{
	return namesTable;
}

const PWORD PE::ExportDirectory::OrdinalTable()
{
	return nameOrdinalsTable;
}

const PDWORD PE::ExportDirectory::NumberOfFunctions()
{
	return numberOfFunctions;
}

const PDWORD PE::ExportDirectory::NumberOfNames()
{
	return numberOfNames;
}
