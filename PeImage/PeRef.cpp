#include "stdafx.h"
#include "PeRef.h"
namespace PeDecoder
{
	namespace Detail
	{
		PeRef::PeRef(PeImage & pe) :
			pe_(pe)
		{
		}

		PeImage & PeRef::GetPe()
		{
			return pe_;
		}

		const PeImage & PeRef::GetPe() const
		{
			return pe_;
		}
	}  // namespace Detail


}  // namespace PeDecoder
