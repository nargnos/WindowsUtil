using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpcodeArrayBuilder.Opcode
{
    public enum OpcodeType
    {
        Inst, // 普通指令
        Inst_Change, // 根据长度修改指令名的指令
        Prefix,
        Grp,
        Table,
        Esc
    }
}
