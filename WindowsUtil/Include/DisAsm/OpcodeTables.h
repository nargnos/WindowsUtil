#pragma once
// 存储opcode表，可根据指令的hex查表得到指令描述。
// 描述有指令、前缀、组、多字节表跳转、多指令选择表（同一hex有几个指令）几个类型
#include <Windows.h>
#include <WinBase.h>
#include "InstructionNames.h"
#include "Registers.h"
#include "OperandStruct.h"
#include "Operands.h"

#include <assert.h>
namespace Asm
{

	BYTE PrefixByteToGroup(BYTE prefix);

	const static USHORT OpcodeArray_2[][2] =
	{
		{ HEX_CMD(2,25),		HEX_CMD(2,26) },
		{ HEX_CMD(2,31),		HEX_CMD(0,4)},//xchg eax,eax = nop
		{ HEX_CMD(0,37),		HEX_CMD(0,38) },
		{ HEX_CMD(2,125),		HEX_CMD(2,126) },
		// 4
		{ HEX_CMD(3,9),			HEX_CMD(3,10) },
		{ HEX_CMD(3,11),		HEX_CMD(3,12) },
		{ HEX_CMD(2,128),		HEX_CMD(2,129) },
		// 7
		{HEX_CMD(2,134),		HEX_CMD(2,135)},

		{ HEX_CMD(2,138),		HEX_CMD(3,18) },
		// 9
		{ HEX_CMD(2,139),		HEX_CMD(3,19) },
		// 10
		{ HEX_CMD(3,20),		HEX_CMD(3,21) },
		{ HEX_CMD(3,22),		HEX_CMD(3,23) },
		// 12
		{ HEX_CMD(3,24),		HEX_CMD(3,25) },
		// 13
		{ HEX_CMD(3,26),		HEX_CMD(3,27) },
		// 14
		{ HEX_CMD(2,140),		HEX_CMD(3,28) },
		// 15
		{ HEX_CMD(2,141),		HEX_CMD(3,29) },
		// 16
		{ HEX_CMD(2,142),		HEX_CMD(3,30) },
		// 17
		{ HEX_CMD(2,143),		HEX_CMD(3,31) },
		{ HEX_CMD(2,144),		HEX_CMD(3,32) },
		{ HEX_CMD(2,145),		HEX_CMD(3,33) },
		{ HEX_CMD(2,146),		HEX_CMD(3,34) },
		{ HEX_CMD(2,147),		HEX_CMD(3,35) },
		// 22
		{ HEX_CMD(2,148),		HEX_CMD(3,40) },
		{ HEX_CMD(2,149),		HEX_CMD(3,41) },
		{ HEX_CMD(2,150),		HEX_CMD(3,42) },
		// 25
		{ HEX_CMD(2,151),		HEX_CMD(2,152) },
		{ HEX_CMD(2,153),		HEX_CMD(2,154) },
		// 27
		{ HEX_CMD(2,157),		HEX_CMD(2,158) },
		// 28
		{ HEX_CMD(2,167),		HEX_CMD(2,168) },
		{ HEX_CMD(2,169),		HEX_CMD(2,170) },
		// 30
		{ HEX_CMD(2,176),		HEX_CMD(3,71) },
		{ HEX_CMD(2,177),		HEX_CMD(3,72) },
		{ HEX_CMD(2,178),		HEX_CMD(3,73) },
		{ HEX_CMD(2,179),		HEX_CMD(3,74) },
		// 34
		{ HEX_CMD(2,180),		HEX_CMD(2,181) },
		// 35
		{ HEX_CMD(3,77),		HEX_CMD(3,78) },
		{ HEX_CMD(3,79),		HEX_CMD(3,80) },
		// 37
		{ HEX_CMD(3,83),		HEX_CMD(4,4) },
		// 38
		{ HEX_CMD(3,84),		HEX_CMD(3,85) },
		// 39
		{ HEX_CMD(4,5),		HEX_CMD(4,6) },
		// 40
		{ HEX_CMD(3,86),		HEX_CMD(3,87) },
		// 41
		{ HEX_CMD(2,205),		HEX_CMD(3,88) },
		// 42
		{ HEX_CMD(2,206),		HEX_CMD(3,89) },
		{ HEX_CMD(2,207),		HEX_CMD(3,90) },
		{ HEX_CMD(2,208),		HEX_CMD(3,91) },
		{ HEX_CMD(2,209),		HEX_CMD(3,92) },
		// 46
		{ HEX_CMD(2,213),		HEX_CMD(2,214) },
		// 47
		{ HEX_CMD(2,215),		HEX_CMD(3,93) },
		{ HEX_CMD(2,216),		HEX_CMD(3,94) },
		{ HEX_CMD(2,217),		HEX_CMD(3,95) },
		{ HEX_CMD(2,218),		HEX_CMD(3,96) },
		{ HEX_CMD(2,219),		HEX_CMD(3,97) },
		{ HEX_CMD(2,220),		HEX_CMD(3,98) },
		// 53
		{ HEX_CMD(2,224),		HEX_CMD(2,225) },
		// 54
		{ HEX_CMD(2,227),		HEX_CMD(3,99) },
		{ HEX_CMD(2,228),		HEX_CMD(3,100) },
		{ HEX_CMD(2,229),		HEX_CMD(3,101) },
		{ HEX_CMD(2,230),		HEX_CMD(3,102) },
		{ HEX_CMD(2,231),		HEX_CMD(3,103) },
		{ HEX_CMD(2,232),		HEX_CMD(3,104) },
		{ HEX_CMD(2,233),		HEX_CMD(2,234) },
		// 61
		{ HEX_CMD(2,239),		HEX_CMD(2,240) },
		{ HEX_CMD(2,241),		HEX_CMD(2,242) },
		// 63
		{ HEX_CMD(2,245),		HEX_CMD(3,107) },
		{ HEX_CMD(2,246),		HEX_CMD(3,108) },
		{ HEX_CMD(2,247),		HEX_CMD(3,109) },
		{ HEX_CMD(2,248),		HEX_CMD(3,110) },
		{ HEX_CMD(2,249),		HEX_CMD(3,111) },
		{ HEX_CMD(2,250),		HEX_CMD(3,112) },
		{ HEX_CMD(2,251),		HEX_CMD(3,113) },
		{ HEX_CMD(2,252),		HEX_CMD(3,114) },
			// 71
		{ HEX_CMD(2,253),		HEX_CMD(3,115) },
		{ HEX_CMD(2,254),		HEX_CMD(3,116) },
		{ HEX_CMD(2,255),		HEX_CMD(3,117) },
		{ HEX_CMD(2,256),		HEX_CMD(3,118) },
		{ HEX_CMD(2,257),		HEX_CMD(3,119) },
		{ HEX_CMD(2,258),		HEX_CMD(3,120) },
		{ HEX_CMD(2,259),		HEX_CMD(3,121) },
		{ HEX_CMD(2,260),		HEX_CMD(3,122) },
			// 79
		{ HEX_CMD(2,261),		HEX_CMD(3,123) },
		{ HEX_CMD(2,262),		HEX_CMD(3,124) },
		{ HEX_CMD(2,263),		HEX_CMD(3,125) },
		{ HEX_CMD(2,264),		HEX_CMD(3,126) },
		{ HEX_CMD(2,265),		HEX_CMD(3,127) },
		{ HEX_CMD(2,266),		HEX_CMD(3,128) },
		{ HEX_CMD(2,267),		HEX_CMD(3,129) },
			// 86
	};
	const static USHORT OpcodeArray_3[][3] =
	{
		{ HEX_CMD(2,173),HEX_CMD(2,174),HEX_CMD(2,175) },
		{ HEX_CMD(2,182),HEX_CMD(2,183),HEX_CMD(2,184) },
		// 2
		{ HEX_CMD(2,187),HEX_CMD(2,188),HEX_CMD(2,189) },
		{ HEX_CMD(2,190),HEX_CMD(2,191),HEX_CMD(2,192) },

		//4
		{ HEX_CMD(2,210),HEX_CMD(2,211),HEX_CMD(2,212) },
		// 5
		{ HEX_CMD(2,221),HEX_CMD(2,222),HEX_CMD(2,223) },
		// 6

	};
	const static USHORT OpcodeArray_4[][4] =
	{
		{ HEX_CMD(2,119),HEX_CMD(2,120),HEX_CMD(3,2),HEX_CMD(3,3) },
		{ HEX_CMD(2,121),HEX_CMD(2,122),HEX_CMD(3,4),HEX_CMD(3,5) },
		{ HEX_CMD(3,13),HEX_CMD(3,14),HEX_CMD(3,15),HEX_CMD(2,127) },
		// 3
		{ HEX_CMD(2,136),HEX_CMD(2,137),HEX_CMD(3,16),HEX_CMD(3,17) },
		// 4
		{ HEX_CMD(3,36),HEX_CMD(3,37),HEX_CMD(3,38),HEX_CMD(3,39) },
		// 5
		{ HEX_CMD(2,155),HEX_CMD(2,156),HEX_CMD(3,43),HEX_CMD(3,44) },
		// 6
		{ HEX_CMD(2,159),HEX_CMD(2,160),HEX_CMD(2,161),HEX_CMD(2,162) },
		// 7
		{ HEX_CMD(2,163),HEX_CMD(2,164),HEX_CMD(2,165),HEX_CMD(2,166) },
		// 8
		{ HEX_CMD(3,45),HEX_CMD(3,46),HEX_CMD(3,47),HEX_CMD(3,48) },
		// 9
		{ HEX_CMD(3,49),HEX_CMD(3,50),HEX_CMD(3,51),HEX_CMD(3,52) },
		// 10
		{ HEX_CMD(2,171),HEX_CMD(2,172),HEX_CMD(3,53),HEX_CMD(3,54) },
		// 11
		{ HEX_CMD(3,55),HEX_CMD(3,56),HEX_CMD(3,57),HEX_CMD(3,58) },
		// 12
		{ HEX_CMD(3,59),HEX_CMD(3,60),HEX_CMD(3,61),HEX_CMD(3,62) },
		// 13
		{ HEX_CMD(3,63),HEX_CMD(3,64),HEX_CMD(3,65),HEX_CMD(3,66) },
		{ HEX_CMD(3,67),HEX_CMD(3,68),HEX_CMD(3,69),HEX_CMD(3,70) },
		// 15
		{ HEX_CMD(4,0),HEX_CMD(4,1),HEX_CMD(4,2),HEX_CMD(4,3) },
		// 16


	};
	const static USHORT OpcodeArray_5[][5] =
	{
		{ HEX_CMD(3,6),HEX_CMD(3,7),HEX_CMD(3,8),HEX_CMD(2,123),HEX_CMD(2,124) },

	};
	
