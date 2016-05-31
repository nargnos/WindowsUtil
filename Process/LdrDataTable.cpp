#include "stdafx.h"
#include "LdrDataTable.h"

namespace Process
{
	namespace EnvironmentBlock
	{
		LdrDataTable::LdrDataTable(LdrDataTableModuleList desList)
			:LdrDataTable(NtCurrentPeb->Ldr, desList)
		{
		}
		LdrDataTable::LdrDataTable(PPEB_Ex peb, LdrDataTableModuleList desList)
			: LdrDataTable(peb->Ldr, desList)
		{
		}
		LdrDataTable::LdrDataTable(PPEB_LDR_DATA_Ex ldr, LdrDataTableModuleList desList) :
			ldr_(ldr),
			desList_(desList)
		{
			switch (desList)
			{
			case LdrDataTableModuleList::InLoadOrderModuleList:
			default:
				end_ = &ldr->InLoadOrderModuleList;
				dereference_ = [](PLIST_ENTRY ptr)
				{
					return CONTAINING_RECORD(ptr, LDR_DATA_TABLE_ENTRY_Ex, InLoadOrderLinks);
				};
				break;
			case LdrDataTableModuleList::InMemoryOrderModuleList:
				end_ = &ldr->InMemoryOrderModuleList;
				dereference_ = [](PLIST_ENTRY ptr)
				{
					return CONTAINING_RECORD(ptr, LDR_DATA_TABLE_ENTRY_Ex, InMemoryOrderModuleList);
				};
				break;
			case LdrDataTableModuleList::InInitializationOrderModuleList:
				end_ = &ldr->InInitializationOrderModuleList;
				dereference_ = [](PLIST_ENTRY ptr)
				{
					return CONTAINING_RECORD(ptr, LDR_DATA_TABLE_ENTRY_Ex, InInitializationOrderModuleList);
				};
				break;
			}
			begin_ = end_->Blink;
		}
		LdrDataTableEntryIterator LdrDataTable::begin()
		{
			return LdrDataTableEntryIterator(begin_, dereference_);
		}
		LdrDataTableEntryIterator LdrDataTable::end()
		{
			return LdrDataTableEntryIterator(end_, dereference_);
		}
	}  // namespace EnvironmentBlock
}  // namespace Process
