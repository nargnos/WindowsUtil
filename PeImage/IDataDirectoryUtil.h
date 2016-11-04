#pragma once
#include <Windows.h>
#include "IRvaConverter.h"
#include "DataDirectoryEntryType.h"
#include "ImageType.h"
namespace PeDecoder
{
	__interface IDataDirectoryUtil :
		public IRvaConverter
	{
		bool IsMapped() const;
		PIMAGE_DATA_DIRECTORY GetDirectoryEntry(DataDirectoryEntryType index) const;
		ImageType GetImageType() const;
	};
}  // namespace PeDecoder
