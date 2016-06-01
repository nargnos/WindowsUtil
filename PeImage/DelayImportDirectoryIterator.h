#pragma once
#include "PeImageFwd.h"
#include "DelayImportDescriptor.h"
#include "ImportThunk.h"
namespace PeDecoder
{
	class DelayImportDirectoryIterator :
		public iterator_facade<
		DelayImportDirectoryIterator,
		DelayImportDescriptor,
		forward_traversal_tag>
	{
	public:
		friend class iterator_core_access;
		DelayImportDirectoryIterator(DelayImportDirectory& delayImportDirectory, PImgDelayDescr ptr);

	private:
		bool equal(const DelayImportDirectoryIterator & val) const;
		void increment();
		reference dereference() const;
		DelayImportDescriptor& GetStore();
		const DelayImportDescriptor& GetStore() const;
		DelayImportDescriptor store_;
	};
}  // namespace PeDecoder