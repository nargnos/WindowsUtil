#pragma once
#include "PeImageFwd.h"
namespace PeDecoder
{
	namespace Detail
	{
		class PeRef
		{
		public:
			PeRef(PeImage& pe);

			~PeRef() = default;
			PeImage& GetPe();
			const PeImage& GetPe() const;
		private:
			PeImage& pe_;
		};
	}  // namespace Detail

}  // namespace PeDecoder
