using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using OpcodeArrayBuilder.Opcode;
namespace OpcodeArrayBuilder
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void OpcodeBuilder()
        {
            Builder builder = new Builder();
            var superScripts = builder.GetAllSuperScripts();
            var pfxs = builder.GetAllPfxs();
            var operand = builder.GetOperandPairs();
            var names = builder.GetAllNames();
            var operandGroups = builder.GetOperandGroups();
            var operandsDefineCode = builder.GetOperandDefs();
            var operandsGrpDefineCode = builder.GetOperandGroupDefCode();
            var namesCode = builder.GetNamesDefCode();
        }
    }
}
