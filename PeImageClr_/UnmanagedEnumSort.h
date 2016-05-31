#pragma once
namespace PeImageClr
{
	using namespace System;
	public ref class UnmanagedEnumSort
	{
		static array<String^>^ sortList;
		UnmanagedEnumSort();
	public:
		static array<String^>^ GetSortList();
	};
}  // namespace PeImageClr
