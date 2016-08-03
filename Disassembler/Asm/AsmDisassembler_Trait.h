#pragma once
#include "..\Common\Disassembler_Trait.h"
#include "..\Common\Interface\IStateUsed.h"
namespace Disassembler
{
	class AsmDisassembler;
	class AsmStateFactory;
	class AsmOpcodeDataWrapper;
	class AsmStorage;
	
	template<>
	struct Disassembler_Trait<AsmDisassembler>
	{
		
		typedef AsmStateFactory TStateFactory;
		typedef AsmOpcodeDataWrapper TOpcodeDataWapper;
		typedef AsmStorage TStorage;
		typedef IStateUsed<Disassembler_Trait<AsmDisassembler>> TStateUsed;
	};
}  // namespace Disassembler