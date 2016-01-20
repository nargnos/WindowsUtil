// 类作用是把指令文本转成C++的数据定义弄到c++项目那边使用
// 这里懒得管代码整齐了
// 有可能理解文档理解错的，发现了再改
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpcodeArrayBuilder.Opcode
{
    public class Builder
    {
        Lazy<List<GroupOpcodeData>> grpOpcode = new Lazy<List<GroupOpcodeData>>(() => AnalyOpcodeStr<GroupOpcodeData>(".\\Opcode\\opcodeGrp"));
        Lazy<List<OpcodeData>> opcodes = new Lazy<List<OpcodeData>>(() => AnalyOpcodeStr<OpcodeData>(".\\Opcode\\opcode"));
        private static List<T> AnalyOpcodeStr<T>(string path) where T : IOpcode, new()
        {
            var result = new List<T>();
            using (StreamReader sr = new StreamReader(path))
            {
                while (!sr.EndOfStream)
                {
                    var tmpStr = sr.ReadLine();
                    if (string.IsNullOrEmpty(tmpStr?.Trim()) || tmpStr.StartsWith("#"))
                    {
                        continue;
                    }
                    var tmpItem = new T();
                    tmpItem.Init(tmpStr);
                    result.Add(tmpItem);
                }
            }
            return result;
        }

        
        
        



        public void GetTables()
        {
            // 括号表示多少长度可以满足数据条数, grp esc 指令未包括, 各种ID要从1开始算（查询时再-1），0表示没有
            // 关系数据转成表ID指向数据ID+数据长度形式
            // 1Inst对应一个param，如果出现同名多参数的就分成2个

            // V $pfxcdt(byte:3), xxx ...前缀条件，满足条件指令才成立
            // V $pair(byte), xxx
            // V $name(short:10), xxx
            // V $superscript(byte:4), xxx

            // V $param(byte), param_pairID
            // V $param2(byte), param_pairID, param_pairID
            // V $param3(byte), param_pairID, param_pairID, param_pairID
            // V $param4(byte), param_pairID, param_pairID, param_pairID, param_pairID


            // X $hex(byte), hex_instID
            // $inst(short), type, pfxcdtID(byte:3), superscriptID(byte:4), inst_nameID, paramCount(byte:3), paramID ...指令情况
            // $inst_prefix, type, grp, rex...
            // $inst_table, type,...
            // $inst_esc,...
            // $inst_grp,...

            // X $param_pair(byte), pairID, len
            // V $hex_inst(short), instID, len ...表的内容
            // X $inst_name, nameID, len  // 并到inst里

            // 缺rm1、rm2、sib、esc表

            // $pair
            var pairs = GetOperandPairs().ToList();
            // 可以生成 $name $inst_name 
            List<NameIndex> names = CreateNames();
            // 可以生成param 1234
            List<Param>[] param = GetParams(pairs);

            // $hex_inst - id,count
            Tuple<int, byte>[][] hexInst = new Tuple<int, byte>[4][];
            for (int i = 0; i < hexInst.Length; i++)
            {
                hexInst[i] = new Tuple<int, byte>[0x100];
            }


            List<Inst> insts = new List<Inst>(); // $inst 无grp

            // 根据指令字节分组
            foreach (var table in GetByteTables())
            {

                Tuple<int, byte>[] tmp = null;
                switch (table.Key)
                {
                    case "Byte1":
                        tmp = hexInst[0];// byte1;
                        break;
                    case "Byte2_0F":
                        tmp = hexInst[1];// byte2_0F;
                        break;
                    case "Byte3_38":
                        tmp = hexInst[2];// byte3_0F38;
                        break;
                    case "Byte3_3A":
                        tmp = hexInst[3];// byte3_0F3A;
                        break;
                    default:
                        throw new Exception();
                }
                // 根据指令的HEX分组
                foreach (var opcode in table.ToLookup((op) => op.Hex[op.Hex.Count - 1]))
                {
                    tmp[Convert.ToInt32(opcode.Key, 16)] = new Tuple<int, byte>( insts.Count + 1,(byte)opcode.Count());
                    foreach (var instInfo in opcode)
                    {
                        Inst tmpInst = CreateInst(names, param, instInfo);

                        insts.Add(tmpInst);
                    }
                }
            }
            // 映射组
            var grpConv = from item in grpOpcode.Value
                          select new
                          {
                              Grp = item,
                              Name = names.Find((val) => val.Name.SequenceEqual(item.Name)),
                              Pfxcdt = item.Pfx == null ? string.Empty : string.Join("_", item.Pfx),
                              OpId = item.Operand == null ? 0 : param[item.Operand.Count - 1].FindIndex((p) => item.Operand.SequenceEqual(p.Params)) + 1
                          };



            // 统计一下表
            // var hexInstCount = from item in hexInst select item.Count((val) => val != null);
            // 压缩byte3的两个表 - index - id,count
            List<Tuple<byte, Tuple<int, byte>>> zipByte3_38 = new List<Tuple<byte, Tuple<int, byte>>>();
            List<Tuple<byte, Tuple<int, byte>>> zipByte3_3A = new List<Tuple<byte, Tuple<int, byte>>>();
            for (int i = 0; i < hexInst[2].Length; i++)
            {
                var tmp38 = hexInst[2][i];
                var tmp3A = hexInst[3][i];
                if (tmp38 != null)
                {
                    zipByte3_38.Add(new Tuple<byte, Tuple<int, byte>>((byte)i,tmp38));
                }
                if (tmp3A != null)
                {
                    zipByte3_3A.Add(new Tuple<byte, Tuple<int, byte>>((byte)i, tmp3A));
                }

            }

            //param
            //insts
            //hexInst
            //zipByte3_38
            //zipByte3_3A
            //superscript
            //pfx
           
            //var pfx = GetAllPfxs();
            //StringBuilder pfxcdtCode = new StringBuilder("enum ");
            //var superscript = GetAllSuperScripts();

            //StringBuilder superscriptCode = new StringBuilder();

            var pairsCode = GetOperandDefs(pairs);
            var namesCode = GetNamesDefCode(names);

            var paramCode = GetOperandGroupDefCode(param);
            
            var byte1 = GetHexInstCode(hexInst,0);
            var byte2 = GetHexInstCode(hexInst,1);
            
            var byte3_38_zip = GetHexInstCode(zipByte3_38, "Byte3Zip_38");
            var byte3_3A_zip = GetHexInstCode(zipByte3_3A, "Byte3Zip_3A");
            
            StringBuilder instsCode = new StringBuilder();
            // grpConv
            var t = from val in insts select val.ToString();
        }
        private static string GetHexInstCode(List<Tuple<byte, Tuple<int, byte>>> zipArray,string codeName)
        {
            //OpcodeData
            var str = (from val in zipArray select $"{{{val.Item2.Item1},{val.Item2.Item2},{val.Item1}}}").ToArray();
            StringBuilder sb = new StringBuilder($"extern ZipOpcodeData {codeName}[]={{" + Environment.NewLine);
            ConcatOpStr(str, sb);
            sb.AppendLine("};");
            return sb.ToString();
        }
        private static string GetHexInstCode(Tuple<int, byte>[][] hexInst,int index)
        {
            //OpcodeData
            var str = (from inst in hexInst[index]
                       select inst == null ? "{0,0}" : $"{{{inst.Item1},{inst.Item2}}}").ToArray();
            StringBuilder sb = new StringBuilder($"extern OpcodeData Byte{index + 1}[]={{" + Environment.NewLine);
            ConcatOpStr(str, sb);
            sb.AppendLine("};");
            return sb.ToString();
        }

        private static void ConcatOpStr(string[] str, StringBuilder sb)
        {
            for (int i = 0; i < str.Length; i += 8)
            {
                sb.Append(string.Join(",", str, i, (str.Length- i)>=8? 8: str.Length-i));
                sb.AppendLine(",");
            }
        }

        private List<Param>[] GetParams(List<string> pairs)
        {

            List<Param>[] param = new List<Param>[4];
            foreach (var item in GetOperandGroups().ToLookup((obj) => obj.Count))
            {
                var tmp = new List<Param>();
                foreach (var p in item)
                {
                    tmp.Add(new Param(p, pairs));
                }
                param[item.Key - 1] = tmp;
            }

            return param;
        }

        private List<NameIndex> CreateNames()
        {

            List<NameIndex> names = new List<NameIndex>();
            {
                int index = 0;

                foreach (var item in GetAllNames())
                {
                    names.Add(new NameIndex(item, index));
                    index += item.Count;
                }
            }

            return names;
        }

        private ILookup<string, OpcodeData> GetByteTables()
        {
            return opcodes.Value.ToLookup(
                (op) => $"Byte{op.Hex.Count}{(op.Hex.Count == 1 ? string.Empty : $"_{op.Hex[op.Hex.Count - 2]}") }"
                );
        }

        private static Inst CreateInst(List<NameIndex> names, List<Param>[] param, OpcodeData instInfo)
        {
            var paramID = instInfo.Operand == null ? 0 : param[instInfo.Operand.Count - 1].FindIndex((p) => instInfo.Operand.SequenceEqual(p.Params)) + 1;
            var tmpName = names.Find((val) => val.Name.SequenceEqual(instInfo.Name));
            Debug.Assert(paramID <= byte.MaxValue);
            var tmpInst = new Inst(
                instInfo,
                tmpName,
                (byte)paramID
                );
            return tmpInst;
        }

        public string GetOperandDefs(IEnumerable<string> pairs)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("extern RegOrOperandGroup Operands[]={");
            int index = 0;
            foreach (var item in pairs)
            {
                sb.AppendLine($"/*{index++}*/ {GetOperandDefStr(item)}");
            }
            sb.Append("};");
            return sb.ToString();
        }

        // 取所有上标(文档里的全用上了)
        public IEnumerable<string> GetAllSuperScripts()
        {
            var result = from item in opcodes.Value
                         where !string.IsNullOrEmpty(item.SuperScript)
                         orderby item.SuperScript
                         select item.SuperScript;
            result.Concat(
                from item in grpOpcode.Value
                where !string.IsNullOrEmpty(item.SuperScript)
                orderby item.SuperScript
                select item.SuperScript
                );

            return result.Distinct();
        }
        // 取所有前缀条件
        public IEnumerable<string> GetAllPfxs()
        {
            var result = from opcodeItem in opcodes.Value
                         where !string.IsNullOrEmpty(opcodeItem.Pfx)
                         orderby opcodeItem.Pfx
                         select opcodeItem.Pfx;
            result = result.Concat(
              from opcodeItem in grpOpcode.Value
              where !string.IsNullOrEmpty(opcodeItem.Pfx)
              orderby opcodeItem.Pfx
              select opcodeItem.Pfx
               );
            return result.Distinct();
        }

        // 取所有操作数
        public IEnumerable<string> GetOperandPairs()
        {
            var result = from opcodeItem in opcodes.Value
                         where opcodeItem.Operand != null
                         from item in opcodeItem.Operand
                         select item;

            result = result.Concat(
                from opcodeItem in grpOpcode.Value
                where opcodeItem.Operand != null
                from item in opcodeItem.Operand
                select item
                );
            return result.OrderBy((str) => str).Distinct();
        }

        // 取所有指令名称
        public IEnumerable<List<string>> GetAllNames()
        {
            var result = from opcodeItem in opcodes.Value
                         where opcodeItem.Name != null
                         select opcodeItem.Name;
            result = result.Concat(
               from opcodeItem in grpOpcode.Value
               where opcodeItem.Name != null
               select opcodeItem.Name);
            // 不排序，使同指令的多个名称可以靠在一起
            return result.OrderBy((item) => item.First()).Distinct(new DistinctStringList());
        }
        string GetNamesDefCode(List<NameIndex> names)
        {
            StringBuilder nameCode = new StringBuilder("extern LPCSTR InstructionNames[] = {" + Environment.NewLine);

            foreach (var nameArr in names)
            {
                if (nameArr.Name.Count > 1)
                {
                    var name = nameArr.Name.First();

                    nameCode.AppendLine($"/*{nameArr.Index,3}*/ \"{name}\", \t// Len:{nameArr.Name.Count} {(nameArr.Name[1].Length == 1 ? "Type:Size" : string.Empty)}");

                    if (nameArr.Name[1].Length == 1)
                    {
                        // 根据大小可变
                        for (int i = 1; i < nameArr.Name.Count; i++)
                        {
                            nameCode.AppendLine($"/*{nameArr.Index + i,3}*/ \"{name}{nameArr.Name[i]}\",");
                        }
                    }
                    else
                    {
                        // 普通多名指令
                        for (int i = 1; i < nameArr.Name.Count; i++)
                        {
                            nameCode.AppendLine($"/*{nameArr.Index + i,3}*/ \"{ nameArr.Name[i]}\",");
                        }
                    }
                }
                else
                {
                    // 单名指令
                    nameCode.AppendLine($"/*{nameArr.Index,3}*/ \"{nameArr.Name.First()}\", \t// Len:{nameArr.Name.Count}");
                }

            }
            nameCode.AppendLine("};");

            return nameCode.ToString();
        }
        class DistinctStringList : IEqualityComparer<List<string>>
        {
            public bool Equals(List<string> x, List<string> y)
            {
                return x.SequenceEqual(y);
            }

            public int GetHashCode(List<string> obj)
            {
                return 0;
            }
        }
        // 取所有操作数组合
        public IEnumerable<List<string>> GetOperandGroups()
        {
            var result = from opcodeItem in opcodes.Value
                         where opcodeItem.Operand != null
                         select opcodeItem.Operand;
            result = result.Concat(
                from opcodeItem in grpOpcode.Value
                where opcodeItem.Operand != null
                select opcodeItem.Operand
                );

            return result.Distinct(new DistinctStringList());
        }
        public string GetOperandGroupDefCode(List<Param>[] param)
        {
            StringBuilder sb = new StringBuilder();
            foreach (var item in param)
            {
                int index = 0;
                int count = item.First().Params.Count;
                sb.Append($"extern unsigned char OperandGroup{count}");
                sb.Append("[]");
                if (count > 1)
                {
                    sb.Append($"[{count}]");
                }
                
                
                sb.AppendLine(" ={ ");
                foreach (var val in item)
                {
                    if (count > 1)
                    {
                        sb.Append($"/*{index++}*/ {{");
                        foreach (var idx in val.PairIndexes)
                        {
                            sb.Append($"{idx},");
                        }
                        
                        sb.Length--;
                        sb.AppendLine($"}}, // {string.Join(",", val.Params)}");
                    }
                    else
                    {
                        int indexOf = val.PairIndexes.First();
                        Debug.Assert(indexOf != -1);
                        sb.AppendLine($"/*{index++}*/ {indexOf}, // {val.Params.First()}");
                    }
                }
                sb.AppendLine("};");
            }
            return sb.ToString();
        }


        static List<string> segs = new List<string>()
        {
            "CS",
            "DS",
            "ES",
            "FS",
            "GS",
            "SS",
        };
        static string GetOperandDefStr(string opPairStr)
        {
            Debug.Assert(!string.IsNullOrEmpty(opPairStr));
            // 段寄存器
            if (segs.Contains(opPairStr))
            {
                return $"{{SEG_{opPairStr},NULL}}, // {opPairStr}"; ;
            }
            if (opPairStr.Contains('/'))
            {
                // 特殊的多个参数类型
                return $"{{SPC_{opPairStr.Replace('/','_')},NULL}}, // {opPairStr}";
            }
            // 分开成枚举定义
            if (opPairStr.Length == 1)
            {
                return $"{{H_{opPairStr},NULL}}, // {opPairStr}";
            }
            else
            {
                if (char.IsUpper(opPairStr[0]) && char.IsLower(opPairStr[1]))
                {
                    // U L 操作数组合
                    return $"{{H_{opPairStr.First()},L_{opPairStr.Substring(1)}}}, // {opPairStr}";
                }
                else if (char.IsLower(opPairStr[0]) && char.IsUpper(opPairStr[1]))
                {
                    // L U 寄存器（可根据大小变）
                    return $"{{REG_{opPairStr.ToUpper()},CHANGE_REG}}, // {opPairStr}";
                }
                else
                {
                    // 段寄存器排除了，这里都是寄存器
                    return $"{{REG_{opPairStr},NULL}}, // {opPairStr}";
                }

            }
        }
    }
}