	enum Tables
	{
		OneByteTable,
		TwoByteTable,
		ThreeByteTable
	};
	// TODO: 组和协处理器指令未处理
	const extern Opcode OneByteOpcodeMap[0x100];


	const extern Opcode TwoByteOpcodeMap[0x100];



	const extern Opcode* OpcodeMap[];


	UINT8 GetAsmCmdLen(PVOID code); // 
	
	POpcode Hex2Opcode(BYTE hex, Tables table);
	

	








	/////
	//void GetNextCode(Opcode opcode,std::string& output)
	//{
	//	//,
	//	//	OT_Command,
	//	//	OT_Prefix,
	//	//	OT_Group,
	//	//	OT_Table,
	//	//	OT_Array, // 多指令表
	//	//	OT_ESC
	//	

	//	// 需要一个函数读出一个指令
	//	// 另一个解析出字符串
	//	// 
	//	// 读指令的需要返回指令长度，分析出指令各个部分
	//	// 


	//	// 1 读取一个hex
	//	// 2 查1字节表，根据结果跳转，（多字节、组、协处理器指令、多指令数组、指令）
	//	// 多字节则替换当前表，重复1，读取完毕后恢复表
	//	// 组跟上面一样
	//	// 读取到指令需要先确定前缀、上标、字长，选择对应的指令
	//	// 3 查指令操作数表
	//	// 确定后面需要读取的rm或sib

	//	// 解析步骤
	//	// 根据hex找OneByteOpcodeMap，得到Opcode
	//	// 根据Opcode类型定位，如果是多字节表或组或协处理器指令则跳到对应表继续查表
	//	// 如果是array就找array表
	//	// 如果是前缀则入前缀队列（加入条件选项
	//	// 如果是命令，多个（array）要一个个判断是否符合条件，取得单个命令后取操作数组合
	//	//  分解操作数，多操作数处理（#），根据分解操作数查表处理函数，
	//	// 取到命令可读名，操作数处理可得长度和操作数类型
	//	// 2个步骤分不开，如果分开需要存储解析到的东西，需要时解析后的内容，否则要重新解析才能生成字符串



	//}


}