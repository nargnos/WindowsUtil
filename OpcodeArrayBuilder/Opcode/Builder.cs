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
    public static class StringBuilderEx
    {
        public static void AddStrItem(this StringBuilder sb, string signStr, string str)
        {
            sb.Append((string.IsNullOrEmpty(str) ? "NULL" : signStr + str) + ", ");
        }
    }
    public class Builder
    {
        Lazy<List<GroupOpcodeData>> grpOpcode = new Lazy<List<GroupOpcodeData>>(() => AnalyOpcodeStr<GroupOpcodeData>(".\\Opcode\\opcodeGrp");
        Lazy<List<OpcodeData>> opcodes = new Lazy<List<OpcodeData>>(() => AnalyOpcodeStr<OpcodeData>(".\\Opcode\\opcode");
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
            // $inst_prefix, type, grp, rex...并到hex表里
            // $inst_table, type,...并
            // $inst_esc,...并
            // $inst_grp,...

            // X $param_pair(byte), pairID, len
            // V $hex_inst(short), instID, len ...表的内容
            // X $inst_name, nameID, len  // 并到inst里

            // 缺rm1、rm2、sib、esc表

            // $pair
            var pairs = GetOperandPairs().ToList(); // 包含grp
            // 可以生成 $name $inst_name 
            List<NameIndex> names = CreateNames(); // 包含grp
            // 可以生成param 1234
            List<Param>[] param = GetParams(pairs); // 包含grp

            // $hex_inst - id,count
            Tuple<int, byte>[][] hexInst = CreateEmptyHexInst();

            List<Inst> insts = new List<Inst>(); // $inst 不包含grp

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
                    tmp[Convert.ToInt32(opcode.Key, 16)] = new Tuple<int, byte>(insts.Count/* + 1*/, (byte)opcode.Count());
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
            List<Tuple<byte, Tuple<int, byte>>> zipByte3_38, zipByte3_3A;
            CreateZipByteTable(hexInst, out zipByte3_38, out zipByte3_3A);

            var pairsCode = GetOperandDefs(pairs);
            var namesCode = GetNamesDefCode(names);

            var paramCode = GetOperandGroupDefCode(param);

            var byte1 = GetHexInstCode(hexInst, 0);
            var byte2 = GetHexInstCode(hexInst, 1);

            var byte3_38_zip = GetHexInstCode(zipByte3_38, "HexTable3Zip_38");
            var byte3_3A_zip = GetHexInstCode(zipByte3_3A, "HexTable3Zip_3A");

            var instDic = CreateEmptyInstDic();
            var hexInstCode = GetHexInstCode(insts, instDic);

            var instCode = GetInstCode(instDic);
            var pfxInstCode = GetPfxInstCode(instDic);
            var grpInstCode = GetGrpInstCode(instDic); // inst里描述的grp，非grp表里描述的指令


            StringBuilder result = new StringBuilder();
            result.AppendLine(pairsCode);
            result.AppendLine(namesCode);
            result.AppendLine(paramCode);
            result.AppendLine(byte1);
            result.AppendLine(byte2);
            result.AppendLine(byte3_38_zip);
            result.AppendLine(byte3_3A_zip);
            result.AppendLine(hexInstCode);
            result.AppendLine(instCode);
            result.AppendLine(pfxInstCode);
            result.AppendLine(grpInstCode);

            var file = Path.GetTempFileName();
            File.AppendAllText(file, result.ToString());
            Process.Start("notepad.exe", file).WaitForExit();
            File.Delete(file);
            // escTable escInst grpTable grpInst rmTable sibTable   缺表
        }

        private static Tuple<int, byte>[][] CreateEmptyHexInst()
        {
            Tuple<int, byte>[][] hexInst = new Tuple<int, byte>[4][];
            for (int i = 0; i < hexInst.Length; i++)
            {
                hexInst[i] = new Tuple<int, byte>[0x100];
            }

            return hexInst;
        }

        private static void CreateZipByteTable(Tuple<int, byte>[][] hexInst, out List<Tuple<byte, Tuple<int, byte>>> zipByte3_38, out List<Tuple<byte, Tuple<int, byte>>> zipByte3_3A)
        {
            zipByte3_38 = new List<Tuple<byte, Tuple<int, byte>>>();
            zipByte3_3A = new List<Tuple<byte, Tuple<int, byte>>>();
            for (int i = 0; i < hexInst[2].Length; i++)
            {
                var tmp38 = hexInst[2][i];
                var tmp3A = hexInst[3][i];
                if (tmp38 != null)
                {
                    zipByte3_38.Add(new Tuple<byte, Tuple<int, byte>>((byte)i, tmp38));
                }
                if (tmp3A != null)
                {
                    zipByte3_3A.Add(new Tuple<byte, Tuple<int, byte>>((byte)i, tmp3A));
                }

            }
        }

        private static string GetGrpInstCode(Dictionary<OpcodeType, List<Inst>> instDic)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("const GrpInstData GrpInst[]=" + Environment.NewLine + "{");
            var grp = instDic[OpcodeType.Grp];
            for (int i = 0; i < grp.Count; i++)
            {
                var item = grp[i];
                var tmpSb = new StringBuilder("{");
               
                tmpSb.AddStrItem("S_", item.SS);
                tmpSb.Append(item.ParamID + ", ");
                tmpSb.Append(item.ParamCount + ", ");
                tmpSb.Append(item.GrpName);
                tmpSb.Append("},");
                sb.AppendLine($"{tmpSb.ToString(),paddingSizeNoIndex}// {i}");
            }
            sb.AppendLine("};");

            return sb.ToString();
        }

        private static string GetPfxInstCode(Dictionary<OpcodeType, List<Inst>> instDic)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("const PrefixInstData PfxInst[]=" + Environment.NewLine + "{");
            var pfx = instDic[OpcodeType.Prefix];
            for (int i = 0; i < pfx.Count; i++)
            {
                var item = pfx[i];
                var tmpSb = new StringBuilder("{");
                tmpSb.AddStrItem("S_", item.SS);
                tmpSb.AddStrItem(string.Empty, item.PfxGrp);
                tmpSb.Append(item.NameID);
                tmpSb.Append("},");
                sb.AppendLine($"{tmpSb.ToString(),paddingSizeNoIndex}// {i}");
            }
            sb.AppendLine("};");
            return sb.ToString();
        }

        private static string GetInstCode(Dictionary<OpcodeType, List<Inst>> instDic)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("const InstData Inst[]=" + Environment.NewLine + "{");
            var inst = instDic[OpcodeType.Inst];
            for (int i = 0; i < inst.Count; i++)
            {
                var item = inst[i];
                var tmpSb = new StringBuilder("{");

                AppendProp(tmpSb, item);
                tmpSb.Append("},");
                sb.AppendLine($"{tmpSb.ToString(),paddingSizeNoIndex}// {i}");
            }
            sb.AppendLine("};");
            sb.AppendLine("const InstChangeData InstChange[]=" + Environment.NewLine + "{");
            inst = instDic[OpcodeType.Inst_Change];
            for (int i = 0; i < inst.Count; i++)
            {
                var item = inst[i];
                var tmpSb = new StringBuilder("{");
                AppendProp(tmpSb, item);
                tmpSb.Append(", ");
                var splitExt = item.SType.ToString().Split(new string[] { ",", " " }, StringSplitOptions.RemoveEmptyEntries);
                tmpSb.Append(string.Join(" | ", from val in splitExt select "Ext_" + val));
                tmpSb.Append("},");
                sb.AppendLine($"{tmpSb.ToString(),paddingSizeNoIndex}// {i}");
            }
            sb.AppendLine("};");

            var gg = sb.ToString();
            return gg;
        }

        private static void AppendProp(StringBuilder sb, Inst item)
        {
            var tmpPfx = item.Pfxcdt.Split('_');
            var pfxStr = string.Join(" | ", from val in tmpPfx select $"C_{val}");
            sb.Append((string.IsNullOrEmpty(item.Pfxcdt) ? "NULL" : pfxStr) + ", ");
            sb.AddStrItem("S_", item.SS);
            sb.Append(item.ParamID + ", ");
            sb.Append(item.ParamCount + ", ");
            sb.Append(item.NameCount + ", ");
            sb.Append(item.NameID);
        }

        private static Dictionary<OpcodeType, List<Inst>> CreateEmptyInstDic()
        {
            var instDic = new Dictionary<OpcodeType, List<Inst>>();
            foreach (OpcodeType item in Enum.GetValues(typeof(OpcodeType)))
            {
                instDic[item] = new List<Inst>();
            }

            return instDic;
        }

        // 另外会返回分组好的指令
        private static string GetHexInstCode(List<Inst> insts, Dictionary<OpcodeType, List<Inst>> instDic)
        {
            StringBuilder sb = new StringBuilder($"const Hex_Inst HexInsts[]={Environment.NewLine}{{{Environment.NewLine}");
            for (int i = 0; i < insts.Count; i++)
            {

                var item = insts[i];
                var tmpDic = instDic[item.Type];
                switch (item.Type)
                {
                    case OpcodeType.None:
                        throw new Exception();
                    case OpcodeType.Table:
                        sb.AppendLine($"{$"{{OT_{item.Type.ToString()}_{item.TableName}, 0}},",paddingSize}// {i}");
                        break;
                    case OpcodeType.Esc:
                        sb.AppendLine($"{$"{{OT_{item.Type.ToString()}, 0}},",paddingSize}// {i}");
                        break;
                    default:
                        sb.AppendLine($"{$"{{OT_{item.Type.ToString()}, {tmpDic.Count}}},",paddingSize}// {i}");
                        tmpDic.Add(item);
                        break;
                }


            }
            sb.AppendLine("};");
            return sb.ToString();
        }

        private static string GetHexInstCode(List<Tuple<byte, Tuple<int, byte>>> zipArray, string codeName)
        {
            //OpcodeData
            var str = (from val in zipArray select $"{{{val.Item2.Item1}, {val.Item2.Item2}, {val.Item1}}}").ToArray();
            StringBuilder sb = new StringBuilder($"const ZipOpcodeData {codeName}[]={Environment.NewLine}{{{Environment.NewLine}");
            ConcatOpStr(str, sb);
            sb.AppendLine("};");
            return sb.ToString();
        }
        private static string GetHexInstCode(Tuple<int, byte>[][] hexInst, int index)
        {
            //OpcodeData
            var str = (from inst in hexInst[index]
                       select inst == null ? "{0, 0}" : $"{{{inst.Item1}, {inst.Item2}}}").ToArray();
            StringBuilder sb = new StringBuilder($"const OpcodeData HexTable{index + 1}[]={Environment.NewLine}{{{Environment.NewLine}");
            ConcatOpStr(str, sb);
            sb.AppendLine("};");
            return sb.ToString();
        }

        private static void ConcatOpStr(string[] str, StringBuilder sb)
        {
            for (int i = 0; i < str.Length; i += 8)
            {
                sb.Append(string.Join(", ", str, i, (str.Length - i) >= 8 ? 8 : str.Length - i));
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
            // grp esc table 不用有名字
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
            sb.AppendLine($"const RegOrOperandGroup Operands[]={Environment.NewLine}{{");
            int index = 0;
            foreach (var item in pairs)
            {
                sb.AppendLine($"/*{index++,indexPaddingSize}*/ {GetOperandDefStr(item)}");
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
                         where opcodeItem.Name != null && HasInstName(opcodeItem)
                         select opcodeItem.Name;
            result = result.Concat(
               from opcodeItem in grpOpcode.Value
               where opcodeItem.Name != null && HasInstName(opcodeItem)
               select opcodeItem.Name);
            // 不排序，使同指令的多个名称可以靠在一起
            return result.OrderBy((item) => item.First()).Distinct(new DistinctStringList());
        }

        private static bool HasInstName(IOpcode opcodeItem)
        {
            dynamic tmpItem = null;
            if (opcodeItem is GroupOpcodeData)
            {
                tmpItem = (GroupOpcodeData)opcodeItem;
            }
            else if (opcodeItem is OpcodeData)
            {
                tmpItem = (OpcodeData)opcodeItem;
            }
            else
            {
                throw new Exception();
            }
            return (tmpItem.OpType == OpcodeType.Inst || tmpItem.OpType == OpcodeType.Inst_Change || tmpItem.OpType == OpcodeType.Prefix);
        }
        private const int paddingSize = -36;
        private const int paddingSizeNoIndex = -56;

        private const int indexPaddingSize = 3;

        string GetNamesDefCode(List<NameIndex> names)
        {
            StringBuilder nameCode = new StringBuilder($"const LPCSTR InstructionNames[] = {Environment.NewLine}{{{Environment.NewLine}");

            foreach (var nameArr in names)
            {
                if (nameArr.Name.Count > 1)
                {
                    var name = nameArr.Name.First().ToLower();

                    nameCode.AppendLine($"/*{nameArr.Index,indexPaddingSize}*/ {$"\"{name}\",",paddingSize}// Count: {nameArr.Name.Count}");

                    if (nameArr.Name[1].Length != 1)
                    {
                        // 普通多名指令
                        for (int i = 1; i < nameArr.Name.Count; i++)
                        {
                            nameCode.AppendLine($"/*{nameArr.Index + i,indexPaddingSize}*/ \"{ nameArr.Name[i].ToLower()}\",");
                        }
                    }
                }
                else
                {
                    // 单名指令
                    nameCode.AppendLine($"/*{nameArr.Index,3}*/ {$"\"{nameArr.Name.First().ToLower()}\",",paddingSize}// Count: {nameArr.Name.Count}");
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
                sb.Append($"const unsigned char OperandGroup{count}");
                sb.Append("[]");
                if (count > 1)
                {
                    sb.Append($"[{count}]");
                }


                sb.AppendLine($" ={Environment.NewLine}{{ ");
                foreach (var val in item)
                {
                    if (count > 1)
                    {
                        sb.Append($"/*{index++,indexPaddingSize}*/ ");
                        var tmpSb = new StringBuilder("{");  // 为了让生成的代码对齐所以要生成一个临时的字符串

                        foreach (var idx in val.PairIndexes)
                        {
                            tmpSb.Append($"{idx}, ");
                        }

                        tmpSb.Length--;
                        tmpSb.Append("},");
                        sb.AppendLine($"{tmpSb.ToString(),paddingSize}// {string.Join(", ", val.Params)}");
                    }
                    else
                    {
                        int indexOf = val.PairIndexes.First();
                        Debug.Assert(indexOf != -1);
                        sb.AppendLine($"/*{index++,indexPaddingSize}*/ {$"{indexOf},",paddingSize}// {val.Params.First()}");
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
                return $"{$"{{SEG_{opPairStr}, NULL}},",paddingSize}// {opPairStr}"; ;
            }
            if (opPairStr.Contains('/'))
            {
                // 特殊的多个参数类型
                return $"{$"{{SPC_{opPairStr.Replace('/', '_')}, NULL}},",paddingSize}// {opPairStr}";
            }
            // 分开成枚举定义
            if (opPairStr.Length == 1)
            {
                return $"{$"{{H_{opPairStr}, NULL}},",paddingSize}// {opPairStr}";
            }
            else
            {
                if (char.IsUpper(opPairStr[0]) && char.IsLower(opPairStr[1]))
                {
                    // U L 操作数组合
                    return $"{$"{{H_{opPairStr.First()}, L_{opPairStr.Substring(1)}}},",paddingSize}// {opPairStr}";
                }
                else if (char.IsLower(opPairStr[0]) && (char.IsUpper(opPairStr[1]) || char.IsDigit(opPairStr[1])))
                {
                    // L U 寄存器（可根据大小变）
                    return $"{$"{{REG_{opPairStr.ToUpper()}, CHANGE_REG}},",paddingSize}// {opPairStr}";
                }
                else
                {
                    // 段寄存器排除了，这里都是寄存器
                    return $"{$"{{REG_{opPairStr}, NULL}},",paddingSize}// {opPairStr}";
                }

            }
        }
    }
}
