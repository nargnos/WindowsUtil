using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpcodeArrayBuilder.Opcode
{
    public class OpcodeData : IOpcode
    {
        public OpcodeData()
        {

        }
        public void Init(string val)
        {
            var tmpArr = val.Split('|');
            Debug.Assert(tmpArr.Length == 5);
            SetHex(tmpArr[0]);
            SuperScript = tmpArr[1];
            Pfx = tmpArr[2];
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
                var type = val.Trim('(', ')').Split('/');
                OpType = (OpcodeType)Enum.Parse(typeof(OpcodeType), type[0],true);
                Name.Add(val);
                switch (OpType)
                {
                    case OpcodeType.Prefix:
                        int hex = Convert.ToInt32(Hex.Last(), 16);
                        switch (hex)
                        {
                            case 0x26:
                            case 0x3e:
                            case 0x2e:
                            case 0x36:
                            case 0x65:
                            case 0x64:
                                PfxGrp = "PfxGrp_2";
                                break;
                            case 0xf0:
                            case 0xf2:
                            case 0xf3:
                                PfxGrp = "PfxGrp_1";
                                break;
                            case 0x66:
                                PfxGrp = "PfxGrp_3";
                                break;
                            case 0x67:
                                PfxGrp = "PfxGrp_4";
                                break;
                            case 0xc4:
                            case 0xc5:
                                PfxGrp = "PfxGrp_Vex";
                                break;
                            default:
                                PfxGrp = "PfxGrp_Rex";
                                break;
                        }
                        break;
                    case OpcodeType.Grp:
                        GrpName = type[1];
                        break;
                    case OpcodeType.Table:
                        TableName = type[1];
                        break;
                    default:
                        break;
                }

            }
            else
            {
                var nameArr = val.Split('_');

                if (nameArr.Length > 1)
                {
                    Debug.Assert(nameArr.Length == 2);

                    Name.Add(nameArr[0]);
                    var sizeStr = nameArr[1].Split('/');
                    SType = Sizes.None;
                    // 根据长度改变名
                    for (int i = 0; i < sizeStr.Length; i++)
                    {
                        SType |= (Sizes)Enum.Parse(typeof(Sizes), sizeStr[i].ToUpper());
                        Name.Add(sizeStr[i]);
                    }
                    OpType = OpcodeType.Inst_Change;
                }
                else
                {
                    // 同指令多名
                    Name.AddRange(nameArr[0].Split('/'));
                    OpType = OpcodeType.Inst;
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
        #region 指令类型
        public List<string> Hex { get; set; }
        public string SuperScript { get; set; }
        public string Pfx { get; set; }
        public Sizes SType { get; set; }
        public List<string> Name { get; set; }
        public List<string> Operand { get; set; }
        #endregion

        #region  前缀类型
        public string PfxGrp { get; set; }
        #endregion
        #region  组类型
        public string GrpName { get; set; }
        #endregion
        #region Table
        public string TableName { get; set; }
        #endregion
    }
}
