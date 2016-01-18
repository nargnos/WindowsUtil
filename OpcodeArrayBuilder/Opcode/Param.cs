using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpcodeArrayBuilder.Opcode
{
    public struct Param
    {
        public List<string> Params;
        public IEnumerable<int> PairIndexes;
        public Param(List<string> param, List<string> pairs)
        {
            Params = param;
            PairIndexes = new List<int>();
            PairIndexes = from item in Params select pairs.IndexOf(item);
        }
    }
}
