#include "AsmStorage.h"


namespace Disassembler
{
	AsmStorage::AsmStorage()
	{
		is32Bit = true;
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
