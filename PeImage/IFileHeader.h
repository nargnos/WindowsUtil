#pragma once
#include <Windows.h>
#include "MachineType.h"
#include "FileHeaderCharacteristics.h"
namespace PeDecoder
{
	__interface IFileHeader
	{

		MachineType GetMachineType() const;
		FileHeaderCharacteristics GetFileHeaderCharacteristics() const;
		PIMAGE_FILE_HEADER GetFileHeader() const;
	};
}  // namespace PeDecoder