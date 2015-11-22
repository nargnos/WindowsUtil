#pragma once
#include <Windows.h>
using namespace System;

enum _MemberSize
{
	_Byte=1,
	_Word=2,
	_Dword=4,
	_Qword=8
};
extern String^ GetSizeString(int size);

[AttributeUsage(AttributeTargets::Field | AttributeTargets::Property, AllowMultiple = false)]
ref class ColNameAttribute :Attribute
{
private:
	String^ name;
public:
	ColNameAttribute(String^ name)
	{
		this->name = name;
	}
	property String^ Name
	{
		String^ get()
		{
			return name;
		}
	}
};
ref struct _PeData
{
	[ColNameAttribute("Field Name")]
	String^ Field;
	[ColNameAttribute("Offset")]
	String^ Offset;
	[ColNameAttribute("Size")]
	String^ Size;
	[ColNameAttribute("Value")]
	String^ Value;

	_PeData(String^ fieldName, int offset, int size, int value);

};

ref struct _SectionData
{
	[ColNameAttribute("Name\r\nBYTE[8]")]
	String^ Name;
	String^ NameOffset;

	[ColNameAttribute("VirtualSize\r\nDWORD")]
	String^ VirtualSize;
	String^ VirtualSizeOffset;

	[ColNameAttribute("VirtualAddress\r\nDWORD")]
	String^ VirtualAddr;
	String^ VirtualAddrOffset;

	[ColNameAttribute("SizeOfRawData\r\nDWORD")]
	String^ RawSize;
	String^ RawSizeOffset;

	[ColNameAttribute("PointerToRawData\r\nDWORD")]
	String^ RawAddress;
	String^ RawAddressOffset;

	[ColNameAttribute("PointerToRelocations\r\nDWORD")]
	String^ RelocAddress;
	String^ RelocAddressOffset;

	[ColNameAttribute("PointerToLinenumbers\r\nDWORD")]
	String^ LineNumbers;
	String^ LineNumbersOffset;

	[ColNameAttribute("NumberOfRelocations\r\nWORD")]
	String^ RelocationsNumber;
	String^ RelocationsNumberOffset;

	[ColNameAttribute("NumberOfLinenumbers\r\nWORD")]
	String^ LineNumbersNumber;
	String^ LineNumbersNumberOffset;

	[ColNameAttribute("Characteristics\r\nDWORD")]
	String^ Characteristics;
	String^ CharacteristicsOffset;

	String^ GetOffsetData(int col)
	{
		switch (col)
		{
		case 0:return NameOffset;
		case 1:return VirtualSizeOffset;
		case 2:return VirtualAddrOffset;
		case 3:return RawSizeOffset;
		case 4:return RawAddressOffset;
		case 5:return RelocAddressOffset;
		case 6:return LineNumbersOffset;
		case 7:return RelocationsNumberOffset;
		case 8:return LineNumbersNumberOffset;
		case 9:return CharacteristicsOffset;
		default:
			break;
		}
		return String::Empty;
	}
	_SectionData(PVOID base,PIMAGE_SECTION_HEADER section)
	{
		auto baseValue = (INT_PTR)base;
		Name = gcnew String((char*)section->Name, 0, 8);
		NameOffset = Convert::ToString((INT_PTR)section->Name - baseValue,16);

		VirtualSize = Convert::ToString((int)section->Misc.VirtualSize, 16);
		VirtualSizeOffset = Convert::ToString((INT_PTR)&section->Misc.VirtualSize - baseValue, 16);

		VirtualAddr = Convert::ToString((int)section->VirtualAddress, 16);
		VirtualAddrOffset = Convert::ToString((INT_PTR)&section->VirtualAddress - baseValue, 16);

		RawSize = Convert::ToString((int)section->SizeOfRawData, 16);
		RawSizeOffset = Convert::ToString((INT_PTR)&section->SizeOfRawData - baseValue, 16);

		RawAddress = Convert::ToString((int)section->PointerToRawData, 16);
		RawAddressOffset = Convert::ToString((INT_PTR)&section->PointerToRawData - baseValue, 16);

		RelocAddress = Convert::ToString((int)section->PointerToRelocations, 16);
		RelocAddressOffset = Convert::ToString((INT_PTR)&section->PointerToRelocations - baseValue, 16);

		LineNumbers = Convert::ToString((int)section->PointerToLinenumbers, 16);
		LineNumbersOffset = Convert::ToString((INT_PTR)&section->PointerToLinenumbers - baseValue, 16);

		RelocationsNumber = Convert::ToString((int)section->NumberOfRelocations, 16);
		RelocationsNumberOffset = Convert::ToString((INT_PTR)&section->NumberOfRelocations - baseValue, 16);

		LineNumbersNumber = Convert::ToString((int)section->NumberOfLinenumbers, 16);
		LineNumbersNumberOffset = Convert::ToString((INT_PTR)&section->NumberOfLinenumbers - baseValue, 16);

		Characteristics = Convert::ToString((int)section->Characteristics, 16);
		CharacteristicsOffset = Convert::ToString((INT_PTR)&section->Characteristics - baseValue, 16);


	}
};

ref struct _ExeInfo
{
	[ColNameAttribute("Property")]
	String^ Property;
	[ColNameAttribute("Value")]
	String^ Value;
	_ExeInfo(String^ property, String^ value);
};