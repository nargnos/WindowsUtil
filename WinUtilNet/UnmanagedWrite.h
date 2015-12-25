#pragma once
namespace NAMESPACE {
	ref class UnmanagedWrite
	{
	public:
		static void Copy(IntPtr source, array<byte>^ destination, int startIndex, int length)
		{
			Marshal::Copy(source, destination, startIndex, length);
		}
		static void Copy(array<byte>^ source, int startIndex, IntPtr destination, int length)
		{
			Marshal::Copy(source, startIndex, destination, length);
		}
		static byte ReadByte(IntPtr ptr, int ofs)
		{
			return Marshal::ReadByte(ptr, ofs);
		}
		static void WriteByte(IntPtr ptr, int ofs, byte val)
		{
			Marshal::WriteByte(ptr, ofs, val);
		}
		static Object^ PtrToStructure(IntPtr ptr, Type^ structureType)
		{
			return Marshal::PtrToStructure(ptr, structureType);
		}
		static void StructureToPtr(Object^ structure, IntPtr ptr, bool fDeleteOld)
		{
			Marshal::StructureToPtr(structure, ptr, fDeleteOld);
		}
	};

}