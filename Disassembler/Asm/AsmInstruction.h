#pragma once
#include "..\Common\Common.h"
#include "..\Common\Instruction.h"
#include "AsmToString.h"
namespace Disassembler
{


	class AsmInstruction :
		public Instruction<AsmInstruction>
	{
	public:

		AsmInstruction()
		{
		}

		~AsmInstruction()
		{
		}

	};
}  // namespace Disassembler
