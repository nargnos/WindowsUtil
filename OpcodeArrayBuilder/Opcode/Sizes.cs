using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpcodeArrayBuilder.Opcode
{
    [Flags]
    public enum Sizes
    {
        None = 0,
        B = 1,
        W = B << 1,
        D = W << 1,
        Q = D << 1
    }
}
