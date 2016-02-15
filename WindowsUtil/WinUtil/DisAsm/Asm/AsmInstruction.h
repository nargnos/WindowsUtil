#pragma once
#include "..\Common\Common.h"
#include "Opcode\AsmOpcodeDataWapper.h"
#include <queue>

// 用来临时存储一些变量
class IInstructionStorage
{
public:
	IInstructionStorage()
	{
	}

	virtual ~IInstructionStorage()
	{
	}
	virtual void Clear() = 0;
	virtual bool IsEmpty() = 0;
};

class OperandGroupStorage :public IInstructionStorage
{
public:
	OperandGroupStorage()
	{
	}

	~OperandGroupStorage()
	{
	}
	virtual bool IsEmpty() override
	{
		return operandCount == 0 && operandGrp == NULL;
	}
	virtual void Clear() override
	{
		SetOperandGrp(0, NULL);
	}
	void SetOperandGrp(unsigned char count, const unsigned char* grp)
	{
		operandCount = count;
		operandGrp = grp;
	}
	const unsigned char* GetOperandGrp() const
	{
		return operandGrp;
	}
	unsigned char GetOperandCount() const
	{
		return operandCount;
	}
private:
	// 以下是读取操作数需要记录的信息
	const unsigned char* operandGrp;
	unsigned char operandCount;
};

class OpcodeDataStorage :public IInstructionStorage
{
public:
	OpcodeDataStorage()
	{
	}

	~OpcodeDataStorage()
	{
	}
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
	const TOpcodeData* GetData()
	{
		return reinterpret_cast<const TOpcodeData*>(tmpInstData);
	}
	void SetData(OpcodeType type, const void* ptr)
	{
		tmpInstType = type;
		tmpInstData = ptr;
	}
	OpcodeType GetType()
	{
		return tmpInstType;
	}
	virtual void Clear() override
	{
		tmpInstType = OT_None;
		tmpInstData = NULL;
	}
	virtual bool IsEmpty() override
	{
		return tmpInstType == OT_None && tmpInstData == NULL;
	}
private:
	// 以下是状态中需要传递的临时变量（只用来存OpcodeData里的东西）
	const void* tmpInstData;
	OpcodeType tmpInstType;
};

class NameStorage :public IInstructionStorage
{
public:
	NameStorage()
	{
	}

	~NameStorage()
	{
	}
	void SetInstName(LPCSTR name)
	{
		// 暂时无视单指令多名情况，只选择第一个
		instName = name;
	}

	virtual void Clear() override
	{
		instName = NULL;
		nameExt = Ext_None;
	}
	virtual bool IsEmpty() override
	{
		return nameExt == Ext_None && instName == NULL;
	}
private:
	// 会把指令名指针存储在这里
	LPCSTR instName;
	// 根据长度属性选择的名字后缀字符（好像可以删掉）
	NameExt nameExt;
};

struct PrefixInstData_Hex_Pair
{
	const PrefixInstData* PfxData;
	unsigned char Hex;
	PrefixInstData_Hex_Pair(unsigned char hex, const PrefixInstData* pfxData)
		:Hex(hex), PfxData(pfxData)
	{

	}
};
class PrefixStorage :public IInstructionStorage
{
public:
	PrefixStorage()
	{
	}

	~PrefixStorage()
	{
	}
	// 返回是否可以push进存储区
	// false是因为前缀组冲突，需要清空队列
	bool Push(unsigned char hex, const PrefixInstData* pfxData)
	{
		// 判断冲突
		if (hasGrp[pfxData->PfxGrp])
		{
			return false;
		}
		if (isEmpty)
		{
			isEmpty = false;
		}
		hasPfx[hex] = true;
		hasGrp[pfxData->PfxGrp] = true;

		// 存储前缀
		pfxQueue.push(make_unique<PrefixInstData_Hex_Pair>(hex, pfxData));
		return true;
	}
	virtual void Clear() override
	{
		isEmpty = true;
		pfxQueue.swap(_STD queue<unique_ptr<PrefixInstData_Hex_Pair>>());

		memset(hasGrp, false, sizeof(hasGrp));
		memset(hasPfx, false, sizeof(hasPfx));
	}
	virtual bool IsEmpty() override
	{
		return isEmpty;
	}
	bool HasPrefix(Prefix pfx)
	{
		return hasPfx[pfx];
	}

	// 取得当前前缀判断条件（非已有前缀,只有66、f2、f3标识）
	unsigned char GetCurrentPfxcdt() const
	{
		return (hasPfx[G3_operand_size] ? C_66 : 0) |
			(hasPfx[G1_repne_xacquire] ? C_F2 : 0) |
			(hasPfx[G1_reprepe_xrelease] ? C_F3 : 0);
	}
private:
	_STD queue<unique_ptr<PrefixInstData_Hex_Pair>> pfxQueue;
	bool isEmpty;
	PrefixCondition pfxcdt;
	bool hasGrp[PfxGrp_End];
	bool hasPfx[0x100];  // 只用到前缀对应hex下标的元素
};



class StateFactory;
// 用来存储状态跳转时的一些中间变量
class AsmInstruction
	:public Instruction
{
	friend class InitState;
	friend class EscapeState;
	friend class GroupState;
	friend class InstructionState;
	friend class PrefixState;
	friend class ByteState;
	friend class EndState;
	friend class OperandState;
	friend class AsmOpcodeDataWapper;
private:
	AsmOpcodeDataWapper opcodeDataWapper;
	const AsmOpcodeDataWapper* GetOpcodeDataWapper() const;

	bool isX32;
	bool IsX32() const;

	OperandGroupStorage operandGrpStorage;
	OpcodeDataStorage opcodeDataStorage;
	NameStorage nameStorage;
	PrefixStorage prefixStorage;




	// 以当前游标位置作为起始读取指令（表123指令）并步进,
	// 参数表示表类型，只有1(用None表示)、0F、0F38、0F3A表
	OpcodeType ReadInst(OpcodeType table);

	// 判断是否选择该指令关系, 如果通过则存储 ,需要判断当前读取到的前缀组合（只有66、F2、F3）
	// 成功后返回true会把 OT_Inst\OT_Inst_Change\OT_Prefix\OT_Grp 的对应类型指针存入opcodeDataStorage
	// 返回失败返回false表示指令不存在，同时GetType()为NULL
	// 非switch里的类型会无条件返回true
	bool SelectInst(const Hex_Inst& hexInst);

	// 以当前读取到的信息验证指令是否存在
	bool VerifyCondition(Superscript ss, PrefixCondition pfx) const;

	// 是否记录读取到的字符串信息(先初步分类记录信息，而后再一并输出)
	bool needOutput;
	bool IsNeedOutput() const;


public:
	// 实例化时用isX32设置解析指令字长, 
	// needOutput表示是否解析结果保存为字符串，如果为false，只会读出指令长度，所有中间数据都不会解析
	explicit AsmInstruction(const shared_ptr<StateFactory>& factory, bool isX32, bool needOutput);

	~AsmInstruction();

};
