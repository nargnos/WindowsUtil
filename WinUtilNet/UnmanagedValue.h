#pragma once
namespace NAMESPACE {

	public ref class UnmanagedValueSort
	{
		UnmanagedValueSort() {}
		static array<String^>^ sortList;
	public:
		static array<String^>^ GetSortList()
		{
			if (UnmanagedValueSort::sortList == nullptr)
			{
				UnmanagedValueSort::sortList = gcnew array<String^>
				{
					"Offset",
						"LocalTime",
						"String",
						"Value"
				};
			}
			return UnmanagedValueSort::sortList;
		}
	};

	generic<typename T> where T : ValueType
		[TypeConverter(ShowPropertiesConverter::typeid)]
	public 	ref class UnmanagedValue :
		public StructOffset,
		public IDescription
	{

		typedef UnmanagedValue<T> UnmanagedValueType;
	public:

		UnmanagedValue(IntPtr addr, IntPtr base) :StructOffset(addr, base)
		{

		}

		[TypeConverter(ValueConverter::typeid)]
		property T Value
		{
			T get()
			{
				return safe_cast<T>(UnmanagedMemory::PtrToStructure(addr, T::typeid));
			}

			void set(T value)
			{
				UnmanagedMemory::StructureToPtr(value, addr, false);
			};
		}

		virtual String ^ GetDescription() override
		{
			return String::Format(GetValueSizeStr(sizeof(T)) + "\t{0:X" + 2 * sizeof(T) + "}", Value);
		}

		virtual array<String^>^ GetSortList()
		{
			return UnmanagedValueSort::GetSortList();
		}
	};
	generic<typename T> where T : ValueType
		[TypeConverter(ShowPropertiesConverter::typeid)]
	public 	ref class UnmanagedDateTimeValue :public UnmanagedValue<T>
	{
		static DateTime^ dt = gcnew DateTime(1970, 1, 1, 0, 0, 0, 0);

	public:
		UnmanagedDateTimeValue(IntPtr addr, IntPtr base) :UnmanagedValue<T>(addr, base)
		{

		}
		property DateTime^ LocalTime
		{
			DateTime^ get()
			{

				return  UnmanagedDateTimeValue<T>::dt->AddSeconds(Convert::ToDouble(this->Value));
			}

		}
	};

	[TypeConverter(ShowPropertiesConverter::typeid)]
	public 	ref class UnmanagedString :
		public StructOffset,
		public IDescription
	{
		static array<String^>^ sortList;
		int strLen;
	public:
		UnmanagedString(IntPtr addr, IntPtr base, int strLen) :StructOffset(addr, base), strLen(strLen)
		{
		}
		virtual String ^ GetDescription()
		{
			return String;

		}

		virtual array<String^>^ GetSortList()
		{
			return UnmanagedValueSort::GetSortList();
		}
		property String^ String
		{
			System::String^ get()
			{
				if (strLen == 0)
				{
					auto result = Marshal::PtrToStringAnsi(addr);
					strLen = System::Text::Encoding::ASCII->GetByteCount(result); // 限制字符串长度
					return result;
				}
				// FIX: 遇到字符串中间有\0时会把后面的也输出来，但是又必须限制长度
				return Marshal::PtrToStringAnsi(addr, strLen)->TrimEnd(' ', '\0');
			}
			void set(System::String^ value)
			{
				int writeCount = System::Text::Encoding::ASCII->GetByteCount(value);

				if (strLen == 0)
				{
					strLen = System::Text::Encoding::ASCII->GetByteCount(Marshal::PtrToStringAnsi(addr));
				}
				if (writeCount <= strLen)
				{
					auto strBytes = System::Text::Encoding::ASCII->GetBytes(value);
					UnmanagedMemory::Copy(strBytes, 0, addr, strBytes->Length);
				}
			}
		};
	};

}