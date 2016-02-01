using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpcodeArrayBuilder.Opcode
{
    public struct Inst
    {
        public OpcodeType Type { get; set; }
        public string Pfxcdt { get; set; }

        public string SS { get; set; }
        public int NameID { get; set; }
        public int NameCount { get; set; }

        public byte ParamID { get; set; }
        public byte ParamCount { get; set; }


        public Sizes SType { get; set; }

        //  前缀类型
        public string PfxGrp { get; set; }
        
        //  组类型
        public string GrpName { get; set; }

        // 表名
        public string TableName { get; set; }
        public Inst(OpcodeData op, NameIndex name, byte paramID)
        {

            Type = op.OpType;
            NameID = name.Index;
            NameCount = name.Name?.Count??0;
            ParamCount = (byte)(op.Operand == null ? 0 : op.Operand.Count);
            ParamID = paramID;

            SS = op.SuperScript;

            Pfxcdt = op.Pfx;
            SType = op.SType;
            PfxGrp = op.PfxGrp;
            GrpName = op.GrpName;
            TableName = op.TableName;
        }
        public override string ToString()
        {
            return $"{Type}, {Pfxcdt}, {SS}, {NameID}, {NameCount}, {ParamID}, {ParamCount}, {SType}, {PfxGrp}, {GrpName},";
        }
    }
}
