#include "stdafx.h"
#include "EnumHexConverter.h"

namespace PeImageClr
{
	EnumHexConverter::EnumHexConverter(Type ^ type) :EnumConverter(type)
	{
		Debug::Assert(type->IsEnum);
	}
	Object ^ EnumHexConverter::ConvertTo(ITypeDescriptorContext ^ context, CultureInfo ^ culture, Object ^ value, Type ^ destinationType)
	{
		if (destinationType != String::typeid)
		{
			return nullptr;
		}
		if (String::IsNullOrEmpty(formatStr))
		{
			formatStr = "{0} ({1:X" + sizeof(value) + "})";
		}
		return String::Format(formatStr, EnumConverter::ConvertTo(context, culture, value, destinationType), Convert::ToInt32(value));
	}
	Object ^ EnumHexConverter::ConvertFrom(ITypeDescriptorContext ^ context, CultureInfo ^ culture, Object ^ value)
	{
		if (value->GetType() == String::typeid)
		{
			auto str = safe_cast<String^>(value);
			return EnumConverter::ConvertFrom(context, culture, str->Remove(str->Length - 7, 7));
		}
		return EnumConverter::ConvertFrom(context, culture, value);
	}
}  // namespace PeImageClr
