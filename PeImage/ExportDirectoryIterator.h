#pragma once

#include "ExportIteratorNode.h"
#include "IteratorBase.h"
namespace PeDecoder
{
	class ExportDirectoryIterator :
		public IteratorBase<
		ExportDirectoryIterator,
		_STD random_access_iterator_tag,
		ExportIteratorNode,
		ptrdiff_t,
		ExportIteratorNode,
		ExportIteratorNode>
	{
	public:
		friend IteratorFriendAccess;
		ExportDirectoryIterator(const ExportDirectory& directory, DWORD index);
		virtual ~ExportDirectoryIterator();
	protected:
		bool Equal(const ExportDirectoryIterator & val) const;
		void Increment();
		void Decrement();
		void Advance(int n);
		difference_type DistanceTo(const ExportDirectoryIterator & val) const;
		reference Dereference();
		pointer AddressOf();
		bool InRange() const;
		const ExportDirectory* directory_;
		difference_type index_;
	};
}  // namespace PeDecoder
