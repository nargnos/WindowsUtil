#pragma once
#include "EnvironmentBlock.h"
#include "LdrDataTableModuleList.h"
namespace Process
{
	namespace EnvironmentBlock
	{

		class LdrDataTableEntryIterator:
			public boost::iterator_facade<LdrDataTableEntryIterator, LDR_DATA_TABLE_ENTRY_Ex, forward_traversal_tag>
		{
		public:
			friend iterator_core_access;
			LdrDataTableEntryIterator(PLIST_ENTRY node, _STD function<PLDR_DATA_TABLE_ENTRY_Ex(PLIST_ENTRY)> dereference);
		
		private:
			bool equal(const LdrDataTableEntryIterator & val) const;
			void increment();
			reference dereference() const;
			_STD function<PLDR_DATA_TABLE_ENTRY_Ex(PLIST_ENTRY)> dereference_;
			PLIST_ENTRY node_;
		};
	}  // namespace EnvironmentBlock
}  // namespace Process
