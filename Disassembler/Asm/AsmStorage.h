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
		virtual bool IsEmpty() const = 0;
	};

	class OperandGroupStorage :public IInstructionStorage
	{
	public:
		// 最多只有4个参数
		static constexpr int MaxCount = 4;
		OperandGroupStorage()
		{
			isEmpty = true;
		}

		~OperandGroupStorage()
		{
		}
		virtual bool IsEmpty() const override
		{
			// 取数据是需要判断参数个数，为0表示空
			return operandCount == 0;
		}
		virtual void Clear() override
		{
			memset(operandInfo, 0, MaxCount);
			memset(operandInfoType, OVT_RegOrOperandGroupID, MaxCount);

			isEmpty = true;
		}
		// 先会设置操作数的类型
		// 之后解析后覆盖为解析后的内容
		void SetOperandGrp(unsigned char count, const unsigned char* grp)
		{
			assert(grp != NULL);
			assert(count <= MaxCount);
			operandCount = count;
			memcpy_s(operandInfo, MaxCount, grp, count);
		}
		
		unsigned char GetOperandCount() const
		{
			return operandCount;
		}
		SizeAttribute GetOperandSizeAttribute() { return operandSizeAttribute; }
		void SetOperandSizeAttribute(SizeAttribute size) { operandSizeAttribute = size; }
		SizeAttribute GetAddressSizeAttribute() { return addressSizeAttribute; }
		void SetAddressSizeAttribute(SizeAttribute size) { addressSizeAttribute = size; }
		
		
		
		// 使用OperandValueType类型区分，如果是值类型，单位是bit
		void SetOperandInfo(int index, unsigned char info)
		{
			assert(index < MaxCount);
			operandInfo[index] = info;
		}
		// 值类型的单位是bit
		unsigned char GetOperandInfo(int index)
		{
			return operandInfo[index];
		}
		OperandValueType GetOperandInfoType(int index)
		{
			return operandInfoType[index];
		}
		void SetOperandInfoType(int index, OperandValueType type)
		{
			operandInfoType[index] = type;
		}
	private:
		bool isEmpty;
		// 以下是读取操作数需要记录的信息
		//const unsigned char* operandGrp;
		unsigned char operandCount;
		SizeAttribute operandSizeAttribute;
		SizeAttribute addressSizeAttribute;
		// 操作数的描述信息
		// 如果是REG类型的，值为OperandType的reg部分（去除多重选项）
		unsigned char operandInfo[MaxCount];
		OperandValueType operandInfoType[MaxCount];
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
			tmpInstData = nullptr;
		}
		virtual bool IsEmpty() const override
		{
			return tmpInstType == OT_None && tmpInstData == nullptr;
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
			instName = nullptr;
			nameExt = Ext_None;

		}
		virtual bool IsEmpty() const override
		{
			return nameExt == Ext_None && instName == nullptr;
		}
		void SetNameExt(NameExt val)
		{
			nameExt = val;
		}
		NameExt GetNameExt() const
		{
			return nameExt;
		}
	private:
		// 会把指令名指针存储在这里
		LPCSTR instName;
		// 根据长度属性选择的名字后缀字符
		NameExt nameExt;
	};

	struct PrefixInstData_Hex_Pair
	{
		const PrefixInstData* PfxData;
		const unsigned char* Hex;
		PrefixInstData_Hex_Pair(const unsigned char* hex, const PrefixInstData* pfxData)
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
		bool Push(const unsigned char* hex, const PrefixInstData* pfxData)
		{
			if (HasRex())
			{
				// rex前缀必须在opcode前，不准有其它前缀出现
				return false;
			}
			// 判断冲突
			if (hasGrp[pfxData->PfxGrp])
			{
				return false;
			}
			if (isEmpty)
			{
				isEmpty = false;
			}

			hasPfx[*hex] = true;
			hasGrp[pfxData->PfxGrp] = true;
			// 保存rex前缀随时取用
			if ((unsigned char)pfxData->PfxGrp == PfxGrp_Rex)
			{
				rex = hex;
			}
			// 存储前缀
			pfxQueue.push(make_unique<PrefixInstData_Hex_Pair>(hex, pfxData));
			return true;
		}
		virtual void Clear() override
		{
			isEmpty = true;
			pfxQueue.swap(_STD queue<unique_ptr<PrefixInstData_Hex_Pair>>());
			rex = nullptr;
			memset(hasGrp, false, sizeof(hasGrp));
			memset(hasPfx, false, sizeof(hasPfx));
		}
		virtual bool IsEmpty() const override
		{
			return isEmpty;
		}

		bool HasRex() const
		{
			return hasGrp[PfxGrp_Rex];
		}
		const RexPrefix* GetRex() const
		{
			return reinterpret_cast<const RexPrefix*>(rex);
		}
		bool IsOverrideSegment() const
		{
			return hasGrp[PfxGrp_2];
		}

		bool IsOverrideAddressSize() const
		{
			return hasPfx[G4_address_size];
		}

		bool IsOverrideOperandSize() const
		{
			return hasPfx[G3_operand_size];
		}
		// 使用寄存器的定义返回
		OperandType GetOverrideSegment() const
		{
			if (hasPfx[G2_seg_cs])
			{
				return SEG_CS;
			}
			if (hasPfx[G2_seg_ds])
			{
				return SEG_DS;
			}
			if (hasPfx[G2_seg_es])
			{
				return SEG_ES;
			}
			if (hasPfx[G2_seg_fs])
			{
				return SEG_FS;
			}
			if (hasPfx[G2_seg_gs])
			{
				return SEG_GS;
			}
			if (hasPfx[G2_seg_ss])
			{
				return SEG_SS;
			}
			assert(false);
			return OT_NULL;
		}

		// 取得当前前缀判断条件（非已有前缀,只有66、f2、f3标识）
		unsigned char GetCurrentMandatoryPrefix() const
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
		const unsigned char* rex;
	};

	// 主要的存储区
	class AsmStorage :public StorageBase
	{
	public:

		AsmStorage();

		void SetSizeMode(bool is32)
		{
			is32Bit = is32;
		}

		OperandGroupStorage* GetOperandGroupStorage();
		OpcodeDataStorage* GetOpcodeDataStorage();
		NameStorage* GetNameStorage();
		PrefixStorage* GetPrefixStorage();
		bool Is32() const
		{
			return is32Bit;
		}
		virtual void Clear() override;
	private:
		OperandGroupStorage operandGrpStorage;
		OpcodeDataStorage opcodeDataStorage;
		NameStorage nameStorage;
		PrefixStorage prefixStorage;
		bool is32Bit;



	};


}  // namespace Disassembler
