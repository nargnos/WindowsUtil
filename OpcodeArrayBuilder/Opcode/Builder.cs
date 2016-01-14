using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpcodeArrayBuilder.Opcode
{
    public enum OpcodeType
    {
        Inst1, // 普通指令
        Inst2, // 根据长度修改指令名的指令
        Prefix,
        Grp,
        Table,
        Esc

    }
    public interface IOpcode
    {
        void Init(string val);
    }
    public class Opcode : IOpcode
    {
        public Opcode()
        {

        }
        public void Init(string val)
        {
            var tmpArr = val.Split('|');
            Debug.Assert(tmpArr.Length == 5);
            SetHex(tmpArr[0]);
            SetSuperScript(tmpArr[1]);
            SetPfx(tmpArr[2]);
            SetName(tmpArr[3]);
            SetOperand(tmpArr[4]);
        }
        private void SetHex(string val)
        {
            if (string.IsNullOrEmpty(val))
            {
                return;
            }
            Hex = new List<string>();

            for (int i = 0; i < val.Length; i += 2)
            {
                Hex.Add(val.Substring(i, 2));
            }
        }
        private void SetSuperScript(string val)
        {
            if (string.IsNullOrEmpty(val))
            {
                return;
            }
            SuperScript = new List<string>();
            var ssArr = val.Split('&');
            SuperScript.AddRange(ssArr);

        }
        private void SetPfx(string val)
        {
            if (string.IsNullOrEmpty(val))
            {
                return;
            }
            Pfx = new List<string>();
            var pfxArr = val.Split('&');
            Pfx.AddRange(pfxArr);
        }
        private void SetName(string val)
        {
            if (string.IsNullOrEmpty(val))
            {
                return;
            }
            Name = new List<string>();
            val = val.Trim();
            if (val.StartsWith("("))
            {
                var type = val.Trim('(', ')');
                OpType = (OpcodeType)Enum.Parse(typeof(OpcodeType), type.Split('/')[0]);
                Name.Add(val);
            }
            else
            {
                var nameArr = val.Split('_');

                if (nameArr.Length > 1)
                {
                    Debug.Assert(nameArr.Length == 2);

                    Name.Add(nameArr[0]);
                    var sizeStr = nameArr[1].Split('/');
                    // 根据长度改变名
                    for (int i = 0; i < sizeStr.Length; i++)
                    {
                        Name.Add(sizeStr[i]);
                    }
                    OpType = OpcodeType.Inst2;
                }
                else
                {
                    // 同指令多名
                    Name.AddRange(nameArr[0].Split('/'));
                    OpType = OpcodeType.Inst1;
                }


            }


        }
        private void SetOperand(string val)
        {
            if (string.IsNullOrEmpty(val))
            {
                return;
            }
            Operand = new List<string>();

            var opArr = val.Split(',');
            foreach (var item in opArr)
            {
                Operand.Add(item);
            }
        }
        public OpcodeType OpType { get; set; }
        public List<string> Hex { get; set; }
        public List<string> SuperScript { get; set; }
        public List<string> Pfx { get; set; }
        public List<string> Name { get; set; }
        public List<string> Operand { get; set; }
    }
    public class GroupOpcode : IOpcode
    {
        public OpcodeType OpType { get; set; }
        public string GrpName { get; set; }

        public string SuperScript { get; set; }
        public List<string> Pfx { get; set; }
        public string RM76 { get; set; }
        public string RM543 { get; set; }
        public string RM210 { get; set; }
        public List<string> Name { get; set; }
        public List<string> Operand { get; set; }

        public void Init(string val)
        {
            var arr = val.Split('|');
            Debug.Assert(arr.Length == 8);
            int index = 0;
            GrpName = arr[index++];
            SuperScript = arr[index++];
            var pfx = arr[index++];
            if (!string.IsNullOrEmpty(pfx))
            {
                Pfx = new List<string>();
                Pfx.AddRange(pfx.Split('&'));
            }
            RM76 = arr[index++];
            RM543 = arr[index++];
            RM210 = arr[index++];
            var name = arr[index++];
            if (!string.IsNullOrEmpty(name))
            {
                Name = new List<string>();
                Name.AddRange(name.Split('/'));
            }
            OpType = OpcodeType.Inst1;
            var operand = arr[index++];
            if (!string.IsNullOrEmpty(operand))
            {
                Operand = new List<string>();
                Operand.AddRange(operand.Split(','));
            }
        }
    }
    public class Builder
    {
        Lazy<List<GroupOpcode>> grpOpcode = new Lazy<List<GroupOpcode>>(() => AnalyOpcodeStr<GroupOpcode>(".\\Opcode\\opcodeGrp"));
        Lazy<List<Opcode>> opcodes = new Lazy<List<Opcode>>(() => AnalyOpcodeStr<Opcode>(".\\Opcode\\opcode"));

        public Builder()
        {
        }
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

        // 取所有上标(文档里的全用上了),组就不选了
        public IEnumerable<string> GetAllSuperScripts()
        {
            var result = from item in opcodes.Value
                         where item.SuperScript != null
                         from tmpSuperScript in item.SuperScript
                         orderby tmpSuperScript
                         select tmpSuperScript;


            return result.Distinct();
        }
        // 取所有前缀条件(只有3个66、F2、F3),组就不选了
        public IEnumerable<string> GetAllPfxs()
        {
            var result = from opcodeItem in opcodes.Value
                         where opcodeItem.Pfx != null
                         from item in opcodeItem.Pfx
                         orderby item
                         select item;

            return result.Distinct();
        }

        // 取所有操作数
        public IEnumerable<string> GetOperandPairs()
        {
            var result = from opcodeItem in opcodes.Value
                         where opcodeItem.Operand != null
                         from item in opcodeItem.Operand
                         from grp in item.Split('/')
                         select grp;

            result.Concat(
                from opcodeItem in grpOpcode.Value
                where opcodeItem.Operand != null
                from item in opcodeItem.Operand
                from grp in item.Split('/')
                select grp
                );
            return result.OrderBy((str) => str).Distinct();
        }


        public string GetOperandDefs()
        {
            var pairs = GetOperandPairs();
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("RegOrOperandGroup Operands[]={");
            int index = 0;
            foreach (var item in pairs)
            {
                sb.AppendLine($"/*{index++}*/ {GetOperandDefStr(item)}");
            }
            sb.Append("};");
            return sb.ToString();
        }

        // 取所有指令名称
        public IEnumerable<List<string>> GetAllNames()
        {
            var result = from opcodeItem in opcodes.Value
                         where opcodeItem.Name != null
                         select opcodeItem.Name;
            result.Concat(
               from opcodeItem in grpOpcode.Value
               where opcodeItem.Name != null
               select opcodeItem.Name);
            // 不排序，使同指令的多个名称可以靠在一起
            return result.OrderBy((item) => item.First()).Distinct(new DistinctStringList());
        }
        public string GetNamesDefCode()
        {
            StringBuilder names = new StringBuilder("extern PCSTR InstructionNames[] = {"+Environment.NewLine +"NULL," + Environment.NewLine);
            StringBuilder nameEnums = new StringBuilder("enum InstructionNameIndexs{" + Environment.NewLine + "Name_null," + Environment.NewLine);
            int index = 1;
            foreach (var nameArr in GetAllNames())
            {
                if (nameArr.Count > 1)
                {
                    var name = nameArr.First();
                    
                    nameEnums.AppendFormat("Name_{0} = {1}, \t// Len:{2} {3}" + Environment.NewLine,
                        nameArr.First(),index,nameArr.Count, nameArr[1].Length == 1 ? "Type:Size" : string.Empty);
                    
                    names.AppendFormat("/*{0,3}*/ \"{1}\", \t// Len:{2} {3}" + Environment.NewLine,
                        index++,name,nameArr.Count, nameArr[1].Length == 1?"Type:Size":string.Empty);

                    if (nameArr[1].Length == 1)
                    {
                        // 根据大小可变
                        for (int i = 1; i < nameArr.Count; i++)
                        {
                            names.AppendFormat("/*{0,3}*/ \"{1}{2}\","+Environment.NewLine,index++,name,nameArr[i]);
                        }
                    }
                    else
                    {
                        // 普通多名指令
                        for (int i = 1; i < nameArr.Count; i++)
                        {
                            names.AppendFormat("/*{0,3}*/ \"{1}\"," + Environment.NewLine, index++,nameArr[i]);
                        }
                    }
                }
                else
                {
                    // 单名指令
                    nameEnums.AppendLine($"Name_{nameArr.First().Trim('(',')').Replace('/','_').Replace('.','_').Replace('+','_')} = {index},");
                    names.AppendFormat("/*{0,3}*/ \"{1}\", \t// Len:{2}" + Environment.NewLine, index++,nameArr.First(),nameArr.Count);
                }

            }
            names.AppendLine("};");
            nameEnums.AppendLine("};");
            
            return names.ToString() + nameEnums.ToString();
        }
        class DistinctStringList : IEqualityComparer<List<string>>
        {
            public bool Equals(List<string> x, List<string> y)
            {
                if (x == y)
                {
                    return true;
                }
                if (x != null && y != null && x.Count == y.Count)
                {
                    for (int i = 0; i < x.Count; i++)
                    {
                        if (x[i] != y[i])
                        {
                            return false;
                        }
                    }
                    return true;
                }
                return false;
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
            result.Concat(
                from opcodeItem in grpOpcode.Value
                where opcodeItem.Operand != null
                select opcodeItem.Operand
                );
            var klk = result.Distinct(new DistinctStringList()).ToList();
            return result.Distinct(new DistinctStringList());
        }
        public string GetOperandGroupDefCode()
        {
            var opGrps = GetOperandGroups().ToLookup((obj) => obj.Count);
            var operandList = GetOperandPairs().ToList();
            StringBuilder sb = new StringBuilder();
            foreach (var item in opGrps)
            {
                int index = 0;
                sb.Append($"extern unsigned char OperandGroup{item.Key}[]");
                int count = item.First().Count;
                if (count > 1)
                {
                    sb.Append($"[{count}]");
                }
                sb.AppendLine(" ={ ");
                foreach (var val in item)
                {
                    if (val.Count > 1)
                    {
                        sb.Append($"/*{index++}*/ {{");
                        val.ForEach((str) =>
                        {
                            int indexOf = operandList.IndexOf(str);
                            Debug.Assert(indexOf != -1);
                            sb.Append($"{indexOf},");
                        });
                        sb.Length--;
                        sb.AppendLine($"}}, // {string.Join(",", val)}");
                    }
                    else
                    {
                        int indexOf = operandList.IndexOf(val[0]);
                        Debug.Assert(indexOf != -1);
                        sb.AppendLine($"/*{index++}*/ {indexOf}, // {val[0]}");
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
