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
		for each (String^ item in cols)
		{
			infoGridView->Columns->Add(item, item);
		}
		
		infoGridView->ColumnCount = cols->Count;
		infoGridView->AutoResizeColumns(DataGridViewAutoSizeColumnsMode::AllCells);
	}

}