#pragma once
#include <memory>
#include "IteratorBase.h"
#include "ImportDescriptor.h"
namespace PeDecoder
{
	class ImportDirectory;
	// ImportDescriptor iterator
	// 节点类型为ImportDescriptor
	class ImportDescriptorIterator :
		public IteratorBase<
		ImportDescriptorIterator,
		_STD forward_iterator_tag,
		unique_ptr<ImportDescriptor>,
		ptrdiff_t,
		unique_ptr<ImportDescriptor>,
		unique_ptr<ImportDescriptor>>
	{
	public:
		friend IteratorFriendAccess;
		ImportDescriptorIterator(ImportDirectory& importDirectory, PIMAGE_IMPORT_DESCRIPTOR begin);
		static IMAGE_IMPORT_DESCRIPTOR* FindEndDescriptor(IMAGE_IMPORT_DESCRIPTOR* bgn);
		virtual ~ImportDescriptorIterator();

	protected:
		bool Equal(const TIterator & val) const;
		void Increment();
		unique_ptr<ImportDescriptor> AddressOf();
		unique_ptr<ImportDescriptor> Dereference();

		ImportDirectory* importDirectory_;
		PIMAGE_IMPORT_DESCRIPTOR current_;
#ifdef _DEBUG
		bool CheckRange() const;
		PIMAGE_IMPORT_DESCRIPTOR end_;
#endif // DEBUG

	};


}  // namespace PeDecoder
