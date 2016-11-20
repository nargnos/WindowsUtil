#pragma once

#include "DelayImportDescriptor.h"
#include "ImportThunk.h"
#include "IteratorBase.h"
namespace PeDecoder
{
	class DelayImportDirectory;
	class DelayImportDirectoryIterator :
		public IteratorBase<
		DelayImportDirectoryIterator,
		_STD forward_iterator_tag,
		DelayImportDescriptor>
	{
	public:
		friend IteratorFriendAccess;
		DelayImportDirectoryIterator(DelayImportDirectory& delayImportDirectory, PImgDelayDescr ptr);

	private:
		bool Equal(const DelayImportDirectoryIterator & val) const;
		void Increment();
		reference Dereference();
		DelayImportDescriptor& GetStore();
		const DelayImportDescriptor& GetStore() const;
		DelayImportDescriptor store_;
	};
}  // namespace PeDecoder