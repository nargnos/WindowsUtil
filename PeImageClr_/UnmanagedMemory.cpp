#include "stdafx.h"
#include "UnmanagedMemory.h"

namespace PeImageClr
{
	void UnmanagedMemory::Copy(IntPtr source, array<byte>^ destination, int startIndex, int length)
	{
		Marshal::Copy(source, destination, startIndex, length);
	}
	void UnmanagedMemory::Copy(array<byte>^ source, int startIndex, IntPtr destination, int length)
	{
		//Marshal::Copy(source, startIndex, destination, length);
	}
	byte UnmanagedMemory::ReadByte(IntPtr ptr, int ofs)
	{
		return Marshal::ReadByte(ptr, ofs);
	}
	void UnmanagedMemory::WriteByte(IntPtr ptr, int ofs, byte val)
	{
		Marshal::WriteByte(ptr, ofs, val);
	}
	Object ^ UnmanagedMemory::PtrToStructure(IntPtr ptr, Type ^ structureType)
	{
		return Marshal::PtrToStructure(ptr, structureType);
	}
	void UnmanagedMemory::StructureToPtr(Object ^ structure, IntPtr ptr, bool fDeleteOld)
	{
		//Marshal::StructureToPtr(structure, ptr, fDeleteOld);
	}
	String ^ UnmanagedMemory::PtrToStringAnsi(IntPtr ptr, int len)
	{
		return Marshal::PtrToStringAnsi(ptr, len);
	}
}  // namespace PeImageClr
