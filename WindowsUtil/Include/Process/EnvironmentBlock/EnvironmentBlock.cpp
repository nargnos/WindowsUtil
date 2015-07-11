#include "EnvironmentBlock.h"
namespace Process
{
	namespace EnvironmentBlock
	{
		LdrDataTableEntryReader::LdrDataTableEntryReader(LdrDataTableModuleList desList)
			:LdrDataTableEntryReader(NtCurrentPeb->Ldr, desList)
		{}

		LdrDataTableEntryReader::LdrDataTableEntryReader(PPEB_Ex peb, LdrDataTableModuleList desList)
			: LdrDataTableEntryReader(peb->Ldr, desList)
		{}

		LdrDataTableEntryReader::LdrDataTableEntryReader(PPEB_LDR_DATA_Ex ldr, LdrDataTableModuleList desList)
		{
			this->desList = desList;
			switch (desList)
			{
			case LdrDataTableModuleList::InLoadOrderModuleList:
			default:
				ModuleListHead = &ldr->InLoadOrderModuleList;
				break;
			case LdrDataTableModuleList::InMemoryOrderModuleList:
				ModuleListHead = &ldr->InMemoryOrderModuleList;
				break;
			case LdrDataTableModuleList::InInitializationOrderModuleList:
				ModuleListHead = &ldr->InInitializationOrderModuleList;
				break;
			}

			Reset();
		}
		LdrDataTableEntryReader::~LdrDataTableEntryReader()
		{
		}
		bool LdrDataTableEntryReader::Next()
		{
			if (TmpEntry == NULL)
			{
				TmpEntry = ModuleListHead->Flink;
				return true;
			}
			else if (TmpEntry->Flink != ModuleListHead)
			{
				TmpEntry = TmpEntry->Flink;
				return true;
			}
			return false;
		}
		PLDR_DATA_TABLE_ENTRY_Ex LdrDataTableEntryReader::Current()
		{
			if (TmpEntry == NULL)
			{
				return NULL;
			}
			switch (desList)
			{
			case LdrDataTableModuleList::InLoadOrderModuleList:
				return CONTAINING_RECORD(TmpEntry, LDR_DATA_TABLE_ENTRY_Ex, InLoadOrderLinks);
				break;
			case LdrDataTableModuleList::InMemoryOrderModuleList:
				return CONTAINING_RECORD(TmpEntry, LDR_DATA_TABLE_ENTRY_Ex, InMemoryOrderModuleList);
				break;
			case LdrDataTableModuleList::InInitializationOrderModuleList:
				return CONTAINING_RECORD(TmpEntry, LDR_DATA_TABLE_ENTRY_Ex, InInitializationOrderModuleList);
				break;
			default:
				break;
			}
			return NULL;
		}
		void LdrDataTableEntryReader::Reset()
		{
			TmpEntry = NULL;
		}

		HINSTANCE __stdcall FindLoadedModuleHandle(LPCWSTR name)
		{
			assert(name != NULL);
			LdrDataTableEntryReader iterator(LdrDataTableModuleList::InLoadOrderModuleList);
			while (iterator.Next())
			{
				auto current = iterator.Current();
				auto moduleName = current->BaseDllName.Buffer;
				if (moduleName)
				{
					if (_wcsicmp(name, moduleName) == 0)
					{
						return (HMODULE)current->DllBase;
					}
				}
			}
			return NULL;
		}
	}
}