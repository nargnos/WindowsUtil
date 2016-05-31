#pragma once
#include "PeStructArrayConverter.h"
#include "IWrapperArray.h"
#include "PeStructDescription.h"

namespace PeImageClr
{
	using namespace System::Collections::Generic;
	ref class ExportNameWrapper;

	[TypeConverter(PeStructArrayConverter::typeid)]
	public ref class ExportNameArrayWrapper :
		public IWrapperArray,
		public PeStructDescription
	{
		System::Collections::Generic::IList<IElementName^>^ names;
	public:
		ExportNameArrayWrapper(List<ExportNameWrapper^>^ nameWrappers);
		virtual System::Collections::Generic::IList<IElementName^>^ GetElements();

		virtual array<String^>^ GetSortList() override;

	};

}  // namespace PeImageClr
