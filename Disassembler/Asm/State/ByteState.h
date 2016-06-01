#pragma once
#include "AsmState.h"
#include "AsmStateFactory.h"
#include "..\Opcode\OpcodeDef.h"
#include "..\AsmDisassembler.h"
#include "..\AsmStorage.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Byte> :public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param);
	private:
		// 以当前游标位置作为起始读取指令（表123指令）
		// 参数表示表类型，只有1(用None表示)、0F、0F38、0F3A表
		static OpcodeType ReadInst(AsmStateFactory::ParamType* param, OpcodeType table);

		// 判断是否选择该指令关系, 如果通过则存储 ,需要判断当前读取到的前缀组合（只有66、F2、F3）
		// 成功后返回true会把 OT_Inst\OT_Inst_Change\OT_Prefix\OT_Grp 的对应类型指针存入opcodeDataStorage
		// 返回失败返回false表示指令不存在，同时GetType()为NULL
		// 非switch里的类型会无条件返回true
		static bool SelectInst(AsmStateFactory::ParamType* param, const Hex_Inst & hexInst);

		// 以当前读取到的信息验证指令是否存在
		// ss和pfx都为指令数据
		static bool VerifyCondition(AsmStateFactory::ParamType* param, Superscript ss, PrefixCondition pfx);
		static int OpcodeTypeToStateID(OpcodeType opType);
		
	};

}  // namespace Disassembler