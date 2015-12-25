using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WinUtilWapper.PeDecoderWapper;
namespace WinUtilNetTest
{
    public partial class ShowPropertiesTest : Form
    {
        PeImage pe;
        bool isLoad;
        public ShowPropertiesTest()
        {
            InitializeComponent();
            
        }

        private void ShowPropertiesTest_Load(object sender, EventArgs e)
        {
           
            pe = new PeImage();
            
            isLoad = pe.LoadPEImage(Process.GetCurrentProcess().MainModule.BaseAddress, true);
            Debug.WriteLine(isLoad);
            if (isLoad)
            {
                propertyGrid1.SelectedObject = pe;
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (isLoad)
            {
                propertyGrid1.SelectedObject = pe.DosHeader;
            }
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (isLoad)
            {
                propertyGrid1.SelectedObject = pe;
            }
        }
    }
}
