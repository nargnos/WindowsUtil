#pragma once
#include "..\Common\Common.h"
#include "AsmDisassembler_Trait.h"
#include "State\AsmStateFactory.h"
#include "Opcode\AsmOpcodeDataWapper.h"
#include "AsmStorage.h"
#include "AsmDisassembler.h"
#include "..\Common\DisassemblerBase.h"

namespace Disassembler
{
	class AsmDisassembler :
		public DisassemblerBase<AsmDisassembler>
	{
	public:
		AsmDisassembler(bool is32)
		{
			storage.SetX32(is32);
		}

		~AsmDisassembler()
		{
			
		}
	
		virtual unsigned int Parse(void * pos) override;
		virtual unique_ptr<IInstruction> GetResult() const override;

	};
}  // namespace Disassembler