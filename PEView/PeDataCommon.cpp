#include "stdafx.h"
#include "PeDataCommon.h"

String ^ GetSizeString(int size)
{
	switch ((_MemberSize)size)
	{
	case _Byte:return "BYTE";
	case _Word:return "WORD";
	case _Dword:return "DWORD";
	case _Qword:return "QWORD";
	default:
		break;
	}
	return String::Empty;
}

inline _ExeInfo::_ExeInfo(String ^ property, String ^ value) :Property(property), Value(value)
{
}

inline _PeData::_PeData(String ^ fieldName, int offset, int size, int value)
	: Field(fieldName), Offset(Convert::ToString(offset, 16)->ToUpper()), Size(GetSizeString(size)), Value(Convert::ToString(value, 16)->ToUpper())
{}
