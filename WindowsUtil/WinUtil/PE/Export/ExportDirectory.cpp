#include "ExportDirectory.h"

PE::ExportDirectory::ExportDirectory(PeDecoder* pe) :DataDirectoryBase(pe)
{
	auto exportDirectory = GetValue();
	if (exportDirectory)
	{
		numberOfNames = &exportDirectory->NumberOfNames;
		numberOfFunctions = &exportDirectory->NumberOfFunctions;
		funcTable = reinterpret_cast<PDWORD>(peDecoder->GetRvaData(exportDirectory->AddressOfFunctions));
		nameTable = reinterpret_cast<PDWORD>(peDecoder->GetRvaData(exportDirectory->AddressOfNames));
		nameOrdinalTable = reinterpret_cast<PWORD>(peDecoder->GetRvaData(exportDirectory->AddressOfNameOrdinals));
		canCreateIterator = true;
	}
	else
	{
		numberOfNames = NULL;
		numberOfFunctions = NULL;
		funcTable = NULL;
		nameTable = NULL;
		nameOrdinalTable = NULL;
	}
}

PE::ExportDirectory::~ExportDirectory() {}

PIMAGE_EXPORT_DIRECTORY PE::ExportDirectory::GetValue()
{
	return data;
}

const PDWORD PE::ExportDirectory::FuncTable()
{
	return funcTable;
}

const PDWORD PE::ExportDirectory::NameTable()
{
	return nameTable;
}

const PWORD PE::ExportDirectory::OrdinalTable()
{
	return nameOrdinalTable;
}

const PDWORD PE::ExportDirectory::NumberOfFunctions()
{
	return numberOfFunctions;
}

const PDWORD PE::ExportDirectory::NumberOfNames()
{
	return numberOfNames;
}
