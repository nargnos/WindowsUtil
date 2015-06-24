#include "EnvironmentBlock.h"
namespace Peb
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
		case Peb::InLoadOrderModuleList:
		default:
			ModuleListHead = &ldr->InLoadOrderModuleList;
			break;
		case Peb::InMemoryOrderModuleList:
			ModuleListHead = &ldr->InMemoryOrderModuleList;
			break;
		case Peb::InInitializationOrderModuleList:
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
		else if (TmpEntry != ModuleListHead)
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
		case Peb::InLoadOrderModuleList:
			return CONTAINING_RECORD(TmpEntry, LDR_DATA_TABLE_ENTRY_Ex, InLoadOrderLinks);
			break;
		case Peb::InMemoryOrderModuleList:
			return CONTAINING_RECORD(TmpEntry, LDR_DATA_TABLE_ENTRY_Ex, InMemoryOrderModuleList);
			break;
		case Peb::InInitializationOrderModuleList:
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

	HMODULE __stdcall FindLoadedModuleHandle(PWCHAR name)
	{
		LdrDataTableEntryReader iterator(InLoadOrderModuleList);
		while (iterator.Next())
		{
			auto current = iterator.Current();
			if (_wcsicmp(name, current->BaseDllName.Buffer) == 0)
			{
				return (HMODULE)current->DllBase;
			}
		}
		return NULL;
	}
}