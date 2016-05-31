using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.MemoryMappedFiles;
using System.IO;
using System.Diagnostics;

namespace PeExplorer
{
    public partial class Main : Form
    {
        PeFile pe;
        public Main()
        {
            InitializeComponent();
            HidePropertyGrid();
            pe = new PeFile();
            pe.Closed += HidePropertyGrid;
        }

        private void HidePropertyGrid()
        {
            Text = "Pe Explorer";
            toolStripStatusLabel_Path.Text = string.Empty;
            propertyGrid.SelectedObject = null;
            propertyGrid.Visible = false;

        }
        private void ShowPropertyGrid()
        {
            Text = toolStripStatusLabel_Path.Text = pe.FileName;
            propertyGrid.Visible = true;
            propertyGrid.SelectedObject = pe.PE;
        }
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                OpenFile(openFileDialog.FileName, openFileDialog.ReadOnlyChecked);
            }
        }
        private void OpenFile(string path, bool isReadOnly)
        {
            try
            {
                if (pe.Open(path, isReadOnly))
                {
                    ShowPropertyGrid();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.Message);
                pe.Close();
            }
        }
        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pe.Close();
        }

        private void toggleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (propertyGrid.SelectedGridItem != null)
            {
                ToggleAll(propertyGrid.SelectedGridItem, !propertyGrid.SelectedGridItem.Expanded);
            }

        }
        // 返回当前结点和深度
        private IEnumerable<Tuple< GridItem,int>> ForEachGridItem(GridItem gi,int depth=0)
        {
            if (gi.Expandable)
            {
                yield return new Tuple<GridItem, int>( gi,depth);
                if (gi.GridItems.Count > 0)
                {
                    depth++;
                    foreach (GridItem item in gi.GridItems)
                    {
                        foreach (var node in ForEachGridItem(item, depth))
                        {
                            yield return node; ;
                        }
                    }
                }
               
            }
        }
        private void ToggleAll(GridItem gi, bool isExpanded)
        {
            foreach (var item in ForEachGridItem(gi))
            {
                item.Item1.Expanded = isExpanded;
            }
        }
       
        private void onlyShowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string str = GetPath(toolStripStatusLabel_Path.Text);
            propertyGrid.SelectedObject = propertyGrid.SelectedGridItem.Value;
            toolStripStatusLabel_Path.Text = str;
        }

        private string GetPath(string oldPath)
        {
            Stack<string> path = new Stack<string>();

            var tmpGridItem = propertyGrid.SelectedGridItem;
            do
            {
                path.Push(tmpGridItem.Label);
                tmpGridItem = tmpGridItem.Parent;
            } while (tmpGridItem.Parent != null);

            StringBuilder sb = new StringBuilder(oldPath);
           
            foreach (var item in path)
            {
                sb.AppendFormat("->{0}", item);
            }

            return sb.ToString();
        }

       
        private void contextMenuStrip_Prop_Opening(object sender, CancelEventArgs e)
        {
            toggleToolStripMenuItem.Enabled =
            onlyShowToolStripMenuItem.Enabled = pe.IsOpen && (propertyGrid.SelectedGridItem != null) && propertyGrid.SelectedGridItem.Expandable;
            backToolStripMenuItem.Enabled = IsOnlyShow();
        }
        private bool IsOnlyShow()
        {
            return propertyGrid.SelectedObject != pe.PE;
        }
        private void backToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ShowPropertyGrid();
        }

        private void fileToolStripMenuItem_DropDownOpening(object sender, EventArgs e)
        {
            saveAsToolStripMenuItem.Enabled = saveToolStripMenuItem.Enabled = closeToolStripMenuItem.Enabled = pe.IsOpen;
        }

        private void Main_DragDrop(object sender, DragEventArgs e)
        {

            var files = e.Data.GetData(DataFormats.FileDrop) as string[];
            if (files != null && files.Length > 0)
            {
                OpenFile(files[0], true);
            }
        }

        private void Main_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Link;
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // 记录一些更新日志，编完删掉
            var textBox = new TextBox();
            textBox.Dock = DockStyle.Fill;
            textBox.ReadOnly = true;
            textBox.Multiline = true;
            textBox.BorderStyle = BorderStyle.None;
            textBox.ScrollBars = ScrollBars.Vertical;
            textBox.BackColor = this.BackColor;
            textBox.Text =
