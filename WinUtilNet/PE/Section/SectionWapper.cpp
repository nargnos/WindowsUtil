#include "..\..\stdafx.h"
#include "SectionWapper.h"
#include "..\PeImage.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		void SectionHeaderArrayWapper::InitArrayList()
		{

			list = gcnew List<IElementName^>(numberOfSections); // 
			auto iter = GetUnmanagedStruct()->CreateIterator();
			while (iter->Next())
			{
				list->Add(gcnew SectionHeaderWapper(IntPtr(iter->Current()), pe->BaseAddress));
			}
		}
		SectionHeaderArrayWapper::SectionHeaderArrayWapper(PeImage ^ pe) :PeStructWapperBase(pe)
		{
			list = nullptr;
			numberOfSections = pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()->FileHeader.NumberOfSections;

			PVOID sectionAddr = NULL;
			if (pe->HasNtHeader32)
			{
				sectionAddr = IMAGE_FIRST_SECTION((PIMAGE_NT_HEADERS32)(&pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()->Signature));
			}
			else
			{
				sectionAddr = IMAGE_FIRST_SECTION((PIMAGE_NT_HEADERS64)(&pe->GetPeDecoder()->GetNtHeader->GetNtHeader64()->Signature));
			}
			SetDescription(IntPtr(sectionAddr), GetPeBase(), sizeof(IMAGE_SECTION_HEADER)*numberOfSections);

		}
		SectionHeaderArrayWapper::PeStructWapperType & SectionHeaderArrayWapper::GetUnmanagedStruct()
		{
			return pe->GetPeDecoder()->GetSection;
		}

		System::Collections::Generic::IList<IElementName^>^ SectionHeaderArrayWapper::GetElements()
		{
			if (list == nullptr)
			{
				InitArrayList();
			}
			return list;
		}


		String ^ SectionHeaderWapper::GetName()
		{
			return Name->String;
		}

	}
}