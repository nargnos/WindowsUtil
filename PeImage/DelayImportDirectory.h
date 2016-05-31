#pragma once
#include "PeImageFwd.h"
#include "DirectoryBase.h"
#include "DelayImportDescriptor.h"
#include "ImportThunk.h"
namespace PeDecoder
{
	// UNDONE: 
	class DelayImportDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::DelayImport>
	{
	public:
		class iterator;
		DelayImportDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr);
		iterator begin();
		iterator end();
	};
	class DelayImportDirectory::iterator:
		public iterator_facade<
		DelayImportDirectory::iterator,
		DelayImportDescriptor,
		forward_traversal_tag,
		const DelayImportDescriptor&>,
		protected DelayImportDescriptor
	{
	public:
		friend class iterator_core_access;
		iterator(DelayImportDirectory& delayImportDirectory, PImgDelayDescr ptr);

	private:
		bool equal(const iterator & val) const;
		void increment();
		reference dereference() const;
	};
}  // namespace PeDecoder
