#pragma once
#include "UnmanagedArray.h"
namespace PeImageClr
{
	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class UnmanagedByteArray :
		public UnmanagedArray<byte>
	{

	public:
		UnmanagedByteArray(IntPtr ptr, IntPtr base, int length) :UnmanagedArrayBase(ptr, base, length)
		{
		}

		[TypeConverter(ValueArrayConverter::typeid)]
		property array<byte>^ Array
		{
			array<byte>^ get()
			{
				return ToByteArray();
			}
			void set(array<byte>^ value)
			{
				WriteBytes(value, 0);
			}
		};
		byte ReadByte(int index)
		{
			Debug::Assert(index < length && index >= 0);
			return UnmanagedMemory::ReadByte(addr, index);
		}
		void WriteByte(int index, byte value)
		{
			Debug::Assert(index < length && index >= 0);
			UnmanagedMemory::WriteByte(addr, index, value);
		}

		array<byte>^ ToByteArray()
		{
			return ReadBytes(0, length);
		}
		void WriteBytes(array<byte>^ bytes, int index)
		{
			Debug::Assert(bytes != nullptr && bytes->Length != 0 && index + bytes->Length <= length && index >= 0);
			UnmanagedMemory::Copy(bytes, index, addr, bytes->Length);
		}
		array<byte>^ ReadBytes(int index, int length)
		{
			Debug::Assert(index + length <= this->length && index >= 0);
			auto result = gcnew array<byte>(length);
			UnmanagedMemory::Copy(addr, result, index, length);
			return result;
		}


	};

}  // namespace PeImageClr
