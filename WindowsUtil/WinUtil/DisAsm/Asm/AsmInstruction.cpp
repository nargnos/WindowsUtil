#include "AsmInstruction.h"
#include "StateFactory.h"

// 操作数(立即数)所占的字长，在读取operandGrp会将对应参数字长设置好

const AsmOpcodeDataWapper* AsmInstruction::GetOpcodeDataWapper() const
{
	return &opcodeDataWapper;
}

bool AsmInstruction::IsX32() const
{
	return isX32;
}

OpcodeType AsmInstruction::ReadInst(OpcodeType table)
{
	assert(GetFactory<StateFactory>()->GetCurrentState() == StateFactory::State_Byte);

	const OpcodeData* opcodeData = NULL;
	auto index = *CurrentBytePtr();
	opcodeData = &opcodeDataWapper.GetOpcodeData(table, index);
	// 根据已有条件选择指令
	for (auto i = 0; i < opcodeData->Count; i++)
	{
		if (SelectInst(opcodeDataWapper.GetHex_Inst(opcodeData->Hex_InstIndex + i)))
		{
			break;
		}
	}
	return opcodeDataStorage.GetType();
}


bool AsmInstruction::SelectInst(const Hex_Inst & hexInst)
{
	Superscript tmpInstSs = (Superscript)NULL;
	PrefixCondition tmpInstPfxcdt = (PrefixCondition)NULL;
	if (!opcodeDataStorage.IsEmpty())
	{
		opcodeDataStorage.Clear();
	}
	auto instType = (OpcodeType)hexInst.Type;
	assert(instType != (OpcodeType)NULL);
	switch (instType)
	{
	case OT_Inst:
	case OT_Inst_Change:
	{
		const InstData* tmpInst = NULL;
		if (instType == OT_Inst_Change)
		{
			// 两个结构体类型只有最后一个成员变量的区别，此时不使用所以当作同一类型
			tmpInst = reinterpret_cast<const InstData*>(&opcodeDataWapper.GetInstChange(hexInst.InstIndex));
		}
		else
		{
			tmpInst = &opcodeDataWapper.GetInst(hexInst.InstIndex);
		}
		assert(tmpInst != NULL);
		opcodeDataStorage.SetData(instType, tmpInst);
		tmpInstSs = (Superscript)tmpInst->Ss;
		tmpInstPfxcdt = (PrefixCondition)tmpInst->Pfxcdt;
	}
	break;
	case OT_Prefix:
	{
		auto tmpInst = &opcodeDataWapper.GetPfxInst(hexInst.InstIndex);
		opcodeDataStorage.SetData(instType, tmpInst);
		tmpInstSs = (Superscript)tmpInst->Ss;
	}
	break;
	case OT_Grp:
	{
		auto tmpInst = &opcodeDataWapper.GetGrpInst(hexInst.InstIndex);
		opcodeDataStorage.SetData(instType, tmpInst);
		tmpInstSs = (Superscript)tmpInst->Ss;
	}
	break;
	default:
		opcodeDataStorage.SetData(instType, NULL);
		return true;
	}
	auto result = VerifyCondition(tmpInstSs, tmpInstPfxcdt);
	if (!result)
	{
		// 验证失败清空临时数据
		opcodeDataStorage.Clear();
	}
	return result;
}

// ss和pfx都为指令数据
bool AsmInstruction::VerifyCondition(Superscript ss, PrefixCondition pfx) const
{
	if (pfx != NULL && ((pfx & prefixStorage.GetCurrentPfxcdt()) != pfx))
	{
		return false;
	}
	switch (ss)
	{
	case S_i64:
		return isX32;
	case S_o64:
		return !isX32;
	default:
		return true;
	}
}

bool AsmInstruction::IsNeedOutput() const
{
	return needOutput;
}

AsmInstruction::AsmInstruction(const shared_ptr<StateFactory>& factory, bool isX32, bool needOutput)
	:Instruction(dynamic_pointer_cast<IStateFactory>(factory)),
	isX32(isX32),
	needOutput(needOutput)
{
}


AsmInstruction::~AsmInstruction()
{
}
