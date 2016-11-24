#pragma once

#include "ExportIteratorNode.h"
#include "IteratorBase.h"
namespace PeDecoder
{
	class ExportDirectoryIterator :
		public IteratorBase<
		ExportDirectoryIterator,
		_STD random_access_iterator_tag,
		_STD unique_ptr<ExportIteratorNode>,
		ptrdiff_t,
		_STD unique_ptr<ExportIteratorNode>,
		_STD unique_ptr<ExportIteratorNode>>
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
		DWORD index_;
	};
}  // namespace PeDecoder
