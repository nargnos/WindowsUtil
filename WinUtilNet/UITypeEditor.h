#pragma once
#include "FlagsEditorUI.h"
namespace NAMESPACE {

	using namespace System::Drawing::Design;
	using namespace System::Windows::Forms::Design;
	generic<typename T> where T:Enum
		public ref class FlagsEditor :public UITypeEditor
	{
		IWindowsFormsEditorService^ edSvc;
		FlagsEditorUI<T>^ ui;
	public:
		virtual Object ^ FlagsEditor::EditValue(System::ComponentModel::ITypeDescriptorContext ^ context, System::IServiceProvider ^ provider, Object ^ value) override
		{
			if (edSvc == nullptr)
			{
				edSvc = dynamic_cast<IWindowsFormsEditorService^>(provider->GetService(IWindowsFormsEditorService::typeid));
			}

			if (ui == nullptr)
			{
				ui = gcnew FlagsEditorUI<T>((T)value, edSvc);
			}
			else
			{
				ui->SetCheckBoxes((T)value);
			}
			edSvc->DropDownControl(ui);

			if (ui->Result == DialogResult::OK)
			{
				value = ui->Value;
			}

			return value;
		}
		virtual System::Drawing::Design::UITypeEditorEditStyle FlagsEditor::GetEditStyle(System::ComponentModel::ITypeDescriptorContext ^ context) override
		{
			return UITypeEditorEditStyle::DropDown;
		}
	};


}