#pragma once
#include "PeImageFwd.h"
#include "ImportDescriptor.h"
#include "ImportThunk.h"
namespace PeDecoder
{
	// ImportDescriptor iterator
	// 节点类型为ImportDescriptor
	class ImportDirectoryIterator :
		public iterator_facade<
		ImportDirectoryIterator,
		ImportDescriptor,
		forward_traversal_tag>
	{
	public:
		friend class iterator_core_access;
		ImportDirectoryIterator(ImportDirectory& importDirectory, PIMAGE_IMPORT_DESCRIPTOR ptr);

	protected:
		bool equal(const ImportDirectoryIterator & val) const;
		void increment();
		reference dereference() const;

		ImportDescriptor& GetStore();
		const ImportDescriptor& GetStore() const;
		ImportDescriptor store_;
	};


}  // namespace PeDecoder
