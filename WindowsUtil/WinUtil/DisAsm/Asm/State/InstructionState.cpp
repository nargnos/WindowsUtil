//#include "InstructionState.h"
//#include "StateFactory.h"
//// 读需要的操作数信息，输出指令名
//const State*  InstructionState::Next(const shared_ptr<Instruction>& inst) const
//{
//	auto asmInst = inst->Cast<AsmInstruction>();
//	auto type = asmInst->opcodeDataStorage.GetType();
//	assert(type == OT_Inst || type == OT_Inst_Change);
//	
//	// 这里跟InstChangeData共用结构，这两个结构成员变量类型大小顺序必须相同
//	// InstChangeData的最后一个成员变量是用来添加名字后缀用的，这里不需要
//	auto instData = asmInst->opcodeDataStorage.GetData<InstData>();
//	auto wapper = asmInst->GetOpcodeDataWapper();
//	if (asmInst->IsNeedOutput())
//	{
//		// 输出名字
//		asmInst->nameStorage.SetInstName(wapper->GetInstructionNames(instData->NameID));
//		if (type == OT_Inst_Change)
//		{
//			// 解析后缀
//			auto instChange = reinterpret_cast<const InstChangeData*>(instData);
//			// TODO: 需要prefix解析，判断操作数长度从选项中选出“后缀”
//		}
//	}
//
//	if (instData->ParamCount == 0)
//	{
//		asmInst->operandGrpStorage.SetOperandGrp(0, NULL);
//		asmInst->SetSuccess();
//		return asmInst->GetFactory()->GetState(StateFactory::State_End);
//	}
//	auto operandGrp = wapper->GetOperandGroup(instData->ParamCount, instData->ParamID);
//	assert(operandGrp != NULL);
//	asmInst->operandGrpStorage.SetOperandGrp(instData->ParamCount, operandGrp);
//	return asmInst->GetFactory()->GetState(StateFactory::State_Operand);
//
//	// TODO: 不用先确定rm存在，整合到读操作数类型里，边读操作数边读rm（或者rm先读出来，用到再查）。
//	// 现在对于3字节指令有疑问，66 0F3A 0F C1 08H为什么是palignr Vdq, Wdq, Ib
//	// 而不是palignr Pq, Qq, Ib 或vpalignr Vx,Hx,Wx,Ib
//	// 这个设定表里没有记录啊！！Vs的解析结果使用了3个操作数，是不是我漏看了什么？
//	// 按强制前缀查到的应该是第3个（4操作数），至少不要前缀也是第二个结果，为什么例子写的是表里没记录的第一个结果？
//	// TODO: 弄明白前无法往下编，暂时放下先，可能跟SSE版本有关，H解释为旧版不存在，得到结果就会跟例子一样。
//	// 可能4操作数需要Vex前缀, 测试了一下，64位加了vex前缀vs不解析，可能用法不对。64位下的指令还是跟32位的一样
//
//}
//
