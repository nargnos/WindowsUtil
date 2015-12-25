#pragma once
#include "..\..\stdafx.h"
#include "FileHeaderWapper.h"
#include "OptionalHeaderWapper.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		ref class PeImage;
		[TypeConverter(NtHeaderConverter::typeid)]
		public ref class NtHeaderWapper :
			public PeStructWapper<PE::PeDecoder::PeStructInstance<PE::NtHeader>>, public IReset
		{
			FileHeaderWapper^ fileHeader;
			IOptionalHeaderWapper^ optionalHeader;
			bool Is32PE();
		public:

			NtHeaderWapper(PeImage^ pe) :PeStructWapperBase(pe)
			{
			}

			property UnmanagedValue<DWORD>^ Signature
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetNtHeader32()->Signature));
				}
			};
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
			virtual void Reset() override
			{
				fileHeader = nullptr;
			}

			// Í¨¹ý PeStructWapper ¼Ì³Ð
			virtual PeStructWapperType & GetUnmanagedStruct() override;
		};

	}
}