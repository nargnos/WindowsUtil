#pragma once
#include "PeImageFwd.h"
#include "BaseRelocation.h"
#include "IteratorBase.h"
namespace PeDecoder
{
	class RelocDirectoryIterator :
		public IteratorBase<RelocDirectoryIterator,_STD forward_iterator_tag, BaseRelocation>
	{
	public:
		friend IteratorFriendAccess;
		RelocDirectoryIterator(RelocDirectory& relocDirectory, PIMAGE_BASE_RELOCATION ptr);
	protected:
		bool Equal(const RelocDirectoryIterator & val) const;
		void Increment();
		reference Dereference();
		bool InRange() const;

		const BaseRelocation& GetStore() const;
		BaseRelocation& GetStore();
		BaseRelocation store_;
	};
}  // namespace PeDecoder
