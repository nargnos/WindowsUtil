#pragma once
#include "PeImageFwd.h"
#include "BaseRelocation.h"
namespace PeDecoder
{
	class RelocDirectoryIterator :
		public iterator_facade<RelocDirectoryIterator, BaseRelocation, forward_traversal_tag>
	{
	public:
		friend class iterator_core_access;
		RelocDirectoryIterator(RelocDirectory& relocDirectory, PIMAGE_BASE_RELOCATION ptr);
	protected:
		bool equal(const RelocDirectoryIterator & val) const;
		void increment();
		reference dereference() const;
		bool InRange() const;

		const BaseRelocation& GetStore() const;
		BaseRelocation& GetStore();
		BaseRelocation store_;
	};
}  // namespace PeDecoder
