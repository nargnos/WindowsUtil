#pragma once
#include "..\Common\ToStringBase.h"
#include "..\Common\Common.h"
namespace Disassembler
{
	class AsmInstruction;
	template<>
	struct ToStringBase<AsmInstruction>
	{
		typedef AsmInstruction TInstruction;
		static void ToString(const TInstruction* inst, _STD ostringstream& stream)
		{

		}
	};
}  // namespace Disassembler