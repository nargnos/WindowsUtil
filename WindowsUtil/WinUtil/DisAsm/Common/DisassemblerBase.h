#pragma once
#include "Common.h"

#include "Disassembler_Trait.h"
#include "Interface\IDisassembler.h"
#include "Interface\IStateUsed.h"
namespace Disassembler
{
	// 参数为子类
	template<typename TChild, typename TTrait = Disassembler_Trait<TChild>>
	class DisassemblerBase 
		:public IDisassembler,
		protected IStateUsed<TTrait>
	{
	public:
		typedef TTrait Trait;
		
		DisassemblerBase()
		{
			auto isChild = std::is_base_of<IDisassembler, TChild>::value;
			assert(isChild);
		}

		~DisassemblerBase()
		{
		}
	protected:
		typename TTrait::TOpcodeDataWapper opcodeDataWapper;
		typename TTrait::TStorage storage;

		virtual typename TTrait::TOpcodeDataWapper* GetOpcodeDataWapper() override
		{
			return &opcodeDataWapper;
		}
		virtual typename TTrait::TStorage* GetStorage() override
		{
			return &storage;
		}
	};
}  // namespace Disassembler
