#pragma once
// 在这里处理指令
// 处理输出名称，根据指令信息决定跳转到读取操作数还是读取RM
// 会跳转到结束或RM状态

#include "AsmState.h"
#include "AsmStateFactory.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Instruction> :public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param);
	};
	 
}  // namespace Disassembler

