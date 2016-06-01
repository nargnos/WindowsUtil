#include "AsmDisassembler.h"
#include "State\AsmStateFactory.h"
#include "..\Common\DisassemblerBase.h"
namespace Disassembler
{


	unique_ptr<IInstruction> AsmDisassembler::GetResult() const
	{
		return unique_ptr<IInstruction>();
	}

}  // namespace Disassembler

