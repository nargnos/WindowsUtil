#pragma once
#include "..\..\stdafx.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		ref class PeImage;

		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class DosHeaderWapper :
			public PeStructWapper<PE::PeDecoder::PeStructInstance<PE::DosHeader>>
		{
			static array<String^>^ sortList;
			UnmanagedArray<WORD>^ e_res2;
			UnmanagedArray<WORD>^ e_res;

		internal:
			virtual PeStructWapperType & GetUnmanagedStruct() override;
		public:
			DosHeaderWapper(PeImage^ pe);
			virtual array<String^>^ GetSortList() override
			{
				if (DosHeaderWapper::sortList == nullptr)
				{
					DosHeaderWapper::sortList = gcnew array<String^>
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
					};
				}
				return DosHeaderWapper::sortList;
			}

			[ReadOnlyAttribute(true)]
			property UnmanagedValue<WORD>^ E_magic
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_magic), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_cblp
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_cblp), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_cp
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_cp), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_crlc
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_crlc), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_cparhdr
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_cparhdr), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_minalloc
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_minalloc), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_maxalloc
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_maxalloc), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_ss
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_ss), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_sp
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_sp), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_csum
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_csum), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_ip
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_ip), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_cs
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_cs), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_lfarlc
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_lfarlc), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_ovno
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_ovno), GetPeBase());
				}
			};

			property UnmanagedArray<WORD>^ E_res//[4]
			{
				UnmanagedArray<WORD>^ get()
				{
					if (e_res == nullptr)
					{
						e_res = gcnew UnmanagedArray<WORD>(IntPtr(GetUnmanagedStruct()->GetValue()->e_res), GetPeBase(), 4);
					}
					return e_res;
				}
			};
			property UnmanagedValue<WORD>^ E_oemid
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_oemid), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ E_oeminfo
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_oeminfo), GetPeBase());
				}
			};

			property UnmanagedArray<WORD>^ E_res2//[10]
			{
				UnmanagedArray<WORD>^ get()
				{
					if (e_res2 == nullptr)
					{
						e_res2 = gcnew UnmanagedArray<WORD>(IntPtr(GetUnmanagedStruct()->GetValue()->e_res2), GetPeBase(), 10);
					}
					return e_res2;
				}
			};
			property UnmanagedValue<LONG>^ E_lfanew
			{
				UnmanagedValue<LONG>^ get()
				{
					return gcnew UnmanagedValue<LONG>(IntPtr(&GetUnmanagedStruct()->GetValue()->e_lfanew), GetPeBase());
				}
			};


		};

	}
}