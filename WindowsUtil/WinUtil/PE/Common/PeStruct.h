#pragma once
namespace PE
{
	template<typename _PeDecoder>
	class PeStruct
	{
	protected :
		_PeDecoder& peDecoder;
	public:
		
		PeStruct(_PeDecoder& pe):peDecoder(pe)
		{
		}
		_PeDecoder& GetPeDecoder()
		{
			return peDecoder;
		}
		virtual ~PeStruct()
		{
		}
	};

}