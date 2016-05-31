#include "stdafx.h"
#include "ShowPropertiesConverter.h"
#include "IDescription.h"
#include "IPropertiesFilter.h"
namespace PeImageClr
{
	ShowPropertiesConverter::ShowPropertiesConverter()
	{
	}

	PropertyDescriptorCollection ^ ShowPropertiesConverter::GetProperties(ITypeDescriptorContext ^ context, Object ^ value, array<Attribute^>^ attributes)
	{
		// 这东西排序后就可以删东西了，反编译查看是因为没有设置readonly，是.net类库bug吗
		PropertyDescriptorCollection ^ result = TypeDescriptor::GetProperties(value, attributes)->Sort();
		
		if (IDescription::typeid->IsAssignableFrom(value->GetType()))
		{
			auto des = safe_cast<IDescription^>(value);

			auto sortList = des->GetSortList();
			if (sortList != nullptr && sortList->Length > 0)
			{
				result = result->Sort(sortList);
			}

		}
		if (IPropertiesFilter::typeid->IsAssignableFrom(value->GetType()))
		{
			auto filter = safe_cast<IPropertiesFilter^>(value)->GetHidePropList();
			List<PropertyDescriptor^>^ del = gcnew List<PropertyDescriptor^>();
			for each (String^ var in filter)
			{
				auto tmp = result->Find(var, false);
				if (tmp != nullptr)
				{
					del->Add(tmp);
				}
			}

			for each (auto var in del)
			{
				result->Remove(var);
			}
		}

		return result;
	}

	bool ShowPropertiesConverter::GetPropertiesSupported(ITypeDescriptorContext ^ context)
	{
		return true;
	}

	Object ^ ShowPropertiesConverter::ConvertTo(ITypeDescriptorContext ^ context, CultureInfo ^ culture, Object ^ value, Type ^ destinationType)
	{
		if (value == nullptr)
		{
			return "[Null]";
		}
		if (destinationType != String::typeid)
		{
			return nullptr;
		}
		if (!IDescription::typeid->IsAssignableFrom(value->GetType()))
		{
			return TypeConverter::ConvertTo(context, culture, value, destinationType);
		}

		auto showProperties = safe_cast<IDescription^>(value);
		return showProperties->GetDescription();
	}

}  // namespace PeImageClr

