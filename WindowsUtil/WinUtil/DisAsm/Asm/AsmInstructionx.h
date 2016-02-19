//#pragma once
//#include "..\Common\Common.h"
//#include "Opcode\AsmOpcodeDataWapper.h"

//
//
//
//class StateFactory;
//// 用来存储状态跳转时的一些中间变量
//class AsmInstruction
//	:public Instruction
//{
//	friend class InitState;
//	friend class EscapeState;
//	friend class GroupState;
//	friend class InstructionState;
//	friend class PrefixState;
//	friend class ByteState;
//	friend class EndState;
//	friend class OperandState;
//	friend class AsmOpcodeDataWapper;
//private:
//	AsmOpcodeDataWapper opcodeDataWapper;
//	const AsmOpcodeDataWapper* GetOpcodeDataWapper() const;
//
//	bool isX32;
//	bool IsX32() const;
//
//	OperandGroupStorage operandGrpStorage;
//	OpcodeDataStorage opcodeDataStorage;
//	NameStorage nameStorage;
//	PrefixStorage prefixStorage;
//
//
//
//
//	// 以当前游标位置作为起始读取指令（表123指令）并步进,
//	// 参数表示表类型，只有1(用None表示)、0F、0F38、0F3A表
//	OpcodeType ReadInst(OpcodeType table);
//
//	// 判断是否选择该指令关系, 如果通过则存储 ,需要判断当前读取到的前缀组合（只有66、F2、F3）
//	// 成功后返回true会把 OT_Inst\OT_Inst_Change\OT_Prefix\OT_Grp 的对应类型指针存入opcodeDataStorage
//	// 返回失败返回false表示指令不存在，同时GetType()为NULL
//	// 非switch里的类型会无条件返回true
//	bool SelectInst(const Hex_Inst& hexInst);
//
//	// 以当前读取到的信息验证指令是否存在
//	bool VerifyCondition(Superscript ss, PrefixCondition pfx) const;
//
//	// 是否记录读取到的字符串信息(先初步分类记录信息，而后再一并输出)
//	bool needOutput;
//	bool IsNeedOutput() const;
//
//
//public:
//	// 实例化时用isX32设置解析指令字长, 
//	// needOutput表示是否解析结果保存为字符串，如果为false，只会读出指令长度，所有中间数据都不会解析
//	explicit AsmInstruction(const shared_ptr<StateFactory>& factory, bool isX32, bool needOutput);
//
//	~AsmInstruction();
//
//};
