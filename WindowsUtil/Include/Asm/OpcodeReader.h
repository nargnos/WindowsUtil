#pragma once
#include <Windows.h>
#include <WinBase.h>
#include "PrefixQueue.h"
#include "OpcodeTables.h"
#include <string>
// TODO: 暂时放一放
namespace Asm
{
	
	// 总状态，读取到的hex类型数值取optype的，方便转换
	enum OpcodeReaderStat
	{
		OpNone = OT_None, // 读到未定义
		OpCommand = OT_Command, // 读到指令
		OpPrefix = OT_Prefix, // 读到前缀
		OpGroup = OT_Group, // 读到组
		OpTable = OT_Table, // 读到切换表
		OpArray = OT_Array, // 读到多指令组
		OpEsc = OT_ESC, // 读到协处理器指令
		ReadHex, // 读hex
		ReadModRM,
		ReadSIB,
		ReadOffset,
		ReadImm,
		AnalyEnd // 该条指令读毕（输出解析的字符串
	};

	using std::string;
	class OpcodeReader
	{
		
	public:
		OpcodeReader( bool is32=true);
		~OpcodeReader();
		// 返回读取的指令长度
		int ReadCode(PUINT8 hex, string* output = NULL);
		// TODO: 读取时清空前缀队列，前缀冲突返回识别的内容，因为还没读到下一个指令所以不会重复读取
	private:
		PUINT8 code; // 读头初始位置
		PUINT8 current; // 读头

		OpcodeReaderStat currentStat; 
		Tables table; // 当前读取的表
		Opcode tmpCode; // 多状态共用的当前需要处理的指令
		string* tmpStr; // 多状态共用的输出字符串
		bool is32; // 32 or 64


		Asm::PrefixQueue prefix;
	
		ModRM mod;
		ModRM sib;

		void AppendOutput(PSTR str, BYTE sizeOption = 0);
		
		//typedef OpcodeReaderStat(*AnalyOperand)(OpcodeCommand& cmd, OpcodeReader & tmpData);

		friend OpcodeReaderStat _AnalyOperand0(const ZeroOperand& cmd, OpcodeReader & tmpData);
		friend OpcodeReaderStat _AnalyOperand1(const OneOperand& cmd, OpcodeReader & tmpData);
		friend OpcodeReaderStat _AnalyOperand2(const TwoOperands& cmd, OpcodeReader & tmpData);
		friend OpcodeReaderStat _AnalyOperand3(const ThreeOperands& cmd, OpcodeReader & tmpData);
		friend OpcodeReaderStat _AnalyOperand4(const FourOperands& cmd, OpcodeReader & tmpData);
		//static AnalyOperand AnalyOperandFunction[];

		typedef OpcodeReaderStat(*AnalyticFunction)(OpcodeReader& tmpData);

		// 状态用
		friend OpcodeReaderStat __OutputNone(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalyCmd(OpcodeReader& tmpData);
		friend OpcodeReaderStat __QueuePrefix(OpcodeReader& tmpData);
		friend OpcodeReaderStat __SwitchGroup(OpcodeReader& tmpData);
		friend OpcodeReaderStat __SwitchTable(OpcodeReader& tmpData);
		friend OpcodeReaderStat __ArraySelection(OpcodeReader& tmpData);
		friend OpcodeReaderStat __SwitchESC(OpcodeReader& tmpData);

		friend OpcodeReaderStat __ReadNextHex(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalyModRM(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalySIB(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalyOffset(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalyImm(OpcodeReader& tmpData);
		
		static AnalyticFunction OpTypeAnalyticFunction[];

		friend void  _AnalyOperand(const RegOrOperandGroup& operand, OpcodeReader& tmpData);
		friend bool IsOpcodeDefine(Superscripts s, OpcodeReader& tmpData);
		


		/* L_a = 1  2word或2dword内存操作数，根据操作数属性决定*/
		/* L_b byte不管属性*/
		/* L_c byte|word 属性决定*/
		/* L_d dword不管*/
		/* L_dq dqword（8字）*/
		/* L_p 32 48 80位指针，属性决定*/
		/* L_pd 128 double*/
		/* L_pi 4word mmx*/
		/* L_ps 128 float*/
		/* L_q  qword不管*/
		/* L_qq */
		/* L_s 6|10byte伪描述符*/
		/* L_sd */
		/* L_ss 128 float标量部分*/
		/* L_si dword*/
		/* L_v word dword qword 操作数尺寸决定*/
		/* L_w word不管*/
		/* L_x */
		/* L_y */
		/* L_z 16位时word 32|64为dword*/
		/* H_A  !ModRM,!SIB,addr*/ /*addr imm offset 都是数字*/
		/* H_B  从VEX前缀取寄存器*/
		/* H_C  ModRM reg=控制寄存器cr* */
		/* H_D  ModRM reg=调试寄存器dr* */
		/* H_E  +ModRM  reg|addr*/
		/* H_F  flag regs */
		/* H_G  ModRM 选择reg那方*/
		/* H_H  */
		/* H_I  imm*/
		/* H_J  offset*/
		/* H_L  */
		/* H_M  ModRM mem*/
		/* H_N  ModRM reg=4字mmx*/
		/* H_O  !ModRM，偏移字或双字*/
		/* H_P  ModR/M reg=4字MMX*/
		/* H_Q  +ModRM  mmx或内存地址*/
		/* H_R  ModRM rm=128xmm*/
		/* H_S  ModRM reg域为段寄存器*/
		/* H_U  ModRM rm=xmm*/
		/* H_V  ModRM reg=xmm*/
		/* H_W	+ModRM 128mmx addr*/
		/* H_X  DS:rSI*/
		/* H_Y  ES:rDI*/
		/* HL_Ux  */
		/* HL_Mb */
		/* HL_Md */
		/* HL_Mw */
		/* HL_Mq */
		/* HL_Rd */
		/* HL_Ry */
		/* HL_Udq */
		/* Seg_cs  */
		/* Seg_ds */
		/* Seg_es */
		/* Seg_fs */
		/* Seg_gs */
		/* Seg_ss */
		/* Rex  */
		/* Rex_B */
		/* Rex_X */
		/* Rex_XB */
		/* Rex_R */
		/* Rex_RB */
		/* Rex_RX */
		/* Rex_RXB */
		/* Rex_W */
		/* Rex_WB */
		/* Rex_WX */
		/* Rex_WXB */
		/* Rex_WR */
		/* Rex_WRB */
		/* Rex_WRX */
		/* Rex_WRXB */
		/* Grp_1 = 74	 */

	};
	
	
}