#pragma once
#include <Windows.h>
#include "../../Common/Common.h"
#include "OpcodeDef.h"
// OpcodeData包装
class AsmOpcodeDataWapper
{
	unique_ptr<OpcodeData[]> table0F38;
	unique_ptr<OpcodeData[]> table0F3A;
	AsmOpcodeDataWapper(const AsmOpcodeDataWapper& obj) = delete;
public:
	AsmOpcodeDataWapper();

	~AsmOpcodeDataWapper();
	
	static _STD unique_ptr<OpcodeData[]> UnzipOpcodeData(const ZipOpcodeData zipArray[], int count);

	// 取操作数组合
	const unsigned char* GetOperandGroup(int opCount, int index) const;
	// 返回值是否在OperandType枚举中定义为SEG
	bool IsSeg(unsigned char val) const
	{
		return val >= SEG_CS && val <= SEG_SS;
	}

	// 其它:取1字节表
	// OT_Table_0F:取2字节表
	// OT_Table_0F38:取3字节38表
	// OT_Table_0F3A:取3字节3A表
	const OpcodeData& GetOpcodeData(OpcodeType tableType, int hex);
	// 取字节-指令对应关系表,输入OpcodeData记录的下标
	const Hex_Inst& GetHex_Inst(int index) const;
	// 取指令-组对应表
	const GrpInstData& GetGrpInst(int index) const;
	// 取前缀表
	const PrefixInstData& GetPfxInst(int index) const;
	// 取指令表（带后缀字符串）
	const InstChangeData& GetInstChange(int index) const;
	// 取指令表
	const InstData& GetInst(int index) const;
	// 取操作数
	const RegOrOperandGroup& GetOperands(int index) const;
	// 取指令名称
	const LPCSTR& GetInstructionNames(int index) const;
	// 取寄存器名称
	const char * GetRegisterName(unsigned char hex, RegisterLength type) const;
	const char * GetRegisterName(OperandType reg) const;

	// 取段寄存器名称
	const char * GetSegName(OperandType seg) const;


};
