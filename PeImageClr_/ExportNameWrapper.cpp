#include "stdafx.h"
#include "ExportNameWrapper.h"
#include "PeImage.h"
namespace PeImageClr
{
	PVOID ExportNameWrapper::GetNamePtr()
	{
		return pe->GetPeDecoder().RvaToDataPtr(*(PDWORD)nameRva.ToPointer());
	}
	ExportNameWrapper::ExportNameWrapper(IntPtr nameRva, IntPtr nameOrdinal, PeImage ^ pe)
		:nameRva(nameRva), nameOrdinal(nameOrdinal), pe(pe)
	{
		SetDescription(nameRva, pe->BaseAddress, 0);
	}
	String ^ ExportNameWrapper::GetName()
	{
		return Name->String;
	}
	array<String^>^ ExportNameWrapper::GetSortList()
	{
		return nullptr;
	}
}  // namespace PeImageClr
