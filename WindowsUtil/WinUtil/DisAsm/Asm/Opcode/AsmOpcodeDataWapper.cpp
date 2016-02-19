#include "AsmOpcodeDataWapper.h"
#include "OpcodeData.h"
namespace Disassembler
{
	AsmOpcodeDataWapper::AsmOpcodeDataWapper()
	{
	}

	AsmOpcodeDataWapper::~AsmOpcodeDataWapper()
	{
	}

	std::unique_ptr<OpcodeData[]> AsmOpcodeDataWapper::UnzipOpcodeData(const ZipOpcodeData zipArray[], int count)
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
	bool AsmOpcodeDataWapper::IsSeg(unsigned char val) const
	{
		return val >= SEG_XX;
	}
	const unsigned char* AsmOpcodeDataWapper::GetOperandGroup(int opCount, int index) const
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


	const OpcodeData& AsmOpcodeDataWapper::GetOpcodeData(OpcodeType tableType, int hex)
	{
		assert(hex >= 0 && hex <= 0xff);
		switch (tableType)
		{
		case OT_Table_0F:
			return HexTable2[hex];
		case OT_Table_0F38:
			if (!table0F38)
			{
				table0F38 = UnzipOpcodeData(HexTable3Zip_38, sizeof(HexTable3Zip_38) / sizeof(ZipOpcodeData));
			}
			return table0F38[hex];
		case OT_Table_0F3A:
			if (!table0F3A)
			{
				table0F3A = UnzipOpcodeData(HexTable3Zip_3A, sizeof(HexTable3Zip_3A) / sizeof(ZipOpcodeData));
			}
			return table0F3A[hex];
		default:
			return HexTable1[hex];
		}
	}

	const Hex_Inst& AsmOpcodeDataWapper::GetHex_Inst(int index) const
	{
		assert(index >= 0 && index < sizeof(HexInsts) / sizeof(Hex_Inst));
		return HexInsts[index];
	}

	const GrpInstData& AsmOpcodeDataWapper::GetGrpInst(int index) const
	{
		assert(index >= 0 && index < sizeof(GrpInst) / sizeof(GrpInstData));
		return GrpInst[index];
	}

	const PrefixInstData& AsmOpcodeDataWapper::GetPfxInst(int index) const
	{
		assert(index >= 0 && index < sizeof(PfxInst) / sizeof(PrefixInstData));
		return PfxInst[index];
	}

	const InstChangeData& AsmOpcodeDataWapper::GetInstChange(int index) const
	{
		assert(index >= 0 && index < sizeof(InstChange) / sizeof(InstChangeData));
		return InstChange[index];
	}

	const RegOrOperandGroup& AsmOpcodeDataWapper::GetOperands(int index) const
	{
		assert(index >= 0 && index < sizeof(Operands) / sizeof(RegOrOperandGroup));
		return Operands[index];
	}

	const InstData& AsmOpcodeDataWapper::GetInst(int index) const
	{
		assert(index >= 0 && index < sizeof(Inst) / sizeof(InstData));
		return Inst[index];
	}

	const LPCSTR& AsmOpcodeDataWapper::GetInstructionNames(int index) const
	{
		assert(index >= 0 && index < sizeof(InstructionNames) / sizeof(LPCSTR));
		return InstructionNames[index];
	}


	const char * AsmOpcodeDataWapper::GetRegisterName(OperandType reg) const
	{
		auto tmpReg = reinterpret_cast<RegOrOperand*>(&reg);
		assert(reg <= REG_END);
		assert(tmpReg->IsReg);

		return Registers[tmpReg->Reg.Hex][tmpReg->Reg.LenType];
	}

	const char* AsmOpcodeDataWapper::GetSegName(OperandType seg) const
	{
		assert(IsSeg(seg));
		auto index = (unsigned char)seg - SEG_XX;
		return Registers[index][0] + 3;
	}

}  // namespace Disassembler
