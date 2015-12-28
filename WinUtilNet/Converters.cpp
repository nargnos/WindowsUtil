#include "stdafx.h"
#include "PE\PeImage.h"
#include "PE\Section\SectionWapper.h"
namespace NAMESPACE {
	using namespace PeDecoderWapper;
	inline ShowPropertiesConverter::ShowPropertiesConverter()
	{
	}
	inline PropertyDescriptorCollection ^ ShowPropertiesConverter::GetProperties(ITypeDescriptorContext ^ context, Object ^ value, array<Attribute^>^ attributes)
	{
		PropertyDescriptorCollection ^ result = TypeDescriptor::GetProperties(value, attributes);

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
		if (IDescription::typeid->IsAssignableFrom(value->GetType()))
		{
			auto des = safe_cast<IDescription^>(value);

			auto sortList = des->GetSortList();
			if (sortList != nullptr && sortList->Length > 0)
			{
				result = result->Sort(sortList);
			}

		}
		return result;
	}
	inline bool ShowPropertiesConverter::GetPropertiesSupported(ITypeDescriptorContext ^ context)
	{
		return true;
	}
	inline Object ^ ShowPropertiesConverter::ConvertTo(ITypeDescriptorContext ^ context, CultureInfo ^ culture, Object ^ value, Type ^ destinationType)
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

	PropertyDescriptorCollection ^ SectionHeaderArrayConverter::GetProperties(ITypeDescriptorContext ^ context, Object ^ value, array<Attribute^>^ attributes)
	{
		array<PropertyDescriptor^>^ propArray = nullptr;
		if (value->GetType() == PeDecoderWapper::SectionHeaderArrayWapper::typeid)
		{
			auto tmpWapper = safe_cast<PeDecoderWapper::SectionHeaderArrayWapper^>(value);

			auto sections = tmpWapper->Sections;
			propArray = gcnew array<PropertyDescriptor^>(sections->Count);

			Type^ type = sections->GetType();
			Type^ elementType = PeDecoderWapper::SectionHeaderWapper::typeid;
			for (int i = 0; i < sections->Count; i++)
			{
				propArray[i] = gcnew SectionHeaderArrayConverter::ArrayPropertyDescriptor(type, elementType, i, sections[i]->Name);
			}
		}
		return gcnew PropertyDescriptorCollection(propArray);
	}

	SectionHeaderArrayConverter::ArrayPropertyDescriptor::ArrayPropertyDescriptor(Type ^ arrayType, Type ^ elementType, int index, String ^ sectionName) : SimplePropertyDescriptor(arrayType, "[" + sectionName + "]", elementType, nullptr)
	{
		this->index = index;
	}

	inline Object ^ SectionHeaderArrayConverter::ArrayPropertyDescriptor::GetValue(Object ^ instance)
	{
		if (instance->GetType() == PeDecoderWapper::SectionHeaderArrayWapper::typeid)
		{
			auto tmpWapper = safe_cast<PeDecoderWapper::SectionHeaderArrayWapper^>(instance);
			return tmpWapper->Sections[index];
		}
		return nullptr;
	}

}