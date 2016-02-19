#pragma once
#include "AsmState.h"
#include "AsmStateFactory.h"
#include "..\Opcode\OpcodeDef.h"
#include "..\AsmDisassembler.h"
#include "..\AsmStorage.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Byte> :public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param)
		{
			auto storage = param->GetStorage();
			storage->NextByte();
			// 需要根据上个指令的类型确定应该读取哪个表（多字节指令）
			auto lastInstType = storage->GetOpcodeDataStorage()->GetType();
			auto currentInstType = ReadInst(param, lastInstType);
			return OpcodeTypeToStateID(currentInstType);  // 跳转过后的读取位置是没有步进的
		}
	private:
		static OpcodeType ReadInst(AsmStateFactory::ParamType* param, OpcodeType table)
		{
			const OpcodeData* opcodeData = NULL;
			auto storage = param->GetStorage();
			auto index = *storage->GetCurrentPosition();
			auto wapper = param->GetOpcodeDataWapper();
			opcodeData = &wapper->GetOpcodeData(table, index);
			// 根据已有条件选择指令
			for (auto i = 0; i < opcodeData->Count; i++)
			{
				if (SelectInst(param, wapper->GetHex_Inst(opcodeData->Hex_InstIndex + i)))
				{
					break;
				}
			}
			return storage->GetOpcodeDataStorage()->GetType();
		}
		
		
		static bool SelectInst(AsmStateFactory::ParamType* param, const Hex_Inst & hexInst)
		{
			Superscript tmpInstSs = (Superscript)NULL;
			PrefixCondition tmpInstPfxcdt = (PrefixCondition)NULL;
			auto storage = param->GetStorage();
			auto opcodeDataStorage = storage->GetOpcodeDataStorage();
			auto opcodeDataWapper = param->GetOpcodeDataWapper();
			if (!opcodeDataStorage->IsEmpty())
			{
				opcodeDataStorage->Clear();
			}
			auto instType = (OpcodeType)hexInst.Type;
			assert(instType != (OpcodeType)NULL);
			switch (instType)
			{
			case OT_Inst:
			case OT_Inst_Change:
			{
				const InstData* tmpInst = NULL;
				if (instType == OT_Inst_Change)
				{
					// 两个结构体类型只有最后一个成员变量的区别，此时不使用所以当作同一类型
					tmpInst = reinterpret_cast<const InstData*>(&opcodeDataWapper->GetInstChange(hexInst.InstIndex));
				}
				else
				{
					tmpInst = &opcodeDataWapper->GetInst(hexInst.InstIndex);
				}
				assert(tmpInst != NULL);
				opcodeDataStorage->SetData(instType, tmpInst);
				tmpInstSs = (Superscript)tmpInst->Ss;
				tmpInstPfxcdt = (PrefixCondition)tmpInst->Pfxcdt;
			}
			break;
			case OT_Prefix:
			{
				auto tmpInst = &opcodeDataWapper->GetPfxInst(hexInst.InstIndex);
				opcodeDataStorage->SetData(instType, tmpInst);
				tmpInstSs = (Superscript)tmpInst->Ss;
			}
			break;
			case OT_Grp:
			{
				auto tmpInst = &opcodeDataWapper->GetGrpInst(hexInst.InstIndex);
				opcodeDataStorage->SetData(instType, tmpInst);
				tmpInstSs = (Superscript)tmpInst->Ss;
			}
			break;
			default:
				opcodeDataStorage->SetData(instType, NULL);
				return true;
			}
			auto result = VerifyCondition(param,tmpInstSs, tmpInstPfxcdt);
			if (!result)
			{
				// 验证失败清空临时数据
				opcodeDataStorage->Clear();
			}
			return result;
		}
		
		// ss和pfx都为指令数据
		static bool VerifyCondition(AsmStateFactory::ParamType* param, Superscript ss, PrefixCondition pfx)
		{
			auto storage = param->GetStorage();
			auto prefixStorage = storage->GetPrefixStorage();
			if (pfx != NULL && ((pfx & prefixStorage->GetCurrentPfxcdt()) != pfx))
			{
				return false;
			}
			switch (ss)
			{
			case S_i64:
				return storage->IsX32();
			case S_o64:
				return !storage->IsX32();
			default:
				return true;
			}
		}
		static int OpcodeTypeToStateID(OpcodeType opType)
		{
			switch (opType)
			{
			case OT_Inst:
			case OT_Inst_Change:
				return AsmStateFactory::State_Instruction;
			case OT_Grp:
				return AsmStateFactory::State_Group;
			case OT_Table_0F:
			case OT_Table_0F38:
			case OT_Table_0F3A:
				return AsmStateFactory::State_Byte;
			case OT_Esc:
				return AsmStateFactory::State_Escape;
			case OT_Prefix:
				return AsmStateFactory::State_Prefix;
			default:
				break;
			}
			return AsmStateFactory::State_PreEnd;
		}
	};
}  // namespace Disassembler