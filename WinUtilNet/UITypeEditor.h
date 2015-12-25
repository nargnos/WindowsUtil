#pragma once
#include "FlagsEditorUI.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		using namespace System::Drawing::Design;
		using namespace System::Windows::Forms::Design;
		generic<typename T> where T:Enum
		public ref class FlagsEditor :public UITypeEditor
		{
		public:
			virtual Object ^ FlagsEditor::EditValue(System::ComponentModel::ITypeDescriptorContext ^ context, System::IServiceProvider ^ provider, Object ^ value) override
			{
				IWindowsFormsEditorService^ edSvc = dynamic_cast<IWindowsFormsEditorService^>(provider->GetService(IWindowsFormsEditorService::typeid));
				if (edSvc != nullptr)
				{
					FlagsEditorUI<T>^ ui = gcnew FlagsEditorUI<T>((T)value, edSvc);
					edSvc->DropDownControl(ui);

					if (ui->Result == DialogResult::OK)
					{
						value = ui->Value;
					}
				}
				return value;
			}
			virtual System::Drawing::Design::UITypeEditorEditStyle FlagsEditor::GetEditStyle(System::ComponentModel::ITypeDescriptorContext ^ context) override
			{
				return UITypeEditorEditStyle::DropDown;
			}
		};
	
	}
}