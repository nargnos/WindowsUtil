#include "stdafx.h"
#include "LdrDataTableEntryIterator.h"
namespace Process
{
	namespace EnvironmentBlock
	{
		LdrDataTableEntryIterator::LdrDataTableEntryIterator(PLIST_ENTRY node, std::function<PLDR_DATA_TABLE_ENTRY_Ex(PLIST_ENTRY)> Dereference) :
			node_(node),
			dereference_(Dereference)
		{
		}
		bool LdrDataTableEntryIterator::Equal(const LdrDataTableEntryIterator & val) const
		{
			return node_ == val.node_;
		}
		void LdrDataTableEntryIterator::Increment()
		{
			node_=node_->Blink;
		}
		LdrDataTableEntryIterator::reference LdrDataTableEntryIterator::Dereference() const
		{
			return *dereference_(node_);
		}
	}  // namespace EnvironmentBlock
}  // namespace Process
