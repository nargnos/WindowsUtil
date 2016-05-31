#pragma once
namespace PeImageClr
{
	interface class IElementName;
	public interface class IWrapperArray
	{
		// 成员类型必须为IElementName，cli不知道怎么声明可协变
		System::Collections::Generic::IList<IElementName^>^ GetElements();
	};
}  // namespace PeImageClr
