#include "stdafx.h"
#include "HeaderFactory.h"
#include "SectionHeaders.h"
#include "NtHeaderImpl.h"
#include "DosHeader.h"
namespace PeDecoder
{
	std::unique_ptr<ISectionHeaders> HeaderFactory::CreateSectionHeadersInstance(const PeImage & pe)
	{
		return _STD make_unique<SectionHeaders>(pe);
	}
	std::unique_ptr<INtHeader> HeaderFactory::CreateNtHeaderInstance(const IDosHeader & dosHeader)
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
	std::unique_ptr<IDosHeader> HeaderFactory::CreateDosHeaderInstance(const PIMAGE_DOS_HEADER rawptr)
	{
		return _STD make_unique<DosHeader>(rawptr);
	}
}  // namespace PeDecoder