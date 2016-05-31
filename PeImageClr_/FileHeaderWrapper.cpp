#include "stdafx.h"
#include "FileHeaderWrapper.h"
#include "PeImage.h"
namespace PeImageClr
{
	 FileHeaderWrapper::PeStructWrapperType & FileHeaderWrapper::GetUnmanagedStruct()
	{
		return pe->NtHeader->GetUnmanagedStruct()->GetNtHeader32()->FileHeader;
	}
	 FileHeaderWrapper::FileHeaderWrapper(PeImage ^ pe) :PeStructWrapperBase(pe)
	{
		SetDescription(IntPtr(&pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()->FileHeader), GetPeBase(), sizeof(IMAGE_FILE_HEADER));
	}
	 array<String^>^ FileHeaderWrapper::GetSortList()
	{
		if (FileHeaderWrapper::sortList == nullptr)
		{
			FileHeaderWrapper::sortList = gcnew array<String^>
			{
				"Machine",
					"NumberOfSections",
					"TimeDateStamp",
					"PointerToSymbolTable",
					"NumberOfSymbols",
					"SizeOfOptionalHeader",
					"Characteristics"
			};
		}
		return FileHeaderWrapper::sortList;
	}
}  // namespace PeImageClr
