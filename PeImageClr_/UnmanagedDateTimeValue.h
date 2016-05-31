#pragma once
#include "UnmanagedValue.h"
#include "ShowPropertiesConverter.h"
namespace PeImageClr
{
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

}  // namespace PeImageClr
