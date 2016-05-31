#pragma once
namespace PeImageClr
{	
	using namespace System;
	using namespace System::Collections::Generic;
	// ÉèÖÃÌõ¼şÒş²Ø
	public interface class IPropertiesFilter
	{
		List<String^>^ GetHidePropList();
	};
}  // namespace PeImageClr
