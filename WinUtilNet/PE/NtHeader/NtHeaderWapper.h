#pragma once
#include "..\..\stdafx.h"
#include "FileHeaderWapper.h"
#include "OptionalHeaderWapper.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		ref class PeImage;
		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class NtHeaderWapper :
			public PeStructWapper<PE::PeDecoder::PeStructInstance<PE::NtHeader>>,
			public IPropertiesFilter
		{
			static array<String^>^ sortList;
			FileHeaderWapper^ fileHeader;
			IOptionalHeaderWapper^ optionalHeader;
			bool Is32PE();
		public:

			NtHeaderWapper(PeImage^ pe);
			virtual array<String^>^ GetSortList() override
			{
				if (NtHeaderWapper::sortList == nullptr)
				{
					NtHeaderWapper::sortList = gcnew array<String^>
					{
						"Signature",
							"FileHeader",
							"OptionalHeader32",
							"OptionalHeader64"

					};
				}
				return NtHeaderWapper::sortList;
			}
			property UnmanagedValue<DWORD>^ Signature
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetNtHeader32()->Signature), GetPeBase());
				}
			}; 
			[DisplayNameAttribute("File Header")]
			property FileHeaderWapper^ FileHeader
			{
				FileHeaderWapper^ get()
				{
					if (fileHeader == nullptr)
					{
						fileHeader = gcnew FileHeaderWapper(pe);
					}
					return fileHeader;
				}
			};
			[DisplayNameAttribute("Optional Header")]
			property OptionalHeaderWapper32^ OptionalHeader32
			{
				OptionalHeaderWapper32^ get()
				{
					if (!Is32PE())
					{
						return nullptr;
					}
					if (optionalHeader == nullptr)
					{
						optionalHeader = gcnew OptionalHeaderWapper32(pe);
					}
					return safe_cast<OptionalHeaderWapper32^>(optionalHeader);
				}
			};
			[DisplayNameAttribute("Optional Header")]
			property OptionalHeaderWapper64^ OptionalHeader64
			{
				OptionalHeaderWapper64^ get()
				{
					if (Is32PE())
					{
						return nullptr;
					}
					if (optionalHeader == nullptr)
					{
						optionalHeader = gcnew OptionalHeaderWapper64(pe);
					}
					return safe_cast<OptionalHeaderWapper64^>(optionalHeader);
				}
			};
			virtual PeStructWapperType & GetUnmanagedStruct() override;

			virtual List<String^>^ GetHidePropList() override
			{
				auto result = gcnew List<String^>();
				if (Is32PE())
				{
					result->Add("OptionalHeader64");
				}
				else
				{
					result->Add("OptionalHeader32");
				}
				return result;
			}
		};

	}
}