using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpcodeArrayBuilder.Opcode
{
    public class GroupOpcodeData : IOpcode
    {
        public OpcodeType OpType { get; set; }
        public string GrpName { get; set; }

        public string SuperScript { get; set; }
        public string Pfx { get; set; }
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
            Pfx = arr[index++];

            RM76 = arr[index++];
            RM543 = arr[index++];
            RM210 = arr[index++];
            var name = arr[index++];
            if (!string.IsNullOrEmpty(name))
            {
                Name = new List<string>();
                Name.AddRange(name.Split('/'));
            }
            OpType = OpcodeType.Inst;
            var operand = arr[index++];
            if (!string.IsNullOrEmpty(operand))
            {
                Operand = new List<string>();
                Operand.AddRange(operand.Split(','));
            }
        }
    }

}
