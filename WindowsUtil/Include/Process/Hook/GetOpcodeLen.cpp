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
			if (!prefix.empty())
			{
				prefix.swap(std::queue<OpcodePrefixGroup>());
			}
			
			has66 = 
			has67 = 
			hasF2= 
			hasF3= 
			isGroupExist[0] = isGroupExist[1] = isGroupExist[2] = isGroupExist[3] = false;
			count = 0;
		}
		int GetOpcodeLen::GetLen(PUINT8 hex)
		{
			Reset();
			currentPos = hex;
			do
			{
				count++;
				
				switch (stat)
				{
				case Stat_ReadHex:
					stat = _ReadHex(*currentPos);
					break;
				case Stat_ReadRM:
					stat = _ReadRM(*currentPos);
					break;
				case Stat_ReadSib:
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
			OpcodeType type = (OpcodeType)cmd.Cmd.Type;
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

			return IsPrefixVerify((OpcodePrefixCondition)cmd.PrefixCondition);
		}

		bool GetOpcodeLen::IsPrefixVerify(OpcodePrefixCondition&& opc)
		{
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
			
			// 不通过则指令未定义
			return verifyOpc&opc;
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
			case Process::Hook::OLT_B_D64: // fixed
				if (is32)
				{
					size = has66 ?   sizeof(DWORD):sizeof(BYTE);
				}
				else
				{
					size = has66 ?  sizeof(DWORD64): sizeof(BYTE);
				}
				break;
			case Process::Hook::OLT_W_D_Q://fixed
				if (is32)
				{
					size = has66 ?  sizeof(WORD): sizeof(DWORD);
				}
				else
				{
					size = has66 ?  sizeof(WORD): sizeof(DWORD64);
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
				return;
			}

			count += size;
		}
		GetOpcodeLen::NextStat GetOpcodeLen::_ReadHex(BYTE hex)
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
		GetOpcodeLen::NextStat GetOpcodeLen::_ReadRM(BYTE hex)
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
				else
				{
					// mod == 3
					return Stat_End;
				}
				// mod 1 2 的rm4有sib
				if (rm==(BYTE)4)
				{
					return Stat_ReadSib;
				}
			}

			return Stat_End;
		}
		GetOpcodeLen::NextStat GetOpcodeLen::_ReadSib(BYTE hex)
		{
			return Stat_End;
		}
		GetOpcodeLen::NextStat GetOpcodeLen::_SwitchTable(OpcodeTables table)
		{
			this->table = table;
			return Stat_ReadHex;
		}
	
		GetOpcodeLen::NextStat GetOpcodeLen::_AnalyPrefix(OpcodePrefixGroup prefixGroup, BYTE hex)
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
		GetOpcodeLen::NextStat GetOpcodeLen::_AnalyCmd(OpcodeCmd& cmd)
		{
			AddImmCount((OpcodeLenType)cmd.LenType);// 添加立即数长度
			return cmd.HasRM ? Stat_ReadRM : Stat_End;
		}
		GetOpcodeLen::NextStat GetOpcodeLen::_AnalyGroup(BYTE grpIndex)
		{
			auto grpByte = (POpcodeModRM)&*(currentPos+1);
			auto mod = grpByte->Mod;
			auto nnn = grpByte->Reg; // nnn字段（op/reg

			auto grpOpcode = GroupTable[grpIndex][nnn];
			if (grpOpcode.Val==NULL)
			{
				return Stat_End;
			}
			
			// 判断mod，判断前缀，判断指令
			if (((grpOpcode.Mod&Mod_11b) == Mod_11b) &&
				(grpByte->Mod == (BYTE)3) &&
				!IsPrefixVerify((OpcodePrefixCondition)grpOpcode.Prefix))
			{
				// 11B 该prefix下指令未定义
				return Stat_End;
			}
			else if (((grpOpcode.Mod&Mod_mem) == Mod_mem) &&
				(grpByte->Mod != (BYTE)3) &&
				!IsPrefixVerify((OpcodePrefixCondition)grpOpcode.Prefix))
			{
				// mem 该prefix下指令未定义
				return Stat_End;
			}

			AddImmCount((OpcodeLenType)grpOpcode.IbIzNone);
			return Stat_ReadRM;
		}
		GetOpcodeLen::NextStat GetOpcodeLen::_AnalyGroup_E(OpcodeGroup_E& grpe)
		{
			// 读rm且读组表,这里定义处理过不会出现冲突(同组号，同指令，不同操作数长度的情况
			AddImmCount((OpcodeLenType)grpe.IbIzNone);
			return _AnalyGroup(grpe.GroupIndex);// 借普通组的函数
		}
		GetOpcodeLen::NextStat GetOpcodeLen::_AnalyEsc(BYTE hex)
		{
			//auto tmprm = (POpcodeModRM)&hex;
			
			return EscMap[hex - 0xd8]?Stat_ReadRM: Stat_End;
		}
		
	}
}