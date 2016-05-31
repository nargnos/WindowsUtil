// 这是主 DLL 文件。

#include "stdafx.h"

#include "PeImage.h"


namespace PeImageClr
{
	PeImage::!PeImage()
	{
		if (pe_ != nullptr)
		{
			delete pe_;
		}
		pe_ = nullptr;
	}
	inline PeImage::PeImage(IntPtr ^ ptr, bool isMapped) :
		pe_(new PeDecoder::PeImage(ptr->ToPointer(), isMapped))
	{

	}
	PeImage::~PeImage()
	{
		pe_->~PeImage();
	}
	PeDecoder::PeImage & PeImage::GetPeDecoder()
	{
		return *pe_;
	}
	String ^ PeImage::GetDescription()
	{
		return nullptr;
	}
	inline array<String^>^ PeImage::GetSortList()
	{
		if (PeImage::sortList == nullptr)
		{
			PeImage::sortList = gcnew array<String^>
			{
				"HasNtHeader32",
					"DosHeader",
					"DosStub",
					"NtHeader",
					"SectionHeaders",
					"Export",
					"Import",
			};
		}
		return PeImage::sortList;
	}
	inline List<String^>^ PeImage::GetHidePropList()
	{
		auto result = gcnew List<String^>;
		/*if (!Export)
		{
		result->Add("Export");
		}
		if (!Import)
		{
		result->Add("Import");
		}*/

		return result;
	}
}  // namespace PeImageClr
