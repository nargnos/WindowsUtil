#pragma once
namespace PE
{
	class PeDecoder;
	class PeStruct
	{
	protected :
		PeDecoder& peDecoder;
	public:
		typedef PeStruct PeStructBase;
		PeStruct(PeDecoder& pe);
		PeDecoder& GetPeDecoder();
		virtual ~PeStruct();
	};

}