#pragma once
namespace NAMESPACE {
	public ref class UnmanagedArraySort
	{
		UnmanagedArraySort() {}
		static array<String^>^ sortList;
	public:
		static array<String^>^ GetSortList()
		{
			if (UnmanagedArraySort::sortList == nullptr)
			{
				UnmanagedArraySort::sortList = gcnew array<String^>
				{
					"Offset",
						"Length",
						"Array"
				};
			}
			return UnmanagedArraySort::sortList;
		}
	};
	generic<typename T> where T:ValueType
		[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class UnmanagedArray :
		public StructOffset,
		public IDescription
	{
		static array<String^>^ sortList;
	protected:
		int length;
		typedef UnmanagedArray<T> UnmanagedArrayBase;
	public:
		UnmanagedArray(IntPtr ptr, IntPtr base, int length) :StructOffset(ptr,base)
		{
			Debug::Assert(ptr != IntPtr::Zero && length > 0);
			this->length = length;
			this->addr = ptr;
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
				return safe_cast<T>(UnmanagedMemory::PtrToStructure(addr + index*sizeof(T), T::typeid));
			};
			void set(int index, T value)
			{
				Debug::Assert(index >= 0 && index <= length);
				UnmanagedMemory::StructureToPtr(value, addr + index*sizeof(T), false);
			};
		};
		[TypeConverter(ValueConverter::typeid)]
		property int Length
		{
			int get()
			{
				return length;
			}
		};
		[TypeConverter(ValueArrayConverter::typeid)]
		property array<T>^ Array
		{
			// FIX: 性能低
			array<T>^ get()
			{
				array<T>^ result = gcnew array<T>(length);
				for (int i = 0; i < result->Length; i++)
				{
					result[i] = default[i];
				}
				return result;
			}
			void set(array<T>^ value)
			{
				if (value != nullptr)
				{
					// 截断多余的
					auto loopTimes = value->Length < length ? value->Length : length;
					for (int i = 0; i < loopTimes; i++)
					{
						default[i] = value[i];
					}
				}
			}
		};
		virtual String ^ GetDescription() override
		{
			return String::Format(GetValueSizeStr(sizeof(T)) + "\t* {0}(D)", length);
		}

		virtual array<String^>^ GetSortList()
		{
			return UnmanagedArraySort::GetSortList();
		}
	};

	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class UnmanagedByteArray :
		public UnmanagedArray<byte>
	{

	public:
		UnmanagedByteArray(IntPtr ptr, IntPtr base, int length) :UnmanagedArrayBase(ptr,base, length)
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


}