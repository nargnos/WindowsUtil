#pragma once
namespace PeImageClr
{
	using namespace System;
	using namespace System::Globalization;
	using namespace System::Collections;
	using namespace System::ComponentModel;
	public ref class ShowPropertiesConverter :
		public TypeConverter
	{
	public:
		ShowPropertiesConverter();
		virtual PropertyDescriptorCollection^ GetProperties(ITypeDescriptorContext^ context, Object^ value, array<Attribute^>^ attributes) override;
		virtual bool GetPropertiesSupported(ITypeDescriptorContext^ context) override;
		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override;
	};
}  // namespace PeImageClr
