#include "stdafx.h"
#include "PE\PeImage.h"
#include "PE\Section\SectionWapper.h"
#include "Converters.h"
namespace NAMESPACE {
	using namespace PeDecoderWapper;
	using namespace System::Collections;
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

}