#include "stdafx.h"
#include "UnmanagedArraySort.h"

namespace PeImageClr
{
	UnmanagedArraySort::UnmanagedArraySort()
	{
	}
	array<String^>^ UnmanagedArraySort::GetSortList()
	{
		if (UnmanagedArraySort::sortList == nullptr)
		{
			UnmanagedArraySort::sortList = gcnew array<String^>
			{
				"Offset",
					"Length",
					"Array"
			};
		}
		return UnmanagedArraySort::sortList;
	}
}  // namespace PeImageClr
