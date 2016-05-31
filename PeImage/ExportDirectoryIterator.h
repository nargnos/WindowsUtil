#pragma once
#include "PeImageFwd.h"
#include "ExportIteratorNode.h"
namespace PeDecoder
{
	class ExportDirectoryIterator :
		public iterator_facade<
		ExportDirectoryIterator,
		ExportIteratorNode,
		random_access_traversal_tag>
	{
	public:
		friend class iterator_core_access;
		ExportDirectoryIterator(ExportDirectory& directory, DWORD index);
	
	protected:
		bool equal(const ExportDirectoryIterator & val) const;
		void increment();
		void decrement();
		void advance(int n);
		difference_type distance_to(const ExportDirectoryIterator & val) const;
		reference dereference() const;

		bool InRange() const;

		ExportIteratorNode& GetStore();
		const ExportIteratorNode& GetStore() const;
		ExportIteratorNode store_;
	};
}  // namespace PeDecoder