@"!未完成
读文件的部分还差一半没写
写文件的等读文件写完，补了类库之后再写
    先提供直接写值的功能（不保证修改后程序能运行
    之后再写修改文件的函数
显示exe其它信息的待补

// 这是PE解析类库的使用例子，有空慢慢补，最近封装成C#能用的类库放到C#下面，所以原先c++cli那边的代码就不写了

// 进度表
// TODO:需要做跟CFF类似的功能，已写但未完成用[=]，已完成用[X]，未写用[ ]
// [=] 解析（枚举值解析需要显示提示,Meaning列需要多做一些处理），解析方面有些不常用的结构未写代码
// 	[=] pe info - 缺identifier，等这个模块写好再补上
// 	[X] Dos Header
// 	[X] Dos Stub
// 	[X] Nt Header
// 	[X] File Header
// 	[X] Optional Header
// 	[X] Data Directories
// 	[=] Section Headers - 缺16进制编辑界面
// 	[X] Export Directory
// 	[X] Import Directory
// 	[=] Resource Directory
// 	[ ] ...
// [ ] 编辑(包括pe结构和资源、添加结构、移动代码并重定位等) - 有空再写
// [=] Address Converter - 代码已有，无界面
// [ ] Dependency Walker - 可通过已写代码修改而来，无界面
// [ ] Hex Editer
// [ ] Identifier
// [ ] Import Adder
// [ ] Quick Disassembler - 写了一点有空再写（需要写的太多了）
// [ ] Rebuilder
// [ ] Resource Editor
// [X] 支持插件(自有插件+peid插件,可能因为是托管程序,peid插件不是完全兼容,自有插件等做完再补充，原先编好的代码没迁移过来，打算重新弄）

// TODO:需要做跟PEID类似的功能（上面的补充）
// [ ] CaveFinder
// [ ] Entropy
// [ ] 各种scan

// lordpe功能太多，等做完上面那些再实现类似功能（估计能载入它的插件应该不需要扩展了
// 后面要做的是载入解析运行中的程序（现在就能直接做...不过这个功能好像没用）
";
            textBox.Select(textBox.Text.Length, 0);

            var dlg = new Form();
            dlg.Size = this.Size;
            dlg.Padding = new Padding(5);
            dlg.BackColor = this.BackColor;
            dlg.FormBorderStyle = FormBorderStyle.None;
            dlg.ControlBox = false;
            dlg.StartPosition = FormStartPosition.CenterParent;
            textBox.Click += (senderx, ex) => { dlg.Close(); };
            dlg.Controls.Add(textBox);
            dlg.ShowInTaskbar = false;
            dlg.ShowDialog(this);
        }

        private void copyPathToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(propertyGrid.SelectedGridItem != null ?GetPath(toolStripStatusLabel_Path.Text):string.Empty);
        }

        private void captionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(propertyGrid.SelectedGridItem != null ? propertyGrid.SelectedGridItem.Label : string.Empty);
        }

        private void treeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            StringBuilder sb = new StringBuilder();
            if (propertyGrid.SelectedGridItem != null)
            {
                foreach (var item in ForEachGridItem(propertyGrid.SelectedGridItem))
                {
                    var tmpPaddingLen = item.Item2 * 2;
                    sb.Append(item.Item2==0?"":" ".PadLeft(tmpPaddingLen, ' '));
                    sb.AppendFormat("{0,-"+(32- tmpPaddingLen) +"}\t{1}" + Environment.NewLine, 
                        item.Item1.Label, 
                        item.Item1.PropertyDescriptor.Converter.ConvertToString(item.Item1.Value)
                        );
                }
            }
            Clipboard.SetText(sb.ToString());
        }

        
    }
}
