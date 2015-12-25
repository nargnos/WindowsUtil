#pragma once
namespace NAMESPACE {
	using namespace System::Globalization;
	using namespace System::Reflection;
	namespace PeDecoderWapper
	{
		ref class DosHeaderWapper;
	}
	public ref class ShowPropertiesConverter :
		public TypeConverter
	{
		array<String^>^ sortList;
	protected:
		void SetSortList(array<String^>^ list)
		{
			sortList = list;
		}
	public:
		ShowPropertiesConverter()
		{
			sortList = nullptr;
		}
		virtual PropertyDescriptorCollection^ GetProperties(ITypeDescriptorContext^ context, Object^ value, array<Attribute^>^ attributes) override
		{
			if (sortList == nullptr || sortList->Length == 0)
			{
				return TypeDescriptor::GetProperties(value, attributes);
			}
			return TypeDescriptor::GetProperties(value, attributes)->Sort(sortList);
		}
		virtual bool GetPropertiesSupported(ITypeDescriptorContext^ context) override
		{
			return true;
		}
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
						format = "X" + 2 * Marshal::SizeOf(value);
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


	public ref class UnmanagedArrayConverter : public ShowPropertiesConverter
	{
	public:
		UnmanagedArrayConverter()
		{
			SetSortList(gcnew array<String^>
			{
				"Offset",
					"Length",
					"Array"
			});
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
			if (value->GetType()->IsArray)
			{
				return "(Array)";
			}
			return String::Empty;
		}
	};
	public ref class EnumHexConverter : public EnumConverter
	{
	public:
		EnumHexConverter(Type^ type):EnumConverter(type)
		{
		}
		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override
		{
			return String::Format("{0} ({1:X4})", EnumConverter::ConvertTo(context, culture, value, destinationType),Convert::ToInt32(value));
		}
		virtual  Object^ ConvertFrom(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value) override
		{
			if (value->GetType() == String::typeid)
			{
				auto str = safe_cast<String^>(value);
				return EnumConverter::ConvertFrom(context, culture,   str->Remove(str->Length - 7, 7));
			}
			return EnumConverter::ConvertFrom(context, culture, value);
		}
	};
	public ref class UnmanagedValueConverter : public ShowPropertiesConverter
	{
	public:
		UnmanagedValueConverter()
		{
			SetSortList(gcnew array<String^>
			{
				"Offset",
					"value"
			});
		}
	};

	public ref class PeImageConverter : public ShowPropertiesConverter
	{
	public:
		PeImageConverter()
		{
			SetSortList(gcnew array<String^>
			{
				"IsMapped",
					"HasNtHeader32",
					"BaseAddress",
					"DosHeader",
					"NtHeader"
			});
		}
	};


	public ref class DosHeaderConverter : public ShowPropertiesConverter
	{
	public:
		DosHeaderConverter()
		{
			SetSortList(gcnew array<String^>
			{
				"E_magic",
					"E_cblp",
					"E_cp",
					"E_crlc",
					"E_cparhdr",
					"E_minalloc",
					"E_maxalloc",
					"E_ss",
					"E_sp",
					"E_csum",
					"E_ip",
					"E_cs",
					"E_lfarlc",
					"E_ovno",
					"E_res",
					"E_oemid",
					"E_oeminfo",
					"E_res2",
					"E_lfanew"
			});
		}

	};


	public ref class NtHeaderConverter : public ShowPropertiesConverter
	{
	public:
		NtHeaderConverter()
		{
			SetSortList(gcnew array<String^>
			{
				"Signature",
					"FileHeader"
			});
		}
	};
	public ref class FileHeaderConverter : public ShowPropertiesConverter
	{
	public:
		FileHeaderConverter()
		{
			SetSortList(gcnew array<String^>
			{
				"Machine",
					"NumberOfSections",
					"TimeDateStamp",
					"PointerToSymbolTable",
					"NumberOfSymbols",
					"SizeOfOptionalHeader",
					"Characteristics"
			});
		}
	};
	public ref class OptionalHeaderConverter : public ShowPropertiesConverter
	{
	public:
		OptionalHeaderConverter()
		{
			SetSortList(gcnew array<String^>
			{
				"Magic",
					"MajorLinkerVersion",
					"MinorLinkerVersion",
					"SizeOfCode",
					"SizeOfInitializedData",
					"SizeOfUninitializedData",
					"AddressOfEntryPoint",
					"BaseOfCode",
					"BaseOfData",
					"ImageBase",
					"SectionAlignment",
					"FileAlignment",
					"MajorOperatingSystemVersion",
					"MinorOperatingSystemVersion",
					"MajorImageVersion",
					"MinorImageVersion",
					"MajorSubsystemVersion",
					"MinorSubsystemVersion",
					"Win32VersionValue",
					"SizeOfImage",
					"SizeOfHeaders",
					"CheckSum",
					"Subsystem",
					"DllCharacteristics",
					"SizeOfStackReserve",
					"SizeOfStackCommit",
					"SizeOfHeapReserve",
					"SizeOfHeapCommit",
					"LoaderFlags",
					"NumberOfRvaAndSizes"
			});
		}
	};

}