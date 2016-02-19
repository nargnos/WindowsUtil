#pragma once
#include "..\Common\Storage.h"
#include "Opcode\OpcodeDef.h"
#include <queue>
namespace Disassembler
{
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

	// 主要的存储区
	class AsmStorage :public StorageBase
	{
	public:

		AsmStorage();

		void SetX32(bool is32);
		bool IsX32() const;
		OperandGroupStorage* GetOperandGroupStorage();
		OpcodeDataStorage* GetOpcodeDataStorage();
		NameStorage* GetNameStorage();
		PrefixStorage* GetPrefixStorage();
		virtual void Clear() override;
	private:
		OperandGroupStorage operandGrpStorage;
		OpcodeDataStorage opcodeDataStorage;
		NameStorage nameStorage;
		PrefixStorage prefixStorage;
		bool isX32;


	};
}  // namespace Disassembler
