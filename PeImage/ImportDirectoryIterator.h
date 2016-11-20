#pragma once

#include "ImportDescriptor.h"
#include "ImportThunk.h"
#include "IteratorBase.h"
namespace PeDecoder
{
	// ImportDescriptor iterator
	// 节点类型为ImportDescriptor
	class ImportDirectoryIterator :
		public IteratorBase<
		ImportDirectoryIterator,
		_STD forward_iterator_tag,
		ImportDescriptor>
	{
	public:
		friend IteratorFriendAccess;
		ImportDirectoryIterator(ImportDirectory& importDirectory, PIMAGE_IMPORT_DESCRIPTOR ptr);

	protected:
		bool Equal(const ImportDirectoryIterator & val) const;
		void Increment();
		reference Dereference();

		ImportDescriptor& GetStore();
		const ImportDescriptor& GetStore() const;
		ImportDescriptor store_;
	};


}  // namespace PeDecoder
