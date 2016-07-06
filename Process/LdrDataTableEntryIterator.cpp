#include "stdafx.h"
#include "LdrDataTableEntryIterator.h"
namespace Process
{
	namespace EnvironmentBlock
	{
		LdrDataTableEntryIterator::LdrDataTableEntryIterator(PLIST_ENTRY node, std::function<PLDR_DATA_TABLE_ENTRY_Ex(PLIST_ENTRY)> dereference) :
			node_(node),
			dereference_(dereference)
		{
		}
		bool LdrDataTableEntryIterator::equal(const LdrDataTableEntryIterator & val) const
		{
			return node_ == val.node_;
		}
		void LdrDataTableEntryIterator::increment()
		{
			node_=node_->Blink;
		}
		LdrDataTableEntryIterator::reference LdrDataTableEntryIterator::dereference() const
		{
			return *dereference_(node_);
		}
	}  // namespace EnvironmentBlock
}  // namespace Process
