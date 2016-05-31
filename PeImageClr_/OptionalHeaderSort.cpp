#include "stdafx.h"
#include "OptionalHeaderSort.h"

namespace PeImageClr
{
	OptionalHeaderSort::OptionalHeaderSort()
	{
	}
	array<String^>^ OptionalHeaderSort::GetSortList()
	{
		if (OptionalHeaderSort::sortList == nullptr)
		{
			OptionalHeaderSort::sortList = gcnew array<String^>
			{
				"Magic",
					"MajorLinkerVersion",
					"MinorLinkerVersion",
					"SizeOfCode",
					"SizeOfInitializedData",
					"SizeOfUninitializedData",
					"AddressOfEntryPoint",
					"BaseOfCode",
					"BaseOfData",
					"ImageBase",
					"SectionAlignment",
					"FileAlignment",
					"MajorOperatingSystemVersion",
					"MinorOperatingSystemVersion",
					"MajorImageVersion",
					"MinorImageVersion",
					"MajorSubsystemVersion",
					"MinorSubsystemVersion",
					"Win32VersionValue",
					"SizeOfImage",
					"SizeOfHeaders",
					"CheckSum",
					"Subsystem",
					"DllCharacteristics",
					"SizeOfStackReserve",
					"SizeOfStackCommit",
					"SizeOfHeapReserve",
					"SizeOfHeapCommit",
					"LoaderFlags",
					"NumberOfRvaAndSizes"
			};
		}
		return OptionalHeaderSort::sortList;
	}
}  // namespace PeImageClr
