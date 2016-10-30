#pragma once
#include "PeImageFwd.h"
#include "ExportIteratorNode.h"
#include "IteratorBase.h"
namespace PeDecoder
{
	class ExportDirectoryIterator :
		public IteratorBase<
		ExportDirectoryIterator,
		_STD random_access_iterator_tag,
		ExportIteratorNode>
	{
	public:
		friend IteratorFriendAccess;
		ExportDirectoryIterator(ExportDirectory& directory, DWORD index);
	
	protected:
		bool Equal(const ExportDirectoryIterator & val) const;
		void Increment();
		void Decrement();
		void Advance(int n);
		difference_type DistanceTo(const ExportDirectoryIterator & val) const;
		reference Dereference();

		bool InRange() const;

		ExportIteratorNode& GetStore();
		const ExportIteratorNode& GetStore() const;
		ExportIteratorNode store_;
	};
}  // namespace PeDecoder
