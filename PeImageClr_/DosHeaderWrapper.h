#pragma once
#include "PeStructWrapper.h"
#include "UnmanagedArray.h"
#include "UnmanagedValue.h"

namespace PeImageClr
{
	ref class PeImage;

	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class DosHeaderWrapper :
		public PeStructWrapper<PeDecoder::DosHeader>
	{
		static array<String^>^ sortList;
		UnmanagedArray<WORD>^ e_res2;
		UnmanagedArray<WORD>^ e_res;

	internal:
		virtual PeStructWrapperType & GetUnmanagedStruct() override;
	public:
		DosHeaderWrapper(PeImage^ pe);
		virtual array<String^>^ GetSortList() override;

		[ReadOnlyAttribute(true)]
		property UnmanagedValue<WORD>^ E_magic
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_magic), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_cblp
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_cblp), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_cp
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_cp), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_crlc
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_crlc), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_cparhdr
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_cparhdr), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_minalloc
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_minalloc), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_maxalloc
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_maxalloc), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_ss
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_ss), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_sp
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_sp), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_csum
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_csum), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_ip
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_ip), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_cs
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_cs), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_lfarlc
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_lfarlc), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_ovno
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_ovno), GetPeBase());
			}
		};

		property UnmanagedArray<WORD>^ E_res//[4]
		{
			UnmanagedArray<WORD>^ get()
			{
				if (e_res == nullptr)
				{
					e_res = gcnew UnmanagedArray<WORD>(IntPtr(GetUnmanagedStruct().GetPtr()->e_res), GetPeBase(), 4);
				}
				return e_res;
			}
		};
		property UnmanagedValue<WORD>^ E_oemid
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_oemid), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^ E_oeminfo
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_oeminfo), GetPeBase());
			}
		};

		property UnmanagedArray<WORD>^ E_res2//[10]
		{
			UnmanagedArray<WORD>^ get()
			{
				if (e_res2 == nullptr)
				{
					e_res2 = gcnew UnmanagedArray<WORD>(IntPtr(GetUnmanagedStruct().GetPtr()->e_res2), GetPeBase(), 10);
				}
				return e_res2;
			}
		};
		property UnmanagedValue<LONG>^ E_lfanew
		{
			UnmanagedValue<LONG>^ get()
			{
				return gcnew UnmanagedValue<LONG>(IntPtr(&GetUnmanagedStruct().GetPtr()->e_lfanew), GetPeBase());
			}
		};


	};
}  // namespace PeImageClr
