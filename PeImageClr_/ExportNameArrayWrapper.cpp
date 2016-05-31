#include "stdafx.h"
#include "ExportNameArrayWrapper.h"
#include "ExportNameWrapper.h"
namespace PeImageClr
{
	 ExportNameArrayWrapper::ExportNameArrayWrapper(List<ExportNameWrapper^>^ nameWrappers)
	{
		// 不支持协变只能转换了
		names = gcnew List<IElementName^>();
		for each (auto var in nameWrappers)
		{
			names->Add(var);
		}
	}
	 System::Collections::Generic::IList<IElementName^>^ ExportNameArrayWrapper::GetElements()
	{
		return names;
	}
	 array<String^>^ ExportNameArrayWrapper::GetSortList()
	{
		return nullptr;
	}
}  // namespace PeImageClr
