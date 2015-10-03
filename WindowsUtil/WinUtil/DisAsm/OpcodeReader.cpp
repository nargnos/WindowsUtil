#include "OpcodeReader.h"
namespace Asm
{
	OpcodeReader::OpcodeReader(bool is32)
	{
		
		this->is32 = is32;
		table = OneByteTable;
		prefix.Reset();
		currentStat = ReadHex;
	}

	OpcodeReader::~OpcodeReader()
	{

	}

	OpcodeReader::AnalyticFunction OpcodeReader::OpTypeAnalyticFunction[] =
	{
		__OutputNone,
		__AnalyCmd,
		__QueuePrefix,
		__SwitchGroup,
		__SwitchTable,
		__ArraySelection,
		__SwitchESC,

		__ReadNextHex,
		__AnalyModRM,
		__AnalySIB,
		__AnalyOffset,
		__AnalyImm

	};

	int OpcodeReader::ReadCode(PUINT8 hex, std::string* output)
	{
		this->code = current = hex;
		//opcode1 = Hex2Opcode(current[0], table);
		tmpStr = output;
		do
		{
			currentStat =  OpTypeAnalyticFunction[currentStat](*this);
		} while (currentStat != AnalyEnd);
		// 重置供下次使用
		currentStat = ReadHex; 
		table = OneByteTable;
		 return current - code;
	}

	OpcodeReaderStat __ReadNextHex(OpcodeReader & tmpData)
	{
		// 从当前搜索表读取opcode存入tmpopcode
		tmpData.tmpCode = *Hex2Opcode(*tmpData.current, tmpData.table);
		tmpData.current++;
		// TODO: 这里要判断读取的是否为rm或sib
		return (OpcodeReaderStat)tmpData.tmpCode.OpType;
	}

	OpcodeReaderStat __AnalyModRM(OpcodeReader & tmpData)
	{
		return OpcodeReaderStat();
	}

	OpcodeReaderStat __AnalySIB(OpcodeReader & tmpData)
	{
		return OpcodeReaderStat();
	}

	OpcodeReaderStat __AnalyOffset(OpcodeReader & tmpData)
	{
		return OpcodeReaderStat();
	}

	OpcodeReaderStat __AnalyImm(OpcodeReader & tmpData)
	{
		return OpcodeReaderStat();
	}

	

	void OpcodeReader::AppendOutput(PSTR str, BYTE sizeOption)
	{
		if (tmpStr)
		{
			tmpStr->append(str);
			// TODO: 判断大小选择合适的符号

		}
	}
	
	// 处理单个操作数
	void _AnalyOperand(const RegOrOperandGroup& operand, OpcodeReader & tmpData)
	{
	}
	OpcodeReaderStat _AnalyOperand0(const ZeroOperand& cmd, OpcodeReader & tmpData)
	{
		tmpData.AppendOutput((PSTR)InstructionNames[cmd.NameID], cmd.SizeOption);
		
		return AnalyEnd; // 不需要读其它信息，处理结束直接返回
	}

	OpcodeReaderStat _AnalyOperand1(const OneOperand& cmd, OpcodeReader & tmpData)
	{
		tmpData.AppendOutput((PSTR)InstructionNames[cmd.NameID],cmd.SizeOption);
		auto op = Operands[cmd.OperandIndex];
		_AnalyOperand(op, tmpData);////////////
		_AnalyOperand(Operands[cmd.OperandIndex_Ext], tmpData);

		return AnalyEnd;
	}

	OpcodeReaderStat _AnalyOperand2(const TwoOperands& cmd, OpcodeReader & tmpData)
	{
		//tmpData.AppendOutput((PSTR)InstructionNames[Opcode_2[cmd.Index].NameID]);
		// 确定操作数个数
		// 处理单个操作数，直到处理完毕
		return AnalyEnd;
	}

	OpcodeReaderStat _AnalyOperand3(const ThreeOperands& cmd, OpcodeReader & tmpData)
	{
		//tmpData.AppendOutput((PSTR)InstructionNames[Opcode_3[cmd.Index].NameID]);
		return AnalyEnd;
	}

