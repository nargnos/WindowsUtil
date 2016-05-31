#pragma once
#include "ShowPropertiesConverter.h"
namespace PeImageClr
{
	using namespace System;
	using namespace System::Globalization;
	using namespace System::Collections;
	using namespace System::ComponentModel;
	using namespace System::Reflection;
	using namespace System::Runtime::InteropServices;
	public ref class PeStructArrayConverter : public ShowPropertiesConverter
	{
		ref class ArrayPropertyDescriptor : TypeConverter::SimplePropertyDescriptor
		{
			int index;
		public:
			ArrayPropertyDescriptor(Type^ arrayType, Type^ elementType, int index, String^ nodeName);
			virtual  Object^ GetValue(Object^ instance) override;
			virtual void SetValue(Object^ instance, Object^ value)override;
		};

	public:
		PeStructArrayConverter();

		virtual  PropertyDescriptorCollection^ GetProperties(ITypeDescriptorContext^ context, Object^ value, array<Attribute^>^ attributes) override;
	};
}  // namespace PeImageClr
