#pragma once
#include <Windows.h>
#include "../../Common/Common.h"
#include "OpcodeDef.h"

namespace Disassembler
{
	// OpcodeData包装
	class AsmOpcodeDataWrapper
	{
	public:
		AsmOpcodeDataWrapper();

		~AsmOpcodeDataWrapper();
		/// <summary>
		/// 解压OpcodeData表
		/// </summary>
		/// <param name="zipArray">压缩后的数组</param>
		/// <param name="count">数组长度</param>
		/// <returns>解压后的表，与Byte1、Byte2同结构</returns>
		static _STD unique_ptr<OpcodeData[]> UnzipOpcodeData(const ZipOpcodeData zipArray[], int count);

		/// <summary>
		/// 取操作数组合
		/// </summary>
		/// <param name="opCount">操作数个数</param>
		/// <param name="index">操作数ID</param>
		/// <returns>操作数组合，是RegOrOperandGroup表的下标组合，长度为opCount</returns>
		const unsigned char* GetOperandGroup(int opCount, int index) const;

		/// <summary>
		/// 判断参数是否在OperandType枚举中定义为SEG
		/// </summary>
		bool IsSeg(unsigned char val) const;


		/// <summary>
		/// 取指令表
		/// </summary>
		/// <param name="tableType">
		/// <para><paramref name="tableType"/>的取值和处理方式如下：</para>
		/// <para>OT_Table_0F:取2字节表</para>
		/// <para>OT_Table_0F38:取3字节38表</para>
		/// <para>OT_Table_0F3A:取3字节3A表</para>
		/// <para>其它:取1字节表</para>
		/// </param>
		/// <param name="hex">表ID，指令机器码</param>
		/// <returns>指令表元素，可能会指向多个指令</returns>
		const OpcodeData& GetOpcodeData(OpcodeType tableType, int hex);

		/// <summary>
		/// 取字节-指令对应关系表
		/// </summary>
		/// <param name="index">OpcodeData记录的下标</param>
		/// <returns>字节-指令对应关系</returns>
		const Hex_Inst& GetHex_Inst(int index) const;

		/// <summary>
		/// 取指令-组对应关系表
		/// </summary>
		/// <param name="index">Hex_Inst记录的下标</param>
		/// <returns>指令-组对应关系</returns>
		const GrpInstData& GetGrpInst(int index) const;

		/// <summary>
		/// 取前缀表
		/// </summary>
		/// <param name="index">Hex_Inst记录的下标</param>

		const PrefixInstData& GetPfxInst(int index) const;

		/// <summary>
		/// 取指令表（带后缀字符串）
		/// </summary>
		/// <param name="index">Hex_Inst记录的下标</param>
		const InstChangeData& GetInstChange(int index) const;

		/// <summary>
		/// 取指令表
		/// </summary>
		/// <param name="index">Hex_Inst记录的下标</param>
		const InstData& GetInst(int index) const;

		/// <summary>
		/// 取操作数
		/// </summary>
		/// <param name="index">通过GetOperandGroup取得</param>
		const RegOrOperandGroup& GetOperands(int index) const;

		/// <summary>
		/// 取指令名称
		/// </summary>
		/// <param name="index">指令结构中记录的名称ID</param>
		const LPCSTR& GetInstructionNames(int index) const;

		/// <summary>
		/// 取寄存器名称
		/// </summary>
		const char* GetRegisterName(OperandType reg) const;

		/// <summary>
		/// 取段寄存器名称
		/// </summary>
		const char* GetSegName(OperandType seg) const;

		// [REX.W Prefix] 32位下不用
		// [Operand Prefix Is Present]
		// [Address Prefix Is Present]
		// [Effective Operand Size/Effective Address Size]
		// 因为操作数或地址大小属性有时候是一起用的，所以返回指针，用EffectiveSizeIndex偏移取各自的值
		const SizeAttribute* FindSizeAttribute(bool is32, bool hasRexW, bool hasOPfx, bool hasAPfx) const;
	private:
		unique_ptr<OpcodeData[]> table0F38;
		unique_ptr<OpcodeData[]> table0F3A;
		AsmOpcodeDataWrapper(const AsmOpcodeDataWrapper& obj) = delete;
	};

}  // namespace Disassembler

