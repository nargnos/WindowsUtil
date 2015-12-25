using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Diagnostics;

using System.Windows.Forms;

namespace WinUtilNetTest
{
    [TestClass]
    public class UnitTest1
    {
        
        [TestMethod]
        [STAThread]
        public void TestMethod1()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            var win = new ShowPropertiesTest();
            win.Visible = true;
            Application.Run(win);
            
        }
    }
}