	OpcodeReaderStat _AnalyOperand4(const FourOperands& cmd, OpcodeReader & tmpData)
	{
		//tmpData.AppendOutput((PSTR)InstructionNames[Opcode_4[cmd.Index].NameID]);
		return AnalyEnd;
	}
	//OpcodeReader::AnalyOperand OpcodeReader::AnalyOperandFunction[]=
	//{
	//	_AnalyOperand0,
	//	_AnalyOperand1,
	//	_AnalyOperand2,
	//	_AnalyOperand3,
	//	_AnalyOperand4
	//};
	//
	bool IsOpcodeDefine(Superscripts s, OpcodeReader& tmpData)
	{
		if (s==S_o64)
		{
			return !tmpData.is32;
		}
		if (s==S_i64)
		{
			return tmpData.is32;
		}

		return true;
	}

	OpcodeReaderStat __OutputNone(OpcodeReader & tmpData)
	{
		tmpData.AppendOutput("???");
		//tmpData.current++;
		return AnalyEnd;
	}

	OpcodeReaderStat __AnalyCmd(OpcodeReader & tmpData)
	{
		// 定义是检测上标，判断在目标系统有没有定义这个指令
#define CHECK_OPCODE_DEFINE(opcount) \
	{\
		auto opcodeInfo = Opcode_##opcount[cmd.Index];\
		if (!IsOpcodeDefine((Superscripts)opcodeInfo.Superscript,tmpData))return OpNone;\
		return _AnalyOperand##opcount(opcodeInfo, tmpData);\
	}
		// 检测是否合法
		auto cmd = tmpData.tmpCode.Command;
		

		assert(cmd.OpCount >= 0 && cmd.OpCount <= 4);
		switch (cmd.OpCount)
		{
		case 0:
			CHECK_OPCODE_DEFINE(0);
		case 1:
			CHECK_OPCODE_DEFINE(1);
		case 2:
			CHECK_OPCODE_DEFINE(2);
		case 3:
			CHECK_OPCODE_DEFINE(3);
		case 4:
			CHECK_OPCODE_DEFINE(4);

		default:
			break;
		}
		return AnalyEnd;
	}

	OpcodeReaderStat __QueuePrefix(OpcodeReader & tmpData)
	{
		// 如果出现冲突，转入输出
		// 否则入队继续读取
		auto tmpPrefix = tmpData.tmpCode.Prefix;
		auto prefixOutput = tmpData.prefix.Push(tmpPrefix);
		if (prefixOutput)
		{
			// 前缀组冲突,此时已出队到不冲突的状态，根据返回的数值设定当前读头，读头之前的前缀表示冲突的前缀组合
			//tmpData.current += prefixOutput;
			// 输出冲突前缀
			auto conflict = tmpData.prefix.ConflictQueues;
			do
			{
				auto conflictPrefix = conflict.front();				
				tmpData.AppendOutput((PSTR)InstructionNames[Opcode_Prefixs[conflictPrefix.Index].NameID]);
				conflict.pop();
			} while (conflict.empty());
			return AnalyEnd; // 此时前缀队列可能还会有值,在读取到cmd时清空
		}
		else
		{
			return ReadHex;
		}
		
	}

	OpcodeReaderStat __SwitchGroup(OpcodeReader & tmpData)
	{
		return ReadHex;
	}

	OpcodeReaderStat __SwitchTable(OpcodeReader & tmpData)
	{
		// 切换搜索表
		tmpData.table = (Tables)tmpData.tmpCode.Table.Index;
		//tmpData.current++;
		return ReadHex;
	}

	OpcodeReaderStat __ArraySelection(OpcodeReader & tmpData)
	{
		// 判断前缀
		// 成功读取到转入cmd流程，失败输出???
		return ReadHex;
	}

	OpcodeReaderStat __SwitchESC(OpcodeReader & tmpData)
	{
		return ReadHex;
	}

}
