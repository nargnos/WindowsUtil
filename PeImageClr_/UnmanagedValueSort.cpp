#include "stdafx.h"
#include "UnmanagedValueSort.h"

namespace PeImageClr
{
	UnmanagedValueSort::UnmanagedValueSort()
	{
	}
	array<String^>^ UnmanagedValueSort::GetSortList()
	{
		if (UnmanagedValueSort::sortList == nullptr)
		{
			UnmanagedValueSort::sortList = gcnew array<String^>
			{
				"Offset",
					"LocalTime",
					"String",
					"Value"
			};
		}
		return UnmanagedValueSort::sortList;
	}
}  // namespace PeImageClr
