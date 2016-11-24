#pragma once
#include <Windows.h>
#include <memory>
#include "ImportThunkIterator.h"
namespace PeDecoder
{
	class ImportDirectory;

	class ImportDescriptor
	{
	public:
		friend class ImportDescriptorIterator;
		ImportDescriptor(ImportDirectory& importDirectory, PIMAGE_IMPORT_DESCRIPTOR ptr);

		ImportThunkIterator begin() const;
		ImportThunkIterator end() const;
		PCHAR GetName() const;
		PIMAGE_IMPORT_DESCRIPTOR RawPtr() const;
		virtual ~ImportDescriptor();
	protected:
		PIMAGE_IMPORT_DESCRIPTOR dataPtr_;
		ImportDirectory* importDirectory_;
	};


}  // namespace PeDecoder
