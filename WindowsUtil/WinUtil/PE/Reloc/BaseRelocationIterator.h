#pragma once
#include "TypeOffsetIterator.h"
namespace PE
{
	class RelocDirectory;
	class BaseRelocationIterator :
		public IIterator<PIMAGE_BASE_RELOCATION>,
		public GetIterator<TypeOffsetIterator, BaseRelocationIterator>
	{
		PIMAGE_BASE_RELOCATION startReloc;
		PIMAGE_BASE_RELOCATION currentReloc;
		PIMAGE_BASE_RELOCATION endReloc;
	public:
		friend GetIteratorBase::Iterator;
		BaseRelocationIterator(RelocDirectory& reloc);
		~BaseRelocationIterator();
		
		
		bool Next();
		PIMAGE_BASE_RELOCATION Current();
		
		void Reset();
		
	};


}