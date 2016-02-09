#pragma once
#include <Windows.h>
#include "../../Common/Common.h"
#include "OpcodeDef.h"
// OpcodeData包装
class AsmOpcodeWapper
{
	_STD unique_ptr<OpcodeData[]> table0F38;
	_STD unique_ptr<OpcodeData[]> table0F3A;

public:
	AsmOpcodeWapper();

	~AsmOpcodeWapper();

	static _STD unique_ptr<OpcodeData[]> UnzipOpcodeData(const ZipOpcodeData zipArray[], int count);

	// 取操作数组合
	const unsigned char* GetOperandGroup(int opCount, int index);

	// OT_None:取1字节表
	// OT_Table_0F:取2字节表
	// OT_Table_0F38:取3字节38表
	// OT_Table_0F3A:取3字节3A表
	const OpcodeData& GetOpcodeData(OpcodeType tableType, int hex);
	// 取字节-指令对应关系表
	const Hex_Inst& GetHex_Inst(int index);
	// 取指令-组对应表
	const GrpInstData& GetGrpInst(int index);
	// 取前缀表
	const PrefixInstData& GetPfxInst(int index);
	// 取指令表（带后缀字符串）
	const InstChangeData& GetInstChange(int index);
	// 取指令表
	const InstData& GetInst(int index);
	// 取操作数
	const RegOrOperandGroup& GetOperands(int index);
	// 取指令名称
	const LPCSTR& GetInstructionNames(int index);
	// 取寄存器名称
	const char * GetRegisterName(unsigned char hex, RegisterLength type);
	// 取段寄存器名称
	const char * GetSegName(OperandType seg);

};
