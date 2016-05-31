#include "stdafx.h"
#include "NtHeaderWrapper.h"
#include "PeImage.h"
#include "FileHeaderWrapper.h"
namespace PeImageClr
{
	inline bool NtHeaderWrapper::Is32PE()
	{
		return pe->HasNtHeader32;
	}
	inline NtHeaderWrapper::NtHeaderWrapper(PeImage ^ pe) :PeStructWrapperBase(pe)
	{
		fileHeader = nullptr;
		optionalHeader = nullptr;
		SetDescription(IntPtr(pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()), pe->BaseAddress, 0);
	}
	inline array<String^>^ NtHeaderWrapper::GetSortList()
	{
		if (NtHeaderWrapper::sortList == nullptr)
		{
			NtHeaderWrapper::sortList = gcnew array<String^>
			{
				"Signature",
					"FileHeader",
					"OptionalHeader32",
					"OptionalHeader64"

			};
		}
		return NtHeaderWrapper::sortList;
	}
	inline PeStructWrapperType & NtHeaderWrapper::GetUnmanagedStruct()
	{
		return pe->GetPeDecoder()->GetNtHeader;
	}
	inline List<String^>^ NtHeaderWrapper::GetHidePropList()
	{
		auto result = gcnew List<String^>();
		if (Is32PE())
		{
			result->Add("OptionalHeader64");
		}
		else
		{
			result->Add("OptionalHeader32");
		}
		return result;
	}
}  // namespace PeImageClr
