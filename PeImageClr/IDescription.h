#pragma once
namespace PeImageClr
{
	using namespace System;
	// 用来获取不方便取到参数
	interface class IDescription
	{
		String^ GetDescription();
		array<String^>^ GetSortList();
	};
}  // namespace PeImageClr
