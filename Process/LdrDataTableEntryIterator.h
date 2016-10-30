#pragma once
#include "EnvironmentBlock.h"
#include "LdrDataTableModuleList.h"
#include <PeImage\IteratorBase.h>
namespace Process
{
	namespace EnvironmentBlock
	{

		class LdrDataTableEntryIterator:
			public IteratorBase<LdrDataTableEntryIterator,_STD forward_iterator_tag, LDR_DATA_TABLE_ENTRY_Ex>
		{
		public:
			friend IteratorFriendAccess;
			LdrDataTableEntryIterator(PLIST_ENTRY node, _STD function<PLDR_DATA_TABLE_ENTRY_Ex(PLIST_ENTRY)> Dereference);
		
		private:
			bool Equal(const LdrDataTableEntryIterator & val) const;
			void Increment();
			reference Dereference();
			_STD function<PLDR_DATA_TABLE_ENTRY_Ex(PLIST_ENTRY)> dereference_;
			PLIST_ENTRY node_;
		};
	}  // namespace EnvironmentBlock
}  // namespace Process
