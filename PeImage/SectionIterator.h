#pragma once
#include <iterator>
#include <cassert>
#include "Section.h"
#include "RandomAccessIteratorBase.h"
namespace PeDecoder
{
	class SectionHeaders;
	namespace Detail
	{
		using SectionIterator = RandomAccessIteratorBase<Section, SectionHeaders>;
	}  // namespace Detail
}  // namespace PeDecoder
