#include "ImportWapper.h"
#include "..\..\stdafx.h"
#include "..\PeImage.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		inline PIMAGE_IMPORT_DESCRIPTOR ImportDescriptorWapper::GetPointer()
		{
			return (PIMAGE_IMPORT_DESCRIPTOR)addr.ToPointer();
		}
		inline PE::PeDecoder * ImportDescriptorWapper::GetPeDecoder()
		{
			return pe->GetPeDecoder();
		}
		inline void ImportThunkArrayWapper::InitArrayList()
		{
			list = gcnew List<IElementName^>();
			auto thunk = new PE::ImportThunkIterator(descriptor, *pe->GetPeDecoder());
			if (pe->HasNtHeader32)
			{
				while (thunk->Next())
				{
					list->Add(gcnew ImportThunkWapper(thunk->CurrentOriginalThunk32(), thunk->CurrentOriginalThunk32(), pe));
				}
			}
			else
			{
				while (thunk->Next())
				{
					list->Add(gcnew ImportThunkWapper(thunk->CurrentOriginalThunk64(), thunk->CurrentOriginalThunk64(), pe));
				}
			}
		}
		inline ImportThunkArrayWapper::ImportThunkArrayWapper(PIMAGE_IMPORT_DESCRIPTOR descriptor, PeImage ^ pe) :descriptor(descriptor), pe(pe)
		{
			this->SetDescription(IntPtr(descriptor), pe->BaseAddress, GetElements()->Count);
		}
		inline System::Collections::Generic::IList<IElementName^>^ ImportThunkArrayWapper::GetElements()
		{
			if (list == nullptr)
			{
				InitArrayList();
			}
			return list;
		}
		inline ImportDescriptorWapper::ImportDescriptorWapper(IntPtr addr, PeImage ^ pe) :pe(pe)
		{
			SetDescription(addr, pe->BaseAddress, 0);
		}
		String ^ ImportDescriptorWapper::GetName()
		{
			return Name->String;
		}
		inline array<String^>^ ImportDescriptorWapper::GetSortList()
		{
			if (ImportDescriptorWapper::sortList == nullptr)
			{
				ImportDescriptorWapper::sortList = gcnew array<String^>
				{
					"Name",
						"OriginalFirstThunk",
						"TimeDateStamp",
						"ForwarderChain",
						"NameRVA",
						"FirstThunk",
						"Functions"
				};
			}
			return ImportDescriptorWapper::sortList;
		}
		inline void ImportDescriptorArrayWapper::InitArrayList()
		{
			list = gcnew List<IElementName^>();
			auto it = GetUnmanagedStruct()->CreateIterator();

			while (it->Next())
			{
				list->Add(gcnew ImportDescriptorWapper(IntPtr(it->Current()), pe));
			}
		}
		inline ImportDescriptorArrayWapper::ImportDescriptorArrayWapper(PeImage ^ pe) :PeStructWapperBase(pe)
		{
			this->SetDescription(IntPtr(GetUnmanagedStruct()->DirectoryEntryToData()), pe->BaseAddress, 0);
		}
		inline array<String^>^ ImportDescriptorArrayWapper::GetSortList()
		{
			return nullptr;
		}
		inline ImportDescriptorArrayWapper::PeStructWapperType & ImportDescriptorArrayWapper::GetUnmanagedStruct()
		{
			return pe->GetPeDecoder()->GetImport;
		}
		System::Collections::Generic::IList<IElementName^>^ ImportDescriptorArrayWapper::GetElements()
		{
			if (list == nullptr)
			{
				InitArrayList();
			}
			return list;
		}
		inline IntPtr ImportThunkWapper::GetBase()
		{
			return pe->BaseAddress;
		}
		inline PIMAGE_IMPORT_BY_NAME ImportThunkWapper::GetNameStruct()
		{
			if (is32)
			{
				auto ot = reinterpret_cast<PIMAGE_THUNK_DATA32>(originalThunk);
				if (PE::IsSnapByOrdinal(ot))
				{
					return nullptr;
				}
				return PE::GetNameStruct(*pe->GetPeDecoder(), ot);
			}
			else
			{
				auto ot = reinterpret_cast<PIMAGE_THUNK_DATA64>(originalThunk);
				if (PE::IsSnapByOrdinal(ot))
				{
					return nullptr;
				}
				return PE::GetNameStruct(*pe->GetPeDecoder(), ot);
			}
			return nullptr;
		}
		array<String^>^ ImportThunkWapper::GetSortList()
		{
			if (ImportThunkWapper::sortList == nullptr)
			{
				ImportThunkWapper::sortList = gcnew array<String^>
				{
					"Name",
						"Hint",
						"Ordinal32",
						"Ordinal64",
						"OriginalThunk32",
						"Thunk32",
						"OriginalThunk64",
						"Thunk64",
				};
			}
			return ImportThunkWapper::sortList;
		}
		String ^ ImportThunkWapper::GetName()
		{
			auto name = Name;
			if (name!=nullptr)
			{
				return name->String;
			}
			else
			{
				return is32 ? Ordinal32.ToString() : Ordinal64.ToString();
			}
		}
		inline ImportThunkWapper::ImportThunkWapper(PIMAGE_THUNK_DATA32 othunk, PIMAGE_THUNK_DATA32 thunk, PeImage ^ pe)
			:originalThunk(othunk), thunk(thunk), pe(pe)
		{
			is32 = pe->HasNtHeader32;
		}
		inline ImportThunkWapper::ImportThunkWapper(PIMAGE_THUNK_DATA64 othunk, PIMAGE_THUNK_DATA64 thunk, PeImage ^ pe)
			: originalThunk(othunk), thunk(thunk), pe(pe)
		{
			is32 = !pe->HasNtHeader32;
		}
		List<String^>^ ImportThunkWapper::GetHidePropList()
		{
			auto result = gcnew List<String^>;
			if (!OriginalThunk32)
			{
				result->Add("OriginalThunk32");
			}
			if (!Thunk32)
			{
				result->Add("Thunk32");
			}
			if (!Ordinal32)
			{
				result->Add("Ordinal32");
			}
			if (!OriginalThunk64)
			{
				result->Add("OriginalThunk64");
			}
			if (!Thunk64)
			{
				result->Add("Thunk64");
			}
			if (!Ordinal64)
			{
				result->Add("Ordinal64");
			}
			if (!Hint)
			{
				result->Add("Hint");
			}
			if (!Name)
			{
				result->Add("Name");
			}
			return result;
		}
		inline String ^ ImportThunkArrayWapper::GetDescription()
		{
			if (addr == IntPtr::Zero)
			{
				return String::Empty;
			}
			auto offset = Offset.ToString("X" + 2 * IntPtr::Size);
			if (structSize == 0)
			{
				return String::Format("[{0}]", offset);
			}
			return String::Format("[{0} (Count: {1})]", offset, structSize);
		}
		array<String^>^ ImportThunkArrayWapper::GetSortList()
		{
			return nullptr;
		}
	}
}