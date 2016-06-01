#pragma once
#include "PeImageFwd.h"
namespace PeDecoder
{
	class BaseRelocation
	{
	public:
		friend class RelocDirectoryIterator;
		typedef TypeOffsetIterator interator;
		BaseRelocation(RelocDirectory& relocDirectory, PIMAGE_BASE_RELOCATION ptr);
		interator begin();
		interator end();
		PIMAGE_BASE_RELOCATION GetPtr() const;
		DWORD GetCount() const;
	protected:
		RelocDirectory* relocDirectory_;
		PIMAGE_BASE_RELOCATION ptr_;
	};

}  // namespace PeDecoder
