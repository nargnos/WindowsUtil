#pragma once

namespace PEView {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;

	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	
	/// <summary>
	/// InfoListControl 摘要
	/// </summary>
	public ref class InfoListControl : public System::Windows::Forms::UserControl
	{
	public:
		InfoListControl(void);

		property int RowCount 
		{
			int get()
			{
				return infoGridView->RowCount;
			}
			void set(int value)
			{
				infoGridView->RowCount = value;
			}
		};
		void AddCols(List<String^>^ cols);
		// 列,行
		event Func<DataGridView^, int,int, String^>^ CellValueNeeded;
		event Action<DataGridView^>^ SelectionChanged;
		void Clear()
		{
			
			infoGridView->RowCount = 0;
			infoGridView->ColumnCount = 0;
			infoGridView->Rows->Clear();
			infoGridView->Columns->Clear();
		}
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~InfoListControl()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  infoGridView;

	private:
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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->infoGridView = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->infoGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// infoGridView
			// 
			this->infoGridView->AllowUserToAddRows = false;
			this->infoGridView->AllowUserToDeleteRows = false;
			this->infoGridView->AllowUserToResizeRows = false;
			this->infoGridView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->infoGridView->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->infoGridView->BackgroundColor = System::Drawing::SystemColors::Window;
			this->infoGridView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->infoGridView->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
			this->infoGridView->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::GrayText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->infoGridView->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->infoGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(205)),
				static_cast<System::Int32>(static_cast<System::Byte>(232)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->infoGridView->DefaultCellStyle = dataGridViewCellStyle2;
			this->infoGridView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->infoGridView->EnableHeadersVisualStyles = false;
			this->infoGridView->Location = System::Drawing::Point(0, 0);
			this->infoGridView->MultiSelect = false;
			this->infoGridView->Name = L"infoGridView";
			this->infoGridView->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			this->infoGridView->RowHeadersVisible = false;
			this->infoGridView->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			this->infoGridView->RowsDefaultCellStyle = dataGridViewCellStyle3;
			this->infoGridView->RowTemplate->Height = 25;
			this->infoGridView->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->infoGridView->Size = System::Drawing::Size(549, 378);
			this->infoGridView->TabIndex = 0;
			this->infoGridView->VirtualMode = true;
			this->infoGridView->CellValueNeeded += gcnew System::Windows::Forms::DataGridViewCellValueEventHandler(this, &InfoListControl::infoGridView_CellValueNeeded);
			this->infoGridView->SelectionChanged += gcnew System::EventHandler(this, &InfoListControl::infoGridView_SelectionChanged);
			// 
			// InfoListControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->Controls->Add(this->infoGridView);
			this->Name = L"InfoListControl";
			this->Size = System::Drawing::Size(549, 378);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->infoGridView))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		

private: System::Void infoGridView_CellValueNeeded(System::Object^  sender, System::Windows::Forms::DataGridViewCellValueEventArgs^  e) 
{
	e->Value = CellValueNeeded((DataGridView^)sender, e->ColumnIndex,e->RowIndex);
}
System::Void infoGridView_SelectionChanged(System::Object^  sender, System::EventArgs^  e) 
{
	SelectionChanged((DataGridView^)sender);
}
};

}
