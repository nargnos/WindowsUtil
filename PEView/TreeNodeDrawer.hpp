#pragma once
#include "ITreeNodeStyle.hpp"
namespace PEView {
	ref class TreeNodeDrawer
	{
ITreeNodeStyle ^style;
TreeView ^treeView;
	public:

		TreeNodeDrawer(TreeView^ treeView, ITreeNodeStyle^ style)
		{
			this->style = style;
			this->treeView = treeView;
			style->Set(treeView);
		}

		 void Draw(DrawTreeNodeEventArgs^ e)
		{
			switch (e->State)
			{
			case (TreeNodeStates)0:
				style->DrawNone(e);
				break;
			case TreeNodeStates::Hot:
				style->DrawHot(e);
				break;
			case TreeNodeStates::Selected:
				style->DrawSelected(e);
				break;
			case TreeNodeStates::Selected | TreeNodeStates::Focused:
				style->DrawSelectedFocused(e);
				break;
			case TreeNodeStates::Selected | TreeNodeStates::Focused | TreeNodeStates::Hot:
				style->DrawSelectedFocusedHot(e);
				break;
			case  TreeNodeStates::Focused | TreeNodeStates::Hot:
				style->DrawFocusedHot(e);
				break;
			case TreeNodeStates::Selected | TreeNodeStates::Hot:
				style->DrawSelectedHot(e);
				break;
			default:
				//
				break;
			}
			style->DrawCommon(e);
		}
	};

}