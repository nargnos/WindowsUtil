#pragma once
#include "PeFile.h"
#include "PeDataCommon.h"
using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Linq::Expressions;
ref class IPeDataReader
{
public:
	virtual String^ GetCell(DataGridView^ sender,int col, int row) = 0;
	virtual int GetCount() = 0;
	virtual List<String^>^ GetCols() = 0;
};

template<typename T>
ref class PeDataReader :public IPeDataReader
{

protected:
	List<String^>^ cols;
	Func<T^, int, String^>^ colReader;
	List<T^>^ data;
	// 返回列读取函数和列名
	static Tuple< Func<T^, int, String^>^, List<String^>^>^ CreateGetCellFunction()
	{
		List<String^>^ colResult = gcnew List<String^>();
		array<Reflection::FieldInfo^>^ properties = (T::typeid)->GetFields();

		auto objParam = Expression::Parameter(T::typeid);
		auto fieldIndexParam = Expression::Parameter(int::typeid);
	
		List<SwitchCase^>^ cases = gcnew List<SwitchCase^>();
		
		for (int i = 0, col=0; i < properties->Length; i++)
		{
			auto var = properties[i];
			auto field = Expression::PropertyOrField(objParam, var->Name);
			auto attr = var->GetCustomAttributes(ColNameAttribute::typeid, true);
			if (attr != nullptr && attr->Length>0)
			{
				colResult->Add(((ColNameAttribute^)attr[0])->Name);
				cases->Add(Expression::SwitchCase(Expression::Convert(field,String::typeid), Expression::Constant(col)));
				col++;
			}
			
		}
		auto switchValue = Expression::Switch(fieldIndexParam,Expression::Constant(String::Empty), cases->ToArray());
		auto lambda = Expression::Lambda<Func<T^, int, String^>^>(switchValue->Reduce(), objParam, fieldIndexParam);
		return gcnew Tuple<Func<T^, int, String^>^, List<String^>^>(lambda->Compile(), colResult) ;
	}


public:
	PeDataReader(List<T^>^ data)
	{
		this->data = data;
		auto tmp = PeDataReader<T>::CreateGetCellFunction();
		colReader= tmp->Item1;
		cols = tmp->Item2;
	}

	String^ GetCell(DataGridView^ sender, int col, int row) override
	{
		if (data->Count<=row)
		{
			return String::Empty;
		}
		
		return colReader(data[row], col);
	}
	int GetCount() override
	{
		return data->Count;
	}
	List<String^>^ GetCols() override
	{
		return cols;
	}
};

// 使用第一行作为偏移量显示
ref class SectionDataReader:public PeDataReader<_SectionData>
{
public:
	SectionDataReader(List<_SectionData^>^ data):PeDataReader<_SectionData>(data)
	{
	}
	int GetCount() override
	{
		return data->Count+1;
	}
	String^ GetCell(DataGridView^ sender, int col, int row) override
	{
		if (row == 0)
		{
			if (sender->SelectedRows->Count>0)
			{
				auto selectedRow = sender->SelectedRows[0];
				
				if (selectedRow->Index>0 && selectedRow->Index-1 < data->Count)
				{
					return data[selectedRow->Index-1]->GetOffsetData(col);
				}
			}
		}
		else if (data->Count >= row)
		{
			auto i = colReader(data[row - 1], col);
			return i;
			
		}
		return String::Empty;
		
	}
};