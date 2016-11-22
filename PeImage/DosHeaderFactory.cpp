#include "stdafx.h"
#include "DosHeaderFactory.h"
#include "DosHeader.h"
namespace PeDecoder
{

	_STD unique_ptr<IDosHeader> DosHeaderFactory::CreateDosHeaderInstance(const PIMAGE_DOS_HEADER rawptr)
	{
		return _STD make_unique<DosHeader>(rawptr);
	}

}