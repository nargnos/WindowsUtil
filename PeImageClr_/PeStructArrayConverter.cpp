#include "stdafx.h"
#include "PeStructArrayConverter.h"
#include "IWrapperArray.h"
#include "IElementName.h"
namespace PeImageClr
{
	inline PeStructArrayConverter::ArrayPropertyDescriptor::ArrayPropertyDescriptor(Type ^ arrayType, Type ^ elementType, int index, String ^ nodeName)
		: SimplePropertyDescriptor(arrayType, "[" + nodeName + "]", elementType, nullptr)
	{
		this->index = index;
	}
	inline Object ^ PeStructArrayConverter::ArrayPropertyDescriptor::GetValue(Object ^ instance)
	{
		if (IWrapperArray::typeid->IsAssignableFrom(instance->GetType()))
		{
			auto tmpWrapper = safe_cast<IWrapperArray^>(instance);
			return tmpWrapper->GetElements()[index];
		}
		return nullptr;
	}
	inline void PeStructArrayConverter::ArrayPropertyDescriptor::SetValue(Object ^ instance, Object ^ value)
	{
	}
	inline PeStructArrayConverter::PeStructArrayConverter()
	{

	}
	inline PropertyDescriptorCollection ^ PeStructArrayConverter::GetProperties(ITypeDescriptorContext ^ context, Object ^ value, array<Attribute^>^ attributes)
	{
		PropertyDescriptorCollection^ result = ShowPropertiesConverter::GetProperties(context, value, attributes);
		if (IWrapperArray::typeid->IsAssignableFrom(value->GetType()))
		{
			auto tmpWrapper = safe_cast<IWrapperArray^>(value);

			auto elemArray = tmpWrapper->GetElements();
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
}  // namespace PeImageClr
