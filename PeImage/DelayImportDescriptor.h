#pragma once
#include "ImportThunkIterator.h"
namespace PeDecoder
{
	template<typename> class ImportThunk;
	class DelayImportDirectory;
	class DelayImportDescriptor
	{
	public:
		friend class DelayImportDescriptorIterator;
		DelayImportDescriptor(const DelayImportDirectory& delayImportDirectory, PImgDelayDescr ptr);

		ImportThunkIterator begin() const;
		ImportThunkIterator end() const;
		PCHAR GetName();
		PImgDelayDescr GetPtr() const;
		virtual ~DelayImportDescriptor();
		DelayImportDescriptor* operator->();
		const DelayImportDescriptor* operator->() const;
	private:
		PImgDelayDescr dataPtr_;
		const DelayImportDirectory* delayImportDirectory_;
	};
}  // namespace PeDecoder

