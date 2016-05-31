#pragma once
namespace PeImageClr
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Globalization;
	using namespace System::Diagnostics;
	public ref class EnumHexConverter : public EnumConverter
	{
		String^ formatStr;
	public:
		EnumHexConverter(Type^ type);
		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override;
		virtual  Object^ ConvertFrom(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value) override;
	};

}  // namespace PeImageClr
