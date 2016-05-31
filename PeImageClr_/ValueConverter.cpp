#include "stdafx.h"
#include "ValueConverter.h"
namespace PeImageClr
{
	bool ValueConverter::CanConvertFrom(ITypeDescriptorContext ^ context, Type ^ sourceType)
	{
		if (sourceType == String::typeid)
		{
			return context->PropertyDescriptor->PropertyType != IntPtr::typeid;
		}
		else
		{
			return TypeConverter::CanConvertFrom(context, sourceType);
		}
	}
	Object ^ ValueConverter::ConvertTo(ITypeDescriptorContext ^ context, CultureInfo ^ culture, Object ^ value, Type ^ destinationType)
	{
		auto propType = value->GetType();
		if (propType->IsValueType && propType->IsPrimitive)
		{
			if (propType == IntPtr::typeid)
			{
				if (String::IsNullOrEmpty(format))
				{
					format = "X" + 2 * IntPtr::Size;
				}
				return ((IntPtr^)value)->ToString(format);
			}
			else
			{
				if (String::IsNullOrEmpty(format))
				{
					format = "{0:X" + 2 * Marshal::SizeOf(value) + "}";
				}
				return String::Format(format, value);
			}
		}
		return TypeConverter::ConvertTo(context, culture, value, destinationType);
	}

	// intptr ²»×ª»»

	Object ^ ValueConverter::ConvertFrom(ITypeDescriptorContext ^ context, CultureInfo ^ culture, Object ^ value)
	{
		if (value->GetType() == String::typeid)
		{
			if (parseMethod == nullptr)
			{
				auto propType = context->PropertyDescriptor->PropertyType;
				if (propType->IsValueType && propType->IsPrimitive)
				{
					parseMethod = propType->GetMethod("Parse", gcnew array<Type^>{ String::typeid, NumberStyles::typeid });
				}
			}
			return parseMethod->Invoke(nullptr, gcnew array<Object^>{ value, NumberStyles::HexNumber });
		}
		else
		{
			return TypeConverter::ConvertFrom(context, culture, value);
		}
	}
}  // namespace PeImageClr

