#include "PreEndState.h"
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_PreEnd>::Next(AsmStateFactory::ParamType * param)
	{
		return AsmStateFactory::State_End;
	}
}  // namespace Disassembler
