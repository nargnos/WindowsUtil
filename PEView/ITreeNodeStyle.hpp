#pragma once
namespace PEView {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Collections::Generic;
	interface class  ITreeNodeStyle 
	{
	public:	
		void Set(TreeView^ treeView);
		void DrawCommon(DrawTreeNodeEventArgs^ e);
		void DrawNone(DrawTreeNodeEventArgs^ e);
		void DrawHot(DrawTreeNodeEventArgs^ e);
		void DrawSelected(DrawTreeNodeEventArgs^ e);
		void DrawSelectedFocused(DrawTreeNodeEventArgs^ e);
		void DrawSelectedFocusedHot(DrawTreeNodeEventArgs^ e);
		void DrawFocusedHot(DrawTreeNodeEventArgs^ e);
		void DrawSelectedHot(DrawTreeNodeEventArgs^ e);
	};
}