#pragma once
#include "ShowPropertiesConverter.h"
#include "StructOffset.h"
#include "IDescription.h"
#include "UnmanagedMemory.h"
#include "UnmanagedValueSort.h"
namespace PeImageClr
{
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
}  // namespace PeImageClr
