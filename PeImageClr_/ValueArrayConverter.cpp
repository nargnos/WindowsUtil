#include "stdafx.h"
#include "ValueArrayConverter.h"

namespace PeImageClr
{
	ValueArrayConverter::ValueArrayConverter()
	{
	}
	Object ^ ValueArrayConverter::ConvertTo(ITypeDescriptorContext ^ context, CultureInfo ^ culture, Object ^ value, Type ^ destinationType)
	{
		if (destinationType != String::typeid)
		{
			return nullptr;
		}
		if (value->GetType()->IsArray)
		{
			return "(Array)";
		}
		return String::Empty;
	}
}  // namespace PeImageClr
