#pragma once
#include "PeStructDescription.h"
namespace PeImageClr
{
	using namespace System;
	ref class PeImage;
	template<typename T>
	public ref class PeStructWrapper :public PeStructDescription
	{
	protected:
		typedef PeStructWrapper<T> PeStructWrapperBase;
		typedef T PeStructWrapperType;
		PeImage^ pe;

	internal:
		virtual PeStructWrapperType& GetUnmanagedStruct() = 0;

	public:
		PeStructWrapper(PeImage^ pe)
		{
			this->pe = pe;
			base = pe->BaseAddress;
		}
		IntPtr GetPeBase()
		{
			return pe->BaseAddress;
		}
	};
}  // namespace PeImageClr
