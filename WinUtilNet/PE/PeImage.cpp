#include "PeImage.h"

namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		void PeImage::OnPeLoaded()
		{
			PeLoaded();
		}
		::PE::PeDecoder * PeImage::GetData()
		{
			return new ::PE::PeDecoder();
		}

		PeImage::PeImage()
		{
		}

		bool PeImage::LoadPEImage(IntPtr pe, bool isMapped)
		{
			auto result = UnmanagedObject()->LoadPEImage(pe.ToPointer(), isMapped);
			if (result)
			{
				OnPeLoaded();
			}
			return result;
		}

		
	}
}