#pragma once
#include "IWrapperArray.h"
#include "PeStructWrapper.h"
#include "PeStructArrayConverter.h"
namespace PeImageClr
{
	// 导出表函数数组， 读导出表包括无名函数，解析用
	[TypeConverter(PeStructArrayConverter::typeid)]
	public ref class ExportFuncArrayWrapper :
		public IWrapperArray,
		public PeStructWrapper<PeDecoder::ExportDirectory>
	{
		System::Collections::Generic::IList<IElementName^>^ list;
		void InitArrayList();
	public:
		virtual PeStructWrapperType & GetUnmanagedStruct() override;
		virtual array<String^>^ GetSortList() override;
		virtual System::Collections::Generic::IList<IElementName^>^ GetElements() override;

		ExportFuncArrayWrapper(PeImage^ pe);
		virtual String ^ GetDescription() override;
	};
}  // namespace PeImageClr
