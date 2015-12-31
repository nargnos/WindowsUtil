#pragma once
namespace NAMESPACE {
	using namespace System::Globalization;
	using namespace System::Reflection;
	using namespace System::Collections::Generic;
	// 用来获取不方便取到参数
	interface class IDescription
	{
		String^ GetDescription();
		array<String^>^ GetSortList();
	};

	// 设置条件隐藏
	public interface class IPropertiesFilter
	{
		 List<String^>^ GetHidePropList();
	};

	public ref class ShowPropertiesConverter :
		public TypeConverter
	{
	public:
		ShowPropertiesConverter();
		virtual PropertyDescriptorCollection^ GetProperties(ITypeDescriptorContext^ context, Object^ value, array<Attribute^>^ attributes) override;
		virtual bool GetPropertiesSupported(ITypeDescriptorContext^ context) override;
		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override;
	};
	// FIX: 在64位程序读文件时的偏移字长有疑问
	public ref class ValueConverter :public TypeConverter
	{
		MethodInfo^ parseMethod = nullptr;
		String^ format;
	public:
		virtual bool CanConvertFrom(ITypeDescriptorContext^ context, Type^ sourceType) override
		{
			if (sourceType == String::typeid)
			{
				return context->PropertyDescriptor->PropertyType != IntPtr::typeid;
			}
			else
			{
				return TypeConverter::CanConvertFrom(context, sourceType);
			}
		}

		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override
		{
			auto propType = value->GetType();
			if (propType->IsValueType && propType->IsPrimitive)
			{
				if (propType == IntPtr::typeid)
				{
					if (String::IsNullOrEmpty(format))
					{
						format = "X" + 2 * IntPtr::Size;
					}
					return ((IntPtr^)value)->ToString(format);
				}
				else
				{
					if (String::IsNullOrEmpty(format))
					{
						format = "{0:X" + 2 * Marshal::SizeOf(value) + "}";
					}
					return String::Format(format, value);
				}
			}
			return TypeConverter::ConvertTo(context, culture, value, destinationType);
		}
		// intptr 不转换
		virtual  Object^ ConvertFrom(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value) override
		{
			if (value->GetType() == String::typeid)
			{
				if (parseMethod == nullptr)
				{
					auto propType = context->PropertyDescriptor->PropertyType;
					if (propType->IsValueType && propType->IsPrimitive)
					{
						parseMethod = propType->GetMethod("Parse", gcnew array<Type^>{ String::typeid, NumberStyles::typeid });
					}
				}
				return parseMethod->Invoke(nullptr, gcnew array<Object^>{ value, NumberStyles::HexNumber });
			}
			else
			{
				return TypeConverter::ConvertFrom(context, culture, value);
			}
		}
	};

	public ref class ValueArrayConverter : public ArrayConverter
	{
	public:
		ValueArrayConverter()
		{
		}
		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override
		{
			if (destinationType != String::typeid)
			{
				return nullptr;
			}
			if (value->GetType()->IsArray)
			{
				return "(Array)";
			}
			return String::Empty;
		}
	};
	public ref class EnumHexConverter : public EnumConverter
	{
		String^ formatStr;
	public:
		EnumHexConverter(Type^ type) :EnumConverter(type)
		{
			Debug::Assert(type->IsEnum);
		}
		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override
		{
			if (destinationType != String::typeid)
			{
				return nullptr;
			}
			if (String::IsNullOrEmpty(formatStr))
			{
				formatStr = "{0} ({1:X" + sizeof(value) + "})";
			}
			return String::Format(formatStr, EnumConverter::ConvertTo(context, culture, value, destinationType), Convert::ToInt32(value));
		}
		virtual  Object^ ConvertFrom(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value) override
		{
			if (value->GetType() == String::typeid)
			{
				auto str = safe_cast<String^>(value);
				return EnumConverter::ConvertFrom(context, culture, str->Remove(str->Length - 7, 7));
			}
			return EnumConverter::ConvertFrom(context, culture, value);
		}
	};


	//public ref class SectionHeaderArrayConverter : public ShowPropertiesConverter
	//{
	//	ref class ArrayPropertyDescriptor : TypeConverter::SimplePropertyDescriptor
	//	{
	//		int index;
	//	public:
	//		ArrayPropertyDescriptor(Type^ arrayType, Type^ elementType, int index, String^ sectionName);
	//		virtual  Object^ GetValue(Object^ instance) override;
	//		virtual void SetValue(Object^ instance, Object^ value)override
	//		{
	//			/*if (instance is Array)
	//			{
	//				Array array = (Array)instance;
	//				if (array.GetLength(0) > this.index)
	//				{
	//					array.SetValue(value, this.index);
	//				}
	//				this.OnValueChanged(instance, EventArgs.Empty);
	//			}*/
	//		}
	//	};

	//public:
	//	SectionHeaderArrayConverter()
	//	{
	//	}

	//	virtual  PropertyDescriptorCollection^ GetProperties(ITypeDescriptorContext^ context, Object^ value, array<Attribute^>^ attributes) override;
	//};

	public interface class IWapperArray
	{
		// 成员类型必须为IElementName，cli不知道怎么声明可协变
		System::Collections::Generic::IList<Object^>^ GetElements();
	};
	public interface class IElementName
	{
		String^ GetName();
	};
	
	public ref class PeStructArrayConverter : public ShowPropertiesConverter
	{
		ref class ArrayPropertyDescriptor : TypeConverter::SimplePropertyDescriptor
		{
			int index;
		public:
			ArrayPropertyDescriptor(Type^ arrayType, Type^ elementType, int index, String^ nodeName);
			virtual  Object^ GetValue(Object^ instance) override;
			virtual void SetValue(Object^ instance, Object^ value)override
			{
			}
		};

	public:
		PeStructArrayConverter()
		{

		}

		virtual  PropertyDescriptorCollection^ GetProperties(ITypeDescriptorContext^ context, Object^ value, array<Attribute^>^ attributes) override;
	};
}