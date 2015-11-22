#include "stdafx.h"
#include "InfoListControl.h"
namespace PEView {

	InfoListControl::InfoListControl(void)
	{
		InitializeComponent();
		this->Dock = DockStyle::Fill;
	}

	void InfoListControl::AddCols(List<String^>^ cols)
	{
		assert(cols != nullptr);
		for each (String^ item in cols)
		{
			infoGridView->Columns->Add(item, item);
		}
		
		infoGridView->ColumnCount = cols->Count;
		infoGridView->AutoResizeColumns(DataGridViewAutoSizeColumnsMode::AllCells);
	}

	void InfoListControl::Clear()
	{
		infoGridView->RowCount = 0;
		infoGridView->ColumnCount = 0;
		infoGridView->Rows->Clear();
		infoGridView->Columns->Clear();
	}

	System::Void InfoListControl::infoGridView_CellValueNeeded(System::Object ^ sender, System::Windows::Forms::DataGridViewCellValueEventArgs ^ e)
	{
		e->Value = CellValueNeeded((DataGridView^)sender, e->ColumnIndex, e->RowIndex);
	}

	System::Void InfoListControl::infoGridView_SelectionChanged(System::Object ^ sender, System::EventArgs ^ e)
	{
		SelectionChanged((DataGridView^)sender);
	}

}