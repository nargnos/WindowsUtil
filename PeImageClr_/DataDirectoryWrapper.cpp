#include "stdafx.h"
#include "DataDirectoryWrapper.h"

namespace PeImageClr
{
	inline DataDirectoryWrapper::DataDirectoryWrapper(IntPtr addr, IntPtr basePtr)//:PeStructDescription()
	{
		SetDescription(addr, basePtr, sizeof(IMAGE_DATA_DIRECTORY));
	}
	inline DataDirectoryWrapper::~DataDirectoryWrapper()
	{
	}
	inline array<String^>^ DataDirectoryWrapper::GetSortList()
	{
		if (DataDirectoryWrapper::sortList == nullptr)
		{
			DataDirectoryWrapper::sortList = gcnew array<String^>
			{
				"Offset",
					"VirtualAddress",
					"Size"
			};
		}
		return DataDirectoryWrapper::sortList;
	}
}  // namespace PeImageClr
