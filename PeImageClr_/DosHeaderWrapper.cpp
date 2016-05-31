#include "stdafx.h"
#include "DosHeaderWrapper.h"
#include "PeImage.h"
namespace PeImageClr
{
	inline DosHeaderWrapper::PeStructWrapperType & DosHeaderWrapper::GetUnmanagedStruct()
	{
		return *pe->GetPeDecoder().GetDosHeader();
	}
	inline DosHeaderWrapper::DosHeaderWrapper(PeImage ^ pe) :PeStructWrapperBase(pe)
	{
		SetDescription(GetPeBase(), GetPeBase(), sizeof(IMAGE_DOS_HEADER));
		e_res = nullptr;
		e_res2 = nullptr;
	}
	inline array<String^>^ DosHeaderWrapper::GetSortList()
	{
		if (DosHeaderWrapper::sortList == nullptr)
		{
			DosHeaderWrapper::sortList = gcnew array<String^>
			{
				"E_magic",
					"E_cblp",
					"E_cp",
					"E_crlc",
					"E_cparhdr",
					"E_minalloc",
					"E_maxalloc",
					"E_ss",
					"E_sp",
					"E_csum",
					"E_ip",
					"E_cs",
					"E_lfarlc",
					"E_ovno",
					"E_res",
					"E_oemid",
					"E_oeminfo",
					"E_res2",
					"E_lfanew"
			};
		}
		return DosHeaderWrapper::sortList;
	}
}  // namespace PeImageClr
