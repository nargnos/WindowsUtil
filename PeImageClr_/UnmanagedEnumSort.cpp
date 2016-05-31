#include "stdafx.h"
#include "UnmanagedEnumSort.h"

namespace PeImageClr
{
	 UnmanagedEnumSort::UnmanagedEnumSort()
	{
	}
	 array<String^>^ UnmanagedEnumSort::GetSortList()
	{
		if (UnmanagedEnumSort::sortList == nullptr)
		{
			UnmanagedEnumSort::sortList = gcnew array<String^>
			{
				"Offset",
					"Value"
			};
		}
		return UnmanagedEnumSort::sortList;
	}
}  // namespace PeImageClr
