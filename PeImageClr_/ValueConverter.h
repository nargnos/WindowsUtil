#pragma once
namespace PeImageClr
{
	using namespace System;
	using namespace System::Globalization;
	using namespace System::Collections;
	using namespace System::ComponentModel;
	using namespace System::Reflection;
	using namespace System::Runtime::InteropServices;
	// FIX: 在64位程序读文件时的偏移字长有疑问
	public ref class ValueConverter :public TypeConverter
	{
		MethodInfo^ parseMethod = nullptr;
		String^ format;
	public:
		virtual bool CanConvertFrom(ITypeDescriptorContext^ context, Type^ sourceType) override;

		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override;
		// intptr 不转换
		virtual  Object^ ConvertFrom(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value) override;
	};
}  // namespace PeImageClr
