#include "stdafx.h"
#include "NtHeaderFactory.h"
#include "NtHeader.h"
#include "NtHeader32.h"
#include "NtHeader64.h"
namespace PeDecoder
{
	_STD unique_ptr<INtHeader> NtHeaderFactory::CreateNtHeaderInstance(const IDosHeader & dosHeader)
	{
		using namespace std;
		assert(dosHeader.IsValid());
		auto header = NtHeader::GetNtHeaderPtr(dosHeader.RawPtr());
		auto type = NtHeader::GetHeaderType(header);
		unique_ptr<INtHeader> result;
		switch (type)
		{
		case PeDecoder::NtHeaderType::NtHeader32:
			result = make_unique<NtHeader32>(reinterpret_cast<PIMAGE_NT_HEADERS32>(header));
			break;
		case PeDecoder::NtHeaderType::NtHeader64:
			result = make_unique<NtHeader64>(reinterpret_cast<PIMAGE_NT_HEADERS64>(header));
			break;
		default:
			break;
		}
		return result;
	}

}

