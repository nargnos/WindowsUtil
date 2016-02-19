#include "AsmStorage.h"


namespace Disassembler
{
	AsmStorage::AsmStorage()
	{
		isX32 = false;
	}
	void AsmStorage::SetX32(bool is32)
	{
		isX32 = is32;
	}
	bool AsmStorage::IsX32() const
	{
		return isX32;
	}
	OperandGroupStorage * AsmStorage::GetOperandGroupStorage() { return &operandGrpStorage; }
	OpcodeDataStorage * AsmStorage::GetOpcodeDataStorage() { return &opcodeDataStorage; }
	NameStorage * AsmStorage::GetNameStorage() { return &nameStorage; }
	PrefixStorage * AsmStorage::GetPrefixStorage() { return &prefixStorage; }
	void AsmStorage::Clear()
	{
		opcodeDataStorage.Clear();
		operandGrpStorage.Clear();
		nameStorage.Clear();
		prefixStorage.Clear();
	}
}  // namespace Disassembler
