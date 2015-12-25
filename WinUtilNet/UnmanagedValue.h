#pragma once
namespace NAMESPACE {





	generic<typename T> where T : ValueType
		[TypeConverter(UnmanagedValueConverter::typeid)]
	public 	ref struct UnmanagedValue
	{
		IntPtr addr;
	public:

		UnmanagedValue(IntPtr addr) :addr(addr)
		{

		}
		virtual String^ ToString() override
		{
			return String::Format("{1}\t{0:X" + 2 * sizeof(T) + "}", Value, GetValueSizeStr(sizeof(T))) ;
		}
		[TypeConverter(ValueConverter::typeid)]
		property T Value
		{
			T get()
			{
				return safe_cast<T>(UnmanagedWrite::PtrToStructure(addr, T::typeid));
			}

			void set(T value)
			{
				UnmanagedWrite::StructureToPtr(value, addr, false);
			};
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
	};

}