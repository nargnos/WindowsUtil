#pragma once
#include "PeStructWrapper.h"
#include "IPropertiesFilter.h"
//#include ""
namespace PeImageClr
{
	ref class PeImage;
	ref class FileHeaderWrapper;
	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class NtHeaderWrapper :
		public PeStructWrapper<PeDecoder::NtHeader>,
		public IPropertiesFilter
	{
		static array<String^>^ sortList;
		FileHeaderWrapper^ fileHeader;
		IOptionalHeaderWrapper^ optionalHeader;
		bool Is32PE();
	public:

		NtHeaderWrapper(PeImage^ pe);
		virtual array<String^>^ GetSortList() override;
		property UnmanagedValue<DWORD>^ Signature
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetNtHeader32()->Signature), GetPeBase());
			}
		};
		[DisplayNameAttribute("File Header")]
		property FileHeaderWrapper^ FileHeader
		{
			FileHeaderWrapper^ get()
			{
				if (fileHeader == nullptr)
				{
					fileHeader = gcnew FileHeaderWrapper(pe);
				}
				return fileHeader;
			}
		};
		//[DisplayNameAttribute("Optional Header")]
		property OptionalHeaderWrapper32^ OptionalHeader32
		{
			OptionalHeaderWrapper32^ get()
			{
				if (!Is32PE())
				{
					return nullptr;
				}
				if (optionalHeader == nullptr)
				{
					optionalHeader = gcnew OptionalHeaderWrapper32(pe);
				}
				return safe_cast<OptionalHeaderWrapper32^>(optionalHeader);
			}
		};
		//[DisplayNameAttribute("Optional Header")]
		property OptionalHeaderWrapper64^ OptionalHeader64
		{
			OptionalHeaderWrapper64^ get()
			{
				if (Is32PE())
				{
					return nullptr;
				}
				if (optionalHeader == nullptr)
				{
					optionalHeader = gcnew OptionalHeaderWrapper64(pe);
				}
				return safe_cast<OptionalHeaderWrapper64^>(optionalHeader);
			}
		};
		virtual PeStructWrapperType & GetUnmanagedStruct() override;

		virtual List<String^>^ GetHidePropList() override;
	};

}  // namespace PeImageClr
