#include "EscapeState.h"
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Escape>::Next(AsmStateFactory::ParamType * param)
	{
		// TODO: 表没录入, 可能需要子状态
		return AsmStateFactory::State_PreEnd;
	}
}  // namespace Disassembler
