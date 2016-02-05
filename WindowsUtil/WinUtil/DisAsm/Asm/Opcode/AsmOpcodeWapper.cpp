#include "AsmOpcodeWapper.h"
#include "OpcodeData.h"

AsmOpcodeWapper::AsmOpcodeWapper()
{
}

AsmOpcodeWapper::~AsmOpcodeWapper()
{
}

std::unique_ptr<OpcodeData[]> AsmOpcodeWapper::UnzipOpcodeData(const ZipOpcodeData zipArray[], int count)
{
	auto result = _STD make_unique<OpcodeData[]>(0x100);

	for (auto i = 0; i < count; i++)
	{
		auto& tmp = zipArray[i];
		auto& tmpResultNode = result[tmp.Index];
		tmpResultNode.Count = tmp.Count;
		tmpResultNode.Hex_InstIndex = tmp.Hex_InstIndex;
	}
	return result;
}

const unsigned char * AsmOpcodeWapper::GetOperandGroup(int opCount, int index)
{
	assert(opCount > 0 && opCount <= 4);
	switch (opCount)
	{
	case 1:
		assert(index >= 0 && index < sizeof(OperandGroup1) / sizeof(char));
		return &OperandGroup1[index];
	case 2:
		assert(index >= 0 && index < sizeof(OperandGroup2) / sizeof(OperandGroup2[0]));
		return OperandGroup2[index];
	case 3:
		assert(index >= 0 && index < sizeof(OperandGroup3) / sizeof(OperandGroup3[0]));
		return OperandGroup3[index];
	case 4:
		assert(index >= 0 && index < sizeof(OperandGroup4) / sizeof(OperandGroup4[0]));
		return OperandGroup4[index];
	default:
		assert(false);
		break;
	}
	return NULL;
}

const OpcodeData & AsmOpcodeWapper::GetOpcodeData(int hex)
{
	assert(hex >= 0 && hex <= 0xff);
	return HexTable1[hex];
}

const OpcodeData & AsmOpcodeWapper::GetTable0FOpcodeData(int hex)
{
	assert(hex >= 0 && hex <= 0xff);
	return HexTable2[hex];
}

const OpcodeData & AsmOpcodeWapper::GetTable0F38OpcodeData(int hex)
{
	assert(hex >= 0 && hex <= 0xff);
	if (!table0F38)
	{
		table0F38 = UnzipOpcodeData(HexTable3Zip_38, sizeof(HexTable3Zip_38) / sizeof(ZipOpcodeData));
	}
	return table0F38[hex];
}

const OpcodeData & AsmOpcodeWapper::GetTable0F3AOpcodeData(int hex)
{
	assert(hex >= 0 && hex <= 0xff);
	if (!table0F3A)
	{
		table0F3A = UnzipOpcodeData(HexTable3Zip_3A, sizeof(HexTable3Zip_3A) / sizeof(ZipOpcodeData));
	}
	return table0F3A[hex];
}

const Hex_Inst & AsmOpcodeWapper::GetHex_Inst(int index)
{
	assert(index >= 0 && index < sizeof(HexInsts) / sizeof(Hex_Inst));
	return HexInsts[index];
}

const GrpInstData & AsmOpcodeWapper::GetGrpInst(int index)
{
	assert(index >= 0 && index < sizeof(GrpInst) / sizeof(GrpInstData));
	return GrpInst[index];
}

const PrefixInstData & AsmOpcodeWapper::GetPfxInst(int index)
{
	assert(index >= 0 && index < sizeof(PfxInst) / sizeof(PrefixInstData));
	return PfxInst[index];
}

const InstChangeData & AsmOpcodeWapper::GetInstChange(int index)
{
	assert(index >= 0 && index < sizeof(InstChange) / sizeof(InstChangeData));
	return InstChange[index];
}

const RegOrOperandGroup & AsmOpcodeWapper::GetOperands(int index)
{
	assert(index >= 0 && index < sizeof(Operands) / sizeof(RegOrOperandGroup));
	return Operands[index];
}

const InstData & AsmOpcodeWapper::GetInst(int index)
{
	assert(index >= 0 && index < sizeof(Inst) / sizeof(InstData));
	return Inst[index];
}

const LPCSTR & AsmOpcodeWapper::GetInstructionNames(int index)
{
	assert(index >= 0 && index < sizeof(InstructionNames) / sizeof(LPCSTR));
	return InstructionNames[index];
}

const char * AsmOpcodeWapper::GetRegisterName(unsigned char hex, RegisterLength type)
{
	assert(hex < 16 && (unsigned char)type < 6);
	assert(hex < 8 ? true : (type != Len_64_MM));
	return Registers[hex][type];
}

const char * AsmOpcodeWapper::GetSegName(OperandType seg)
{
	assert(seg >= SEG_CS && seg <= SEG_SS);
	auto op = reinterpret_cast<RegOrOperand*>(&seg);
	return Registers[op->Reg.Hex][op->Reg.LenType];
}
