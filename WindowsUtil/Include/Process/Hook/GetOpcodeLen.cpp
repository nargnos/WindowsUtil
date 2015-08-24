#include "GetOpcodeLen.h"


namespace Process
{
	namespace Hook
	{
		
		GetOpcodeLen::GetOpcodeLen(bool is32):is32(is32)
		{
			
		}


		GetOpcodeLen::~GetOpcodeLen()
		{

		}
		void GetOpcodeLen::Reset()
		{
			stat = Stat_ReadHex;
			table = OneByteOpcode;
			prefix.swap(std::queue<OpcodePrefixGroup>());
			has66 = false;
			has67 = false;
			hasF2= false;
			hasF3= false;
			isGroupExist[0] = isGroupExist[1] = isGroupExist[2] = isGroupExist[3] = false;
		}
		int GetOpcodeLen::GetLen(PUINT8 hex)
		{
			Reset();
			startPos = currentPos = hex;
			do
			{
				count++;
				switch (stat)
				{
				case Process::Hook::Stat_ReadHex:
					stat = _ReadHex(*currentPos);
					break;
				case Process::Hook::Stat_ReadRM:
					stat = _ReadRM(*currentPos);
					break;
				case Process::Hook::Stat_ReadSib:
					stat = _ReadSib(*currentPos);
					break;
				default:
					break;
				}
				currentPos++;
			} while (stat != Stat_End);

			return count;
		}
		bool GetOpcodeLen::IsOpcodeExDefine(OpcodeEx&  cmd)
		{
			OpcodeType type = (OpcodeType)cmd.Type;
			assert(type != Process::Hook::OT_Prefix && type != Process::Hook::OT_Esc);
			switch (type)
			{
			case Process::Hook::OT_None:
				return false;
			case Process::Hook::OT_Grp:
			case Process::Hook::OT_Grp_E:
			case Process::Hook::OT_Table:
				return true;
			default:
				break;
			}
			if (cmd.PrefixCondition == NULL)
			{
				return false;
			}
			// 取prefix看看是否满足条件
			assert(type == Process::Hook::OT_Cmd);

			// NOTICE: 67会改变modrm查找表，现在的定义可能漏了

			// 格式 OPC_F2 OPC_F3 OPC_66 OPC_None
			auto opc = (OpcodePrefixCondition)cmd.PrefixCondition;

			BYTE verifyOpc = OPC_None;
			if (has66)
			{
				verifyOpc |= OPC_66;
			}
			if (hasF2)
			{
				verifyOpc |= OPC_F2;
			}
			if (hasF3)
			{
				verifyOpc |= OPC_F3;
			}
			// 验证,只要有一个通过都算
			if (verifyOpc&opc)
			{
				return true;
			}
			// 不通过则指令未定义
			return false;
		}
		void GetOpcodeLen::AddImmCount(OpcodeLenType len)
		{
			
			// 配合前缀处理大小
			int size = 0;
			switch (len)
			{
			case Process::Hook::OLT_B:
				size = sizeof(BYTE);
				break;
			case Process::Hook::OLT_W_D: // 16位时W，32、64时D
				size = has66 ? sizeof(WORD) : sizeof(DWORD);
				break;
			case Process::Hook::OLT_W:
				size = sizeof(WORD);
				break;
			case Process::Hook::OLT_W_D_D64:// 64默认64不能编32
				if (is32)
				{
					size = has66 ? sizeof(WORD) : sizeof(DWORD);
				}
				else
				{
					size = has66 ? sizeof(WORD) : sizeof(DWORD64);
				}
				break;
			case Process::Hook::OLT_B_D64:
				if (is32)
				{
					size = has66 ? sizeof(BYTE) : sizeof(DWORD);
				}
				else
				{
					size = has66 ? sizeof(BYTE) : sizeof(DWORD64);
				}
				break;
			case Process::Hook::OLT_W_D_Q:
				if (is32)
				{
					size = has66 ? sizeof(DWORD) : sizeof(WORD);
				}
				else
				{
					size = has66 ? sizeof(DWORD64) : sizeof(WORD);
				}
				break;
			case Process::Hook::OLT_W_And_B:// 3字节
				size = sizeof(WORD) + sizeof(BYTE);
				break;
			case Process::Hook::OLT_B_F64:
				size = is32 ? sizeof(BYTE) : sizeof(DWORD64);
				break;
			case Process::Hook::OLT_W_F64:
				size = is32 ? sizeof(WORD) : sizeof(DWORD64);
				break;
			case Process::Hook::OLT_W_D_F64:
				if (is32)
				{
					size = has66 ? sizeof(WORD) : sizeof(DWORD);
				}
				else
				{
					size = sizeof(DWORD64);
				}
				break;
			default:
				break;
			}

			count += size;
		}
		NextStat GetOpcodeLen::_ReadHex(BYTE hex)
		{
			
			Opcode tmpOpcode;
			OpcodeEx tmpOpcodeEx;
			// 初步处理，查表
			switch (table)
			{
			case Process::Hook::OneByteOpcode:
				tmpOpcode = OneByteTable[hex];
				break;
			case Process::Hook::TwoByteOpcode:
				tmpOpcodeEx = TwoByteTable[hex];
				goto ANALY_OPCODEEX;
			case Process::Hook::ThreeByteOpcode_38:
				tmpOpcodeEx = ThreeByteTable_0F38[hex];
				goto ANALY_OPCODEEX;
			case Process::Hook::ThreeByteOpcode_3A:
				tmpOpcodeEx = ThreeByteTable_0F3A[hex];

			ANALY_OPCODEEX:
				if (!IsOpcodeExDefine(tmpOpcodeEx))
				{
					// 这个命令无定义,OD解析里有bug，依照vs里的来
					// 终止这个不正确解析，返回这一堆不正确hex的长度
					return Stat_End;
				}
			
				tmpOpcode = *(POpcode)&tmpOpcodeEx;

				break;
			default:
				break;
			}

			// 类型处理
			switch ((OpcodeType)tmpOpcode.Type)
			{
			case Process::Hook::OT_None:
				return Stat_End;
			case Process::Hook::OT_Cmd:
				return _AnalyCmd(tmpOpcode.Cmd);
			case Process::Hook::OT_Grp:
				return _AnalyGroup(tmpOpcode.Group.Index);
			case Process::Hook::OT_Grp_E:
				return _AnalyGroup_E(tmpOpcode.Group_E);
			case Process::Hook::OT_Table:
				return _SwitchTable((OpcodeTables)tmpOpcode.Table.Index);
			case Process::Hook::OT_Esc:
				return _AnalyEsc(hex);
			case Process::Hook::OT_Prefix:
				return _AnalyPrefix((OpcodePrefixGroup)tmpOpcode.Prefix.PrefixGroup, hex);
			default:
				break;
			}

			return Stat_End;
		}
		NextStat GetOpcodeLen::_ReadRM(BYTE hex)
		{
			// 这里前缀67用16的表，否则用32的表，可能有问题
			
			// mod reg/opcode rm
			// 表16
			// mod=00 rm=110 disp16
			// mod=01 +disp8
			// mod=10 +disp16
			// 32
			// mod=00 rm=100 sib rm=101 disp32
			// mod=01 +disp8 其中 rm=100 sib+disp8
			// mod=10 +disp32 其中 rm=100 sib+disp32
			auto modrm = (POpcodeModRM)&hex;
			auto mod = modrm->Mod;
			auto rm = modrm->Rm;
			if (has67)
			{
				switch (mod)
				{
				case (BYTE)0:
					if (rm==(BYTE)6)
					{
						count += sizeof(WORD);
					}
					break;
				case (BYTE)1:
				case (BYTE)2:
					count += mod*sizeof(BYTE);
					break;
				default:
					break;
				}
			}
			else
			{
				if (mod == (BYTE)0)
				{
					if (rm == (BYTE)4)
					{
						return Stat_ReadSib;
					}
					else if (rm == (BYTE)5)
					{
						count += sizeof(DWORD);
					}
					return Stat_End;
				}
				else if (mod == (BYTE)1)
				{
					count += sizeof(BYTE);
				}
				else if (mod == (BYTE)2)
				{
					count += sizeof(DWORD);
				}
				if (rm==(BYTE)4)
				{
					return Stat_ReadSib;
				}
			}

			return Stat_End;
		}
		NextStat GetOpcodeLen::_ReadSib(BYTE hex)
		{
			return Stat_End;
		}
		NextStat GetOpcodeLen::_SwitchTable(OpcodeTables table)
		{
			this->table = table;
			return Stat_ReadHex;
		}
	
