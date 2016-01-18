using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpcodeArrayBuilder.Opcode
{
    public struct NameIndex
    {
        public List<string> Name;
        public int Index;
        public NameIndex(List<string> name, int index)
        {
            Name = name;
            Index = index;
        }
    }
}
