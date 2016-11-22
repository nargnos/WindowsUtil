#pragma once
#include <memory>
#include "ISectionHeaders.h"
namespace PeDecoder
{
	class PeImage;
	class SectionHeadersFactory final
	{
	public:
		static _STD unique_ptr<ISectionHeaders> CreateSectionHeadersInstance(const PeImage& pe);
	private:
		SectionHeadersFactory() = delete;

		~SectionHeadersFactory() = delete;
	};
}  // namespace PeDecoder
