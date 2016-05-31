#pragma once
namespace PeImageClr
{
	using namespace System;
	using namespace System::Runtime::InteropServices;
	using namespace cli;
	using namespace System::Diagnostics;
	ref class UnmanagedMemory
	{
	public:
		static void Copy(IntPtr source, array<byte>^ destination, int startIndex, int length);
		static void Copy(array<byte>^ source, int startIndex, IntPtr destination, int length);
		static byte ReadByte(IntPtr ptr, int ofs);
		static void WriteByte(IntPtr ptr, int ofs, byte val);
		static Object^ PtrToStructure(IntPtr ptr, Type^ structureType);
		static void StructureToPtr(Object^ structure, IntPtr ptr, bool fDeleteOld);
		static String^ PtrToStringAnsi(IntPtr ptr, int len);
		/*static void Copy(array<byte>^ source, int startIndex, IntPtr destination, int length)
		{

		}*/
		//static void Copy(System.IntPtr source, byte[] destination, int startIndex, int length)
	};

}  // namespace PeImageClr
