#pragma once
#include "..\..\stdafx.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		ref class PeImage;

		[TypeConverter(DosHeaderConverter::typeid)]
		public ref class DosHeaderWapper :
			public PeStructWapper<PE::PeDecoder::PeStructInstance<PE::DosHeader>>, public IReset
		{
			UnmanagedArray<WORD>^ e_res2;
			UnmanagedArray<WORD>^ e_res;
		internal:
			virtual PeStructWapperType & GetUnmanagedStruct() override;
		public:
			DosHeaderWapper(PeImage^ pe):PeStructWapperBase(pe)
			{
				Reset();
			}
			[ReadOnlyAttribute(true)]
			property UnmanagedValue<WORD>^ E_magic
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_magic));
				}
			};
			property UnmanagedValue<WORD>^ E_cblp
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_cblp));
				}
			};
			property UnmanagedValue<WORD>^ E_cp
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_cp));
				}
			};
			property UnmanagedValue<WORD>^ E_crlc
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_crlc));
				}
			};
			property UnmanagedValue<WORD>^ E_cparhdr
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_cparhdr));
				}
			};
			property UnmanagedValue<WORD>^ E_minalloc
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_minalloc));
				}
			};
			property UnmanagedValue<WORD>^ E_maxalloc
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_maxalloc));
				}
			};
			property UnmanagedValue<WORD>^ E_ss
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_ss));
				}
			};
			property UnmanagedValue<WORD>^ E_sp
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_sp));
				}
			};
			property UnmanagedValue<WORD>^ E_csum
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_csum));
				}
			};
			property UnmanagedValue<WORD>^ E_ip
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_ip));
				}
			};
			property UnmanagedValue<WORD>^ E_cs
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_cs));
				}
			};
			property UnmanagedValue<WORD>^ E_lfarlc
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_lfarlc));
				}
			};
			property UnmanagedValue<WORD>^ E_ovno
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_ovno));
				}
			};

			property UnmanagedArray<WORD>^ E_res//[4]
			{
				UnmanagedArray<WORD>^ get()
				{
					if (e_res == nullptr)
					{
						e_res = gcnew UnmanagedArray<WORD>(IntPtr(GetUnmanagedStruct()->GetValue()->e_res), 4);
					}
					return e_res;
				}
			};
			property UnmanagedValue<WORD>^ E_oemid
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_oemid));
				}
			};
			property UnmanagedValue<WORD>^ E_oeminfo
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_oeminfo));
				}
			};

			property UnmanagedArray<WORD>^ E_res2//[10]
			{
				UnmanagedArray<WORD>^ get()
				{
					if (e_res2 == nullptr)
					{
						e_res2 = gcnew UnmanagedArray<WORD>(IntPtr(GetUnmanagedStruct()->GetValue()->e_res2), 10);
					}
					return e_res2;
				}
			};
			property UnmanagedValue<LONG>^ E_lfanew
			{
				UnmanagedValue<LONG>^ get()
				{
					return gcnew UnmanagedValue<LONG>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_lfanew));
				}
			};

			UnmanagedByteArray^ dosStub;
			property UnmanagedByteArray^ DosStub //
			{
				UnmanagedByteArray^ get()
				{
					if (dosStub == nullptr)
					{
						auto lfanew = &GetUnmanagedStruct()->GetValue()->e_lfanew;
						auto ptr = IntPtr(lfanew);
						ptr += sizeof(*lfanew);
						auto dosStubSize = *lfanew-sizeof(IMAGE_DOS_HEADER);
						dosStub = gcnew UnmanagedByteArray(ptr, dosStubSize);
					}
					return dosStub;
				}
			};
			virtual void Reset() override;


};

	}
}