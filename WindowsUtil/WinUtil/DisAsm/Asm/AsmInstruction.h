#pragma once
#include "..\Common\Common.h"
#include "Opcode\AsmOpcodeWapper.h"

class StateFactory;
class AsmInstruction
	:public Instruction
{
	friend class InitState;
	friend class SibState;
	friend class RmState;
	friend class EscapeState;
	friend class GroupState;
	friend class InstructionState;
	friend class PrefixState;
	friend class ByteState;
	friend class EndState;
	friend class OperandState;
	friend class AsmOpcodeWapper;
	shared_ptr<AsmOpcodeWapper> wapper;
	bool isX32;
	shared_ptr<_STD ostringstream> outputStr;

	// 以下是状态中需要传递的临时变量（只用来存OpcodeData里的东西）
	const void* tmpInstData;
	OpcodeType tmpInstType;

	// 取临时数据指针,下表为对应类型
	// OT_Inst - InstData
	// OT_Inst_Change - InstChangeData
	// OT_Prefix - PrefixInstData
	// OT_Grp - GrpInstData
	// OT_Table_0F - 无
	// OT_Table_0F38 - 无
	// OT_Table_0F3A - 无
	// OT_Esc - 无
	template<typename TOpcodeData>
	const TOpcodeData* GetTmpData()
	{
		return reinterpret_cast<const TOpcodeData*>(tmpInstData);
	}
	OpcodeType GetTmpInstType();
	void SetTmpData(OpcodeType type, const void* ptr);
	void ClearTmpData();
	// end


	_STD shared_ptr<AsmOpcodeWapper>& GetOpcodeDataWapper();
	void SetOutputStream(shared_ptr<_STD ostringstream>& output)
	{
		outputStr = output;
	}
	bool IsX32();
	// TODO: 取得当前前缀判断条件（非已有前缀）
	int GetCurrentPfxcdt();
	// 以当前游标位置作为起始读取指令（表123指令）并步进,
	// 参数表示表类型，只有1(用None表示)、0F、0F38、0F3A表
	OpcodeType ReadInst(OpcodeType table);
	// 判断是否选择该指令关系 ,需要判断当前读取到的前缀组合（只有66、F2、F3）
	// 成功后返回true会把相应数据存储在自身临时变量里，类型设置为选择到的类型
	// 返回失败返回false表示指令不存在，同时GetTmpInstType()为NULL
	bool SelectInst(const Hex_Inst& hexInst);
	bool VerifyCondition(Superscript ss, PrefixCondition pfx);
public:
	// 实例化时设置解析指令字长
	explicit AsmInstruction(const shared_ptr<StateFactory>& factory, bool isX32);
	// 初始化,设置起始读取位置
	virtual void Init(const void* ptr) override;
	~AsmInstruction();
};
