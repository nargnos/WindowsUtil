#pragma once
#include "resource.h"
#include <memory>
#include <list>
#include <msclr\marshal_cppstd.h>  
#include "TreeNodeStyle_Blue.h"
#include "TreeNodeDrawer.hpp"
#include "PeFile.h"
#include "InfoListControl.h"
#include "Plugin.h"
namespace PEView {
	//using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Collections::Generic;
	using namespace msclr::interop;



	/// <summary>
	/// PEView 摘要
	/// </summary>
	public ref class PEView : public System::Windows::Forms::Form
	{
	public:
		PEView(void);



	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~PEView()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::Windows::Forms::MenuStrip^  menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;


		System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
		System::Windows::Forms::OpenFileDialog^  openFileDialog;

		System::Windows::Forms::SplitContainer^  splitContainer1;

		System::Windows::Forms::TreeView^  treeMenu;
		System::Windows::Forms::ToolStripMenuItem^  closeToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  pluginToolStripMenuItem;
		PeFile^ peFile;

		TreeNodeDrawer^ draw;
		bool isDefaultMenuInit;
		bool isExMenuInit;
		Func<DataGridView^, int, int, String^>^ lastCellValueNeeded;
		Action<DataGridView^>^ lastSelectionChanged;
		Dictionary<TreeNode^, System::Action^>^ menuActions;
		Dictionary<TreeNode^, System::Action^>^ defaultMenuactions;
		Dictionary<TreeNode^, System::Action^>^ exMenuActions;

		System::Windows::Forms::TreeNode^  treeNode_DosHeader;
		System::Windows::Forms::TreeNode^  treeNode_FileHeader;
		System::Windows::Forms::TreeNode^  treeNode_DataDirectories;
		System::Windows::Forms::TreeNode^  treeNode_OptionalHeader;
		System::Windows::Forms::TreeNode^  treeNode_NtHeader;
		System::Windows::Forms::TreeNode^  treeNode_SectionHeader;
		System::Windows::Forms::TreeNode^  treeNode_Exe;
		String^ str_DosHeader = "Node_DosHeader";
		String^ str_FileHeader = "Node_FileHeader";
		String^ str_DataDirectories = "Node_DataDirectories";
		String^ str_OptionalHeader = "Node_OptionalHeader";
		String^ str_NtHeader = "Node_NtHeader";
		String^ str_SectionHeader = "Node_SectionHeader";
		String^ str_Exe = "Node_Exe";

		System::Windows::Forms::TreeNode^  treeNode_ExportDirectories;
		System::Windows::Forms::TreeNode^  treeNode_ImportDirectories;
		System::Windows::Forms::TreeNode^  treeNode_ResourceDirectory;
		System::Windows::Forms::TreeNode^  treeNode_RelocationDirectory;
		System::Windows::Forms::TreeNode^  treeNode_DebugDirectory;
		System::Windows::Forms::TreeNode^  treeNode_TLSDirectory;
		String^ str_ExportDirectories = L"ExportDirectories";
		String^ str_ImportDirectories = L"ImportDirectories";
		String^ str_ResourceDirectory = L"ResourceDirectory";
		String^ str_RelocationDirectory = L"RelocationDirectory";
		String^ str_DebugDirectory = L"DebugDirectory";
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;

			 String^ str_TLSDirectory = L"TLSDirectory";

		System::Void aboutToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e);
		System::Void openToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e);

		System::Void treeMenu_DrawNode(System::Object^  sender, System::Windows::Forms::DrawTreeNodeEventArgs^  e);
		System::Void treeMenu_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
		System::Void treeMenu_BeforeSelect(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e);
		System::Void closeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		void CloseFile();
		void InitUI();
		void InitExMenu();
		void AddExMenu(TreeNode^ node);
		void InitTreeView();
		void InitDefaultMenu();

		System::Void OnDosHeaderClick();
		System::Void OnFileHeaderClick();
		System::Void OnDataDirectoriesClick();
		System::Void OnOptionalHeaderClick();
		System::Void OnNtHeaderClick();
		System::Void OnSectionHeaderClick();
		System::Void OnSectionRowSelectionChanged(DataGridView^ sender);
		void AddInfoListControl(List<String^>^ cols, int rowCount, Func<DataGridView^, int, int, String^>^ getCell, Action<DataGridView^>^ selectionChanged);
		void AddInfoListControl(IPeDataReader^ reader);
		void AddInfoListControl(IPeDataReader ^ reader, Action<DataGridView^>^ selectionChanged);

		System::Void OnExeClick();

		System::Void PEView::ExportDirectoriesClick();
		System::Void PEView::ImportDirectoriesClick();
		System::Void PEView::ResourceDirectoryClick();
		System::Void PEView::RelocationDirectoryClick();
		System::Void PEView::DebugDirectoryClick();
		System::Void PEView::TLSDirectoryClick();
		void OnClosed();

		InfoListControl^ infoList;
		PluginMenuManager^ pluginMenu;

		void LoadPlugin();

		/// <summary>
   /// 必需的设计器变量。
   /// </summary>
		System::ComponentModel::Container ^components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pluginToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->treeMenu = (gcnew System::Windows::Forms::TreeView());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Window;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->optionToolStripMenuItem, this->pluginToolStripMenuItem, this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(3, 2, 0, 2);
			this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->menuStrip1->Size = System::Drawing::Size(1021, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openToolStripMenuItem,
					this->closeToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(69, 24);
			this->fileToolStripMenuItem->Text = L"文件(&F)";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openToolStripMenuItem->Size = System::Drawing::Size(206, 26);
			this->openToolStripMenuItem->Text = L"打开(&O)...";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &PEView::openToolStripMenuItem_Click);
			// 
			// closeToolStripMenuItem
			// 
			this->closeToolStripMenuItem->Name = L"closeToolStripMenuItem";
			this->closeToolStripMenuItem->Size = System::Drawing::Size(206, 26);
			this->closeToolStripMenuItem->Text = L"关闭(&C)";
			this->closeToolStripMenuItem->Click += gcnew System::EventHandler(this, &PEView::closeToolStripMenuItem_Click);
			// 
			// optionToolStripMenuItem
			// 
			this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
			this->optionToolStripMenuItem->Size = System::Drawing::Size(70, 24);
			this->optionToolStripMenuItem->Text = L"设置(&S)";
			// 
			// pluginToolStripMenuItem
			// 
			this->pluginToolStripMenuItem->Name = L"pluginToolStripMenuItem";
			this->pluginToolStripMenuItem->Size = System::Drawing::Size(70, 24);
			this->pluginToolStripMenuItem->Text = L"插件(&P)";
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"ALL|*.*";
			this->openFileDialog->ReadOnlyChecked = true;
			this->openFileDialog->ShowReadOnly = true;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = System::Drawing::Point(0, 28);
			this->splitContainer1->Margin = System::Windows::Forms::Padding(0, 4, 0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->treeMenu);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->AutoScroll = true;
			this->splitContainer1->Panel2->Padding = System::Windows::Forms::Padding(5);
			this->splitContainer1->Size = System::Drawing::Size(1021, 565);
			this->splitContainer1->SplitterDistance = 310;
			this->splitContainer1->SplitterWidth = 1;
			this->splitContainer1->TabIndex = 1;
			// 
			// treeMenu
			// 
			this->treeMenu->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->treeMenu->Dock = System::Windows::Forms::DockStyle::Fill;
			this->treeMenu->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->treeMenu->FullRowSelect = true;
			this->treeMenu->Location = System::Drawing::Point(0, 0);
			this->treeMenu->Margin = System::Windows::Forms::Padding(4);
			this->treeMenu->Name = L"treeMenu";
			this->treeMenu->Size = System::Drawing::Size(310, 565);
			this->treeMenu->TabIndex = 0;
			this->treeMenu->DrawNode += gcnew System::Windows::Forms::DrawTreeNodeEventHandler(this, &PEView::treeMenu_DrawNode);
			this->treeMenu->BeforeSelect += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &PEView::treeMenu_BeforeSelect);
			this->treeMenu->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &PEView::treeMenu_AfterSelect);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(73, 24);
			this->helpToolStripMenuItem->Text = L"帮助(&H)";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->aboutToolStripMenuItem->Text = L"关于(&A)...";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &PEView::aboutToolStripMenuItem_Click);
			// 
			// PEView
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(1021, 593);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"PEView";
			this->Text = L"PE View - 测试";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	};

}


