#include "AsmInstruction.h"
#include "StateFactory.h"
OpcodeType AsmInstruction::GetTmpInstType()
{
	return tmpInstType;
}

void AsmInstruction::SetTmpData(OpcodeType type, const void * ptr)
{
	tmpInstType = type;
	tmpInstData = ptr;
}

void AsmInstruction::ClearTmpData()
{
	tmpInstType = OT_None;
	tmpInstData = NULL;
}

std::shared_ptr<AsmOpcodeWapper>& AsmInstruction::GetOpcodeDataWapper()
{
	return wapper;
}

bool AsmInstruction::IsX32()
{
	return isX32;
}

int AsmInstruction::GetCurrentPfxcdt()
{
	return 0;
}

OpcodeType AsmInstruction::ReadInst(OpcodeType table)
{
	auto curStat = GetFactory<StateFactory>()->GetCurrentState();
	assert(curStat == StateFactory::State_Byte);

	const OpcodeData* opcodeData = NULL;
	auto index = *CurrentBytePtr();
	switch (table)
	{
	case OT_None:
		opcodeData = &wapper->GetOpcodeData(index);
		break;
	case OT_Table_0F:
		opcodeData = &wapper->GetTable0FOpcodeData(index);
		break;
	case OT_Table_0F38:
		opcodeData = &wapper->GetTable0F38OpcodeData(index);
		break;
	case OT_Table_0F3A:
		opcodeData = &wapper->GetTable0F3AOpcodeData(index);
		break;
	default:
		assert(false);
		break;
	}
	// 根据已有条件选择指令
	for (auto i = 0; i < opcodeData->Count; i++)
	{
		if (SelectInst(wapper->GetHex_Inst(opcodeData->Hex_InstIndex + i)))
		{
			break;
		}
	}
	NextByte();
	return GetTmpInstType();
}

bool AsmInstruction::SelectInst(const Hex_Inst & hexInst)
{
	Superscript tmpInstSs = (Superscript)NULL;
	PrefixCondition tmpInstPfxcdt = (PrefixCondition)NULL;
	ClearTmpData();
	auto instType = (OpcodeType)hexInst.Type;
	assert(instType != (OpcodeType)NULL);
	switch (instType)
	{
	case OT_Inst:
	{
		auto tmpInst = &wapper->GetInst(hexInst.InstIndex);
		SetTmpData(instType, tmpInst);
		tmpInstSs = (Superscript)tmpInst->Ss;
		tmpInstPfxcdt = (PrefixCondition)tmpInst->Pfxcdt;
	}
	break;
	case OT_Inst_Change:
	{
		auto tmpInst = &wapper->GetInstChange(hexInst.InstIndex);
		SetTmpData(instType, tmpInst);
		tmpInstSs = (Superscript)tmpInst->Ss;
		tmpInstPfxcdt = (PrefixCondition)tmpInst->Pfxcdt;
	}
	break;
	case OT_Prefix:
	{
		auto tmpInst = &wapper->GetPfxInst(hexInst.InstIndex);
		SetTmpData(instType, tmpInst);
		tmpInstSs = (Superscript)tmpInst->Ss;
	}
	break;
	case OT_Grp:
	{
		auto tmpInst = &wapper->GetGrpInst(hexInst.InstIndex);
		SetTmpData(instType, tmpInst);
		tmpInstSs = (Superscript)tmpInst->Ss;
	}
	break;
	default:
		SetTmpData(instType, NULL);
		break;
	}
	auto result = VerifyCondition(tmpInstSs, tmpInstPfxcdt);
	if (!result)
	{
		// 验证失败清空临时数据
		ClearTmpData();
	}
	return result;
}

bool AsmInstruction::VerifyCondition(Superscript ss, PrefixCondition pfx)
{
	if (pfx != NULL && ((pfx & GetCurrentPfxcdt()) != pfx))
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

AsmInstruction::AsmInstruction(const shared_ptr<StateFactory>& factory, bool isX32)
	:Instruction(dynamic_pointer_cast<IStateFactory>(factory)), isX32(isX32)
{
	wapper = make_shared<AsmOpcodeWapper>();
	ClearTmpData();
}

void AsmInstruction::Init(const void * ptr)
{
	this->Instruction::Init(ptr);
	ClearTmpData();
}

AsmInstruction::~AsmInstruction()
{
}
