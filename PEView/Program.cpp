// PEView.cpp: 主项目文件。

#include "stdafx.h"
#include "PEView.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew PEView::PEView());
}
