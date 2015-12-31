#include "PeImage.h"

namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		void PeImage::OnPeAttached()
		{
			PeAttached();
		}

		bool PeImage::Attach(IntPtr pePtr, bool isMapped)
		{
			return Attach(pePtr.ToPointer(), isMapped);
		}
		bool PeImage::Attach(PVOID pePtr, bool isMapped)
		{
			auto result = pe->Attach(pePtr, isMapped);
			if (result)
			{
				OnReset();
				OnPeAttached();
			}
			return result;
		}

		String ^ PeImage::GetDescription()
		{
			return nullptr;
		}

		array<String^>^ PeImage::GetSortList()
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

		List<String^>^ PeImage::GetHidePropList()
		{
			auto result = gcnew List<String^>;
			if (!Export)
			{
				result->Add("Export");
			}
			if (!Import)
			{
				result->Add("Import");
			}

			return result;
		}


	}
}