		NextStat GetOpcodeLen::_AnalyPrefix(OpcodePrefixGroup prefixGroup, BYTE hex)
		{
			assert(prefixGroup != OPG_None);
			// 处理前缀冲突
			auto groupIndex = prefixGroup - 1;
			if (isGroupExist[groupIndex])
			{
				// 冲突
				while (!prefix.empty())
				{
					if (prefix.front() == prefixGroup)
					{
						prefix.pop();
						break;
					}
					else
					{
						prefix.pop();
					}
				} 
				count -= prefix.size() + 1;
				// 这个冲突前缀是下个命令的开始
				return Stat_End;
			}
			else
			{
				isGroupExist[groupIndex] = true;
				prefix.push(prefixGroup);
			}
			// 设置多字节表标记
			if (hex==(BYTE)0x66)
			{
				has66 = true;
			}
			if (hex == (BYTE)0x67)
			{
				has67 = true;
			}
			if (hex == (BYTE)0xf2)
			{
				hasF2 = true;
			}
			if (hex == (BYTE)0xf3)
			{
				hasF3 = true;
			}
			
			return Stat_ReadHex;
		}
		NextStat GetOpcodeLen::_AnalyCmd(OpcodeCmd& cmd)
		{
			AddImmCount((OpcodeLenType)cmd.LenType);// 添加立即数长度
			
			if (cmd.HasRM)
			{
				return Stat_ReadRM;
			}
			return Stat_End;
		}
		NextStat GetOpcodeLen::_AnalyGroup(BYTE grpIndex)
		{
			// 读组信息，判断是否需要读大小或RM
			count++;
			currentPos++;
			BYTE groupInfo = *currentPos;


			return NextStat();
		}
		NextStat GetOpcodeLen::_AnalyGroup_E(OpcodeGroup_E& grpe)
		{
			// 读rm且读组表
			AddImmCount((OpcodeLenType)grpe.IbIzNone);
			 // 借普通组的函数
			if (_AnalyGroup(grpe.GroupIndex) == Stat_End)
			{
				return Stat_End;
			}			
			return Stat_ReadRM;
		}
		NextStat GetOpcodeLen::_AnalyEsc(BYTE hex)
		{
			auto tmprm = (POpcodeModRM)&hex;
			if (!EscMap[hex - 0xd8])
			{
				return Stat_End;
			}
			return Stat_ReadRM;
		}
		
	}
}