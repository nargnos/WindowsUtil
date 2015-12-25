#pragma once
namespace NAMESPACE {
	[TypeConverter(UnmanagedArrayConverter::typeid)]
	public ref class UnmanagedByteArray
	{
	protected:
		int length;
		IntPtr addr;
		bool isAlloc;

	public:
		UnmanagedByteArray(IntPtr ptr, int length)
		{
			Debug::Assert(ptr != IntPtr::Zero && length > 0);
			this->length = length;
			this->addr = ptr;
			isAlloc = false;
		}
		UnmanagedByteArray(int length)
		{
			Debug::Assert(length > 0);
			this->length = length;
			addr = Marshal::AllocHGlobal(length);
			isAlloc = true;
		}
		~UnmanagedByteArray()
		{
			this->!UnmanagedByteArray();
		}
		!UnmanagedByteArray()
		{
			if (isAlloc)
			{
				if (addr != IntPtr::Zero)
				{
					Marshal::FreeHGlobal(addr);
				}
			}
			addr = IntPtr::Zero;
		}
		[TypeConverter(ValueConverter::typeid)]
		property IntPtr Offset
		{
			IntPtr get()
			{
				return addr;
			}
		internal:
			void set(IntPtr value)
			{
				addr = value;
			}
		}
	public:
		[TypeConverter(ValueConverter::typeid)]
		property int Length
		{
			int get()
			{
				return length;
			}
		}; 
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
			return UnmanagedWrite::ReadByte(addr, index);
		}
		void WriteByte(int index, byte value)
		{
			Debug::Assert(index < length && index >= 0);
			UnmanagedWrite::WriteByte(addr, index, value);
		}
		
		array<byte>^ ToByteArray()
		{
			return ReadBytes(0, length);
		}
		void WriteBytes(array<byte>^ bytes, int index)
		{
			Debug::Assert(bytes != nullptr && bytes->Length != 0 && index + bytes->Length <= length && index >= 0);
			UnmanagedWrite::Copy(bytes, index, addr, bytes->Length);
		}
		array<byte>^ ReadBytes(int index, int length)
		{
			Debug::Assert(index + length <= this->length && index >= 0);
			auto result = gcnew array<byte>(length);
			UnmanagedWrite::Copy(addr, result, index, length);
			return result;
		}
		virtual String^ ToString() override
		{
			return String::Format("{0}\t*{1}", GetValueSizeStr(sizeof(byte)), Length);
		}
	};
	

	generic<typename T> where T:ValueType
		[TypeConverter(UnmanagedArrayConverter::typeid)]
		public ref class UnmanagedArray :public UnmanagedByteArray
	{
	public:
		UnmanagedArray(IntPtr ptr, int length) :UnmanagedByteArray(ptr, length)
		{

		}
		T Read(int index)
		{
			return default[index];
		}
		property T default[int]
		{
			T get(int index)
			{
				Debug::Assert(index >= 0 && index <= length);
				return safe_cast<T>(UnmanagedWrite::PtrToStructure(addr+index*sizeof(T), T::typeid));
			};
			void set(int index, T value)
			{
				Debug::Assert(index >= 0 && index <= length);
				UnmanagedWrite::StructureToPtr(value, addr+index*sizeof(T), false);
			};
		};
		virtual String^ ToString() override
		{
			return String::Format("{0}\t*{1}", GetValueSizeStr(sizeof(T)), Length);
		}

		[TypeConverter(ValueArrayConverter::typeid)]
		property array<T>^ Array
		{
			array<T>^ get()
			{
				array<T>^ result = gcnew array<T>(length);
				for (int i = 0; i < length; i++)
				{
					result[i] = default[i];
				}
				return result;
			}
			void set(array<T>^ value)
			{
				if (value!=nullptr)
				{
					// ½Ø¶Ï¶àÓàµÄ
					auto loopTimes = value->Length < length ? value->Length : length;
					for (int i = 0; i < loopTimes; i++)
					{
						default[i] = value[i];
					}
				}
			}
		};
	};
}