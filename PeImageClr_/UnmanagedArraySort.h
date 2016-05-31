#pragma once
namespace PeImageClr
{
	using namespace System;
	public ref class UnmanagedArraySort
	{
		UnmanagedArraySort();
		static array<String^>^ sortList;
	public:
		static array<String^>^ GetSortList();
	};
}  // namespace PeImageClr
