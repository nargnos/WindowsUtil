#pragma once
#include "ITreeNodeStyle.hpp"
// 以前编的C#转成C++,托管C++太JB烦了!
namespace PEView {
	using namespace System::Drawing::Drawing2D;

	ref class TreeNodeStyle_Blue :
		public ITreeNodeStyle
	{
	private:
		const int vSize = 4;
		Pen^ v;
		Pen^ vShadow;
		int shadowOffset = 1;
		LinearGradientBrush^ fade;
		SolidBrush^ hot;
		SolidBrush^ selected;
		SolidBrush^ selectedFocused;
		SolidBrush^ selectedFocusedHot;
		Pen^ selectedFocusedHotPen;
		TreeView^ treeView;
		Brush^ bg;
		int textOffset = 0;

		void FillBackground(Brush^ brush, DrawTreeNodeEventArgs^ e)
		{
			e->Graphics->FillRectangle(brush, e->Bounds.Left + 1, e->Bounds.Top + 1, e->Bounds.Width - 2, e->Bounds.Height - 2);
		}
		void DrawOutLine(Pen^ pen, DrawTreeNodeEventArgs^ e)
		{
			e->Graphics->DrawRectangle(pen, e->Bounds.Left + 1, e->Bounds.Top + 1, e->Bounds.Width - 3, e->Bounds.Height - 3);
		}

	public:
		TreeNodeStyle_Blue()
		{
			v = gcnew Pen(Color::FromArgb(100, 100, 100), vSize / 2);
			vShadow = gcnew Pen(Color::FromArgb(200, 200, 200, 200), vSize / 2);
			v->StartCap = System::Drawing::Drawing2D::LineCap::Triangle;
			v->EndCap = System::Drawing::Drawing2D::LineCap::Triangle;
			vShadow->StartCap = System::Drawing::Drawing2D::LineCap::Triangle;
			vShadow->EndCap = System::Drawing::Drawing2D::LineCap::Triangle;
			hot = gcnew SolidBrush(Color::FromArgb(229, 243, 255));
			selected = gcnew SolidBrush(Color::FromArgb(217, 217, 217));
			selectedFocused = gcnew SolidBrush(Color::FromArgb(205, 232, 255));
			selectedFocusedHot = gcnew SolidBrush(Color::FromArgb(204, 232, 255));
			selectedFocusedHotPen = gcnew Pen(Color::FromArgb(153, 209, 255));
		}

		virtual void  DrawCommon(DrawTreeNodeEventArgs^ e)
		{
			auto x = e->Node->Bounds.Left - treeView->ItemHeight / 2;
			auto y = e->Node->Bounds.Top + treeView->ItemHeight / 2;
			if (e->Node->Bounds.X == e->Node->Bounds.Y&& e->Node->Bounds.Width == e->Node->Bounds.Height)
			{
				return;
			}
			e->Graphics->DrawString(e->Node->Text, treeView->Font, SystemBrushes::ControlText, e->Node->Bounds.X + textOffset, e->Node->Bounds.Y );

			if (!e->Node->IsExpanded && e->Node->Nodes->Count > 0)
			{
				e->Graphics->DrawLines(vShadow,
					gcnew array<Point>{
					Point(x + shadowOffset, y - vSize + shadowOffset),
					Point(x + vSize + shadowOffset, y + shadowOffset),
					Point(x + shadowOffset, y + vSize + shadowOffset)
				});

				e->Graphics->DrawLines(v,
					gcnew array<Point>{
					Point(x, y - vSize),
					Point(x + vSize, y),
					Point(x, y + vSize)
				});
			}
			else if (e->Node->IsExpanded)
			{
				auto midOffset = vSize / 2; //居中偏移
				e->Graphics->DrawLines(vShadow,
					gcnew array<Point>{
					Point(vSize / 2 + x - vSize + shadowOffset, y + shadowOffset - midOffset),
					Point(vSize / 2 + x + shadowOffset, y + shadowOffset + midOffset),
					Point(vSize / 2 + x + vSize + shadowOffset, y + shadowOffset - midOffset)
				});

				e->Graphics->DrawLines(v,
					gcnew array<Point>{
					Point(vSize / 2 + x - vSize, y - midOffset),
					Point(vSize / 2 + x, y + midOffset),
					Point(vSize / 2 + x + vSize, y - midOffset)
				});
			}
		}

		virtual void DrawFocusedHot(DrawTreeNodeEventArgs^ e)
		{
			DrawHot(e);
		}
		virtual void DrawHot(DrawTreeNodeEventArgs^ e)
		{

			FillBackground(hot, e);
			FillBackground(fade, e);
		}
		virtual void DrawNone(DrawTreeNodeEventArgs^ e)
		{
			FillBackground(bg, e);
			FillBackground(fade, e);
		}

		virtual void DrawSelected(DrawTreeNodeEventArgs^ e)
		{
			FillBackground(selected, e);
			FillBackground(fade, e);
		}
		virtual void DrawSelectedFocused(DrawTreeNodeEventArgs^ e)
		{
			FillBackground(selectedFocused, e);
			FillBackground(fade, e);
		}
		virtual void DrawSelectedFocusedHot(DrawTreeNodeEventArgs^ e)
		{
			FillBackground(selectedFocusedHot, e);
			DrawOutLine(selectedFocusedHotPen, e);
			FillBackground(fade, e);
		}
		virtual void DrawSelectedHot(DrawTreeNodeEventArgs^ e)
		{
			DrawSelectedFocusedHot(e);
		}
		void RetsetFadeBrush()
		{
			System::Drawing::Rectangle brush(0, treeView->ItemHeight, treeView->Width, treeView->ItemHeight);
			fade = gcnew LinearGradientBrush(brush, Color::FromArgb(0, treeView->BackColor), treeView->BackColor, LinearGradientMode::Horizontal);
		}
		virtual void Set(TreeView^ treeView)
		{
			this->treeView = treeView;
			treeView->ItemHeight = 25;
			treeView->HotTracking = true;
			treeView->HideSelection = false;
			treeView->BackColor = SystemColors::Window;
			treeView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			treeView->FullRowSelect = true;
			treeView->ShowLines = false;
			treeView->DrawMode = TreeViewDrawMode::OwnerDrawAll;
			treeView->BorderStyle = BorderStyle::None;
			treeView->CheckBoxes = false;
			bg = gcnew SolidBrush(treeView->BackColor);
			textOffset = (int)(treeView->ItemHeight - treeView->Font->Size) / 2;
			RetsetFadeBrush();
			treeView->SizeChanged += gcnew System::EventHandler(this, &PEView::TreeNodeStyle_Blue::OnSizeChanged);

		}

		void OnSizeChanged(System::Object ^sender, System::EventArgs ^e)
		{
			RetsetFadeBrush();
		}

	
};

}

