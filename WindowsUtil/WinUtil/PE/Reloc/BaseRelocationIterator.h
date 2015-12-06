#pragma once
#include "../Common/Common.h"
#include "TypeOffsetIterator.h"
namespace PE
{
	template<typename _RelocDirectory>
	class BaseRelocationIterator :
		public IIterator<PIMAGE_BASE_RELOCATION>,
		public GetIterator<TypeOffsetIterator<BaseRelocationIterator<_RelocDirectory>>, BaseRelocationIterator<_RelocDirectory>>
	{
		PIMAGE_BASE_RELOCATION startReloc;
		PIMAGE_BASE_RELOCATION currentReloc;
		PIMAGE_BASE_RELOCATION endReloc;
	public:
		friend TypeOffsetIterator<BaseRelocationIterator<_RelocDirectory>>;
		BaseRelocationIterator(_RelocDirectory& reloc)
		{
			Reset();
			typeOffsetIterator = NULL;
			startReloc = reloc.data;
			endReloc = startReloc + *reloc.size / sizeof(IMAGE_BASE_RELOCATION);
		}
		~BaseRelocationIterator() {}
		
		
		bool Next() 
		{
			if (!startReloc)
			{
				return false;
			}
			if (currentReloc)
			{
				auto tmpReloc = PIMAGE_BASE_RELOCATION((PUINT8)currentReloc + currentReloc->SizeOfBlock);
				if (tmpReloc < endReloc)
				{
					currentReloc = tmpReloc;
					return true;
				}
			}
			else
			{
				currentReloc = reloc;
				return true;
			}
			return false;
		}
		PIMAGE_BASE_RELOCATION Current()
		{
			return currentReloc;
		}
		
		void Reset() 
		{
			currentReloc = NULL; 
		}
		
	};


}