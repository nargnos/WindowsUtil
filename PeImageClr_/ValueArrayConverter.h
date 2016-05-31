#pragma once
namespace PeImageClr
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Globalization;
	public ref class ValueArrayConverter : public ArrayConverter
	{
	public:
		ValueArrayConverter();
		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override;
	};
}  // namespace PeImageClr
