#pragma once
#include "IElementName.h"
#include "PeStructDescription.h"
#include "UnmanagedString.h"
#include "UnmanagedValue.h"
namespace PeImageClr
{
	using namespace System;
	using namespace System::Collections::Generic;
	ref class PeImage;
	public ref class ExportNameWrapper :
		public IElementName,
		public PeStructDescription
	{
		IntPtr nameRva;
		IntPtr nameOrdinal;
		PeImage^ pe;
		PVOID GetNamePtr();
	public:
		ExportNameWrapper(IntPtr nameRva, IntPtr nameOrdinal, PeImage^ pe);
		virtual String ^ GetName();

		virtual array<String^>^ GetSortList() override;
		property UnmanagedValue<DWORD>^ NameRVA
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(nameRva, base);
			}
		}
		property UnmanagedValue<WORD>^ NameOrdinal
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(nameOrdinal, base);
			}
		}
		property UnmanagedString^ Name
		{
			UnmanagedString^ get()
			{
				return gcnew UnmanagedString(IntPtr(GetNamePtr()), base, 0);//
			}
		}
	};
}  // namespace PeImageClr
