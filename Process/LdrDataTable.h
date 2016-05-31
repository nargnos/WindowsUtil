#pragma once
#include "EnvironmentBlock.h"
#include "LdrDataTableModuleList.h"
#include "LdrDataTableEntryIterator.h"
namespace Process
{
	namespace EnvironmentBlock
	{
		// ldr双链表迭代器，可以用3种方式遍历
		class LdrDataTable
		{
		public:

			explicit LdrDataTable(LdrDataTableModuleList desList);
			LdrDataTable(PPEB_Ex peb, LdrDataTableModuleList desList);
			LdrDataTable(PPEB_LDR_DATA_Ex ldr, LdrDataTableModuleList desList);


			LdrDataTableEntryIterator begin();
			LdrDataTableEntryIterator end();

		private:
			_STD function<PLDR_DATA_TABLE_ENTRY_Ex(PLIST_ENTRY)> dereference_;
			PPEB_LDR_DATA_Ex ldr_;
			PLIST_ENTRY begin_;
			PLIST_ENTRY end_;

			LdrDataTableModuleList desList_;
		};

		

	}  // namespace EnvironmentBlock
}  // namespace Process
