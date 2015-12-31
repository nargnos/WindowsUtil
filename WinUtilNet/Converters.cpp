#include "stdafx.h"
#include "PE\PeImage.h"
#include "PE\Section\SectionWapper.h"
namespace NAMESPACE {
	using namespace PeDecoderWapper;
	using namespace System::Collections;
	inline ShowPropertiesConverter::ShowPropertiesConverter()
	{
	}
	inline PropertyDescriptorCollection ^ ShowPropertiesConverter::GetProperties(ITypeDescriptorContext ^ context, Object ^ value, array<Attribute^>^ attributes)
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

	//PropertyDescriptorCollection ^ SectionHeaderArrayConverter::GetProperties(ITypeDescriptorContext ^ context, Object ^ value, array<Attribute^>^ attributes)
	//{
	//	array<PropertyDescriptor^>^ propArray = nullptr;
	//	if (value->GetType() == PeDecoderWapper::SectionHeaderArrayWapper::typeid)
	//	{
	//		auto tmpWapper = safe_cast<PeDecoderWapper::SectionHeaderArrayWapper^>(value);

	//		auto sections = tmpWapper->Sections;
	//		propArray = gcnew array<PropertyDescriptor^>(sections->Count);

	//		Type^ type = sections->GetType();
	//		Type^ elementType = PeDecoderWapper::SectionHeaderWapper::typeid;
	//		for (int i = 0; i < sections->Count; i++)
	//		{
	//			propArray[i] = gcnew SectionHeaderArrayConverter::ArrayPropertyDescriptor(type, elementType, i, sections[i]->Name->String);
	//		}
	//	}
	//	return gcnew PropertyDescriptorCollection(propArray);
	//}

	//SectionHeaderArrayConverter::ArrayPropertyDescriptor::ArrayPropertyDescriptor(Type ^ arrayType, Type ^ elementType, int index, String ^ sectionName) 
	//	: SimplePropertyDescriptor(arrayType, "[" + sectionName + "]", elementType, nullptr) // 用中括号标识，防止有些节名为空时无显示
	//{
	//	this->index = index;
	//}

	//inline Object ^ SectionHeaderArrayConverter::ArrayPropertyDescriptor::GetValue(Object ^ instance)
	//{
	//	if (instance->GetType() == PeDecoderWapper::SectionHeaderArrayWapper::typeid)
	//	{
	//		auto tmpWapper = safe_cast<PeDecoderWapper::SectionHeaderArrayWapper^>(instance);
	//		return tmpWapper->Sections[index];
	//	}
	//	return nullptr;
	//}

	inline PeStructArrayConverter::ArrayPropertyDescriptor::ArrayPropertyDescriptor(Type ^ arrayType, Type ^ elementType, int index, String ^ nodeName)
		: SimplePropertyDescriptor(arrayType, "[" + nodeName + "]", elementType, nullptr)
	{
		this->index = index;
	}

	inline Object ^ PeStructArrayConverter::ArrayPropertyDescriptor::GetValue(Object ^ instance)
	{
		if (IWapperArray::typeid->IsAssignableFrom(instance->GetType()))
		{
			auto tmpWapper = safe_cast<IWapperArray^>(instance);
			return tmpWapper->GetElements()[index];
		}
		return nullptr;
	}

	inline PropertyDescriptorCollection ^ PeStructArrayConverter::GetProperties(ITypeDescriptorContext ^ context, Object ^ value, array<Attribute^>^ attributes)
	{
		PropertyDescriptorCollection^ result = ShowPropertiesConverter::GetProperties(context, value, attributes);
		if (IWapperArray::typeid->IsAssignableFrom(value->GetType()))
		{
			auto tmpWapper = safe_cast<IWapperArray^>(value);

			auto elemArray = tmpWapper->GetElements();
			if (elemArray->Count > 0)
			{
				Type^ arrayType = elemArray->GetType();
				Type^ elemType = elemArray[0]->GetType();

				for (int i = 0; i < elemArray->Count; i++)
				{
					result->Add(gcnew PeStructArrayConverter::ArrayPropertyDescriptor(
						arrayType, 
						elemType, 
						i, 
						safe_cast<IElementName^>(elemArray[i])->GetName())
						);
				}

			}

		}
		return result;
	}

}