#include "InstructionParser.h"

InstructionParser::InstructionParser(const shared_ptr<IParseEngine>& parseEngine)
	:engine(parseEngine)
{
}

bool InstructionParser::TryParse(void* pos, _Out_ shared_ptr<IInstruction>& result)
{
	return true;
}
