#include "stdafx.h"
#include "SectionHeadersFactory.h"
#include "SectionHeaders.h"
namespace PeDecoder
{
	std::unique_ptr<ISectionHeaders> PeDecoder::SectionHeadersFactory::CreateSectionHeadersInstance(const PeImage & pe)
	{
		return _STD make_unique<SectionHeaders>(pe);
	}

}  // namespace PeDecoder