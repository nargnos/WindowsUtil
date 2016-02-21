#include "InstructionState.h"
#include "..\AsmStorage.h"
#include "..\Opcode\AsmOpcodeDataWapper.h"
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Instruction>::Next(AsmStateFactory::ParamType * param)
	{
		auto storage = param->GetStorage();
		auto opcodeDataStorage = storage->GetOpcodeDataStorage();
		// 查看上个状态保存的指令类型
		auto type = opcodeDataStorage->GetType();
		assert(type == OT_Inst || type == OT_Inst_Change);

		// 这里跟InstChangeData共用结构，这两个结构成员变量类型大小顺序必须相同
		// InstChangeData的最后一个成员变量是用来添加名字后缀用的，这里不需要
		auto instData = opcodeDataStorage->GetData<InstData>();
		auto wapper = param->GetOpcodeDataWapper();

		// 输出名字
		auto nameStorage = storage->GetNameStorage();
		nameStorage->SetInstName(wapper->GetInstructionNames(instData->NameID));
		if (type == OT_Inst_Change)
		{
			// 解析后缀
			auto instChange = reinterpret_cast<const InstChangeData*>(instData);
			// TODO: 需要prefix解析，判断操作数长度从选项中选出“后缀”
		}
		// 如果无操作数直接返回
		auto operandGrpStorage = storage->GetOperandGroupStorage();
		if (instData->ParamCount == 0)
		{
			operandGrpStorage->SetOperandGrp(0, NULL);
			storage->SetSuccess();
			return AsmStateFactory::State_PreEnd;
		}
		// 查找操作数组合
		auto operandGrp = wapper->GetOperandGroup(instData->ParamCount, instData->ParamID);
		assert(operandGrp != NULL);
		// 保存组合
		operandGrpStorage->SetOperandGrp(instData->ParamCount, operandGrp);

		// 设置大小属性
		auto pfxStorage = storage->GetPrefixStorage();
		bool is32 = storage->Is32();
		bool hasRexW = pfxStorage->HasRex() ? pfxStorage->GetRex()->W : false;
		bool hasOPfx = pfxStorage->IsOverrideOperandSize();
		bool hasAPfx = pfxStorage->IsOverrideAddressSize();
		auto sizeAttribute = wapper->FindSizeAttribute(is32, hasRexW, hasOPfx, hasAPfx);
		// 操作数大小
		operandGrpStorage->SetOperandSizeAttribute(sizeAttribute[EffectiveOperand]);
		// 地址大小
		operandGrpStorage->SetOperandSizeAttribute(sizeAttribute[EffectiveAddress]);

		return AsmStateFactory::State_Operand;

		// TODO: 
		// 现在对于3字节指令有疑问，66 0F3A 0F C1 08H为什么是palignr Vdq, Wdq, Ib
		// 而不是palignr Pq, Qq, Ib 或vpalignr Vx,Hx,Wx,Ib
		// 这个设定表里没有记录啊！！Vs的解析结果使用了3个操作数，是不是我漏看了什么？
		// 按强制前缀查到的应该是第3个（4操作数），至少不要前缀也是第二个结果，为什么例子写的是表里没记录的第一个结果？
		// TODO: 弄明白前无法往下编，暂时放下先，可能跟SSE版本有关，H解释为旧版不存在，得到结果就会跟例子一样。
		// 可能4操作数需要Vex前缀, 测试了一下，64位加了vex前缀vs不解析，可能用法不对。64位下的指令还是跟32位的一样

	}
}  // namespace Disassembler
