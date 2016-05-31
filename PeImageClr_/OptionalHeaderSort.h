#pragma once
namespace PeImageClr
{
	using namespace System;
	public ref class OptionalHeaderSort
	{
		static array<String^>^ sortList;
		OptionalHeaderSort();
	public:
		static array<String^>^ GetSortList();
	};

}  // namespace PeImageClr
