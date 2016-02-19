#include "AsmDisassembler.h"
#include "State\AsmStateFactory.h"
#include "..\Common\DisassemblerBase.h"
namespace Disassembler
{
	unsigned int AsmDisassembler::Parse(void * pos)
	{
		this->GetStorage()->SetInitialPosition(pos);
		Trait::TStateFactory::NextStateFunction getNextStateID = NULL;
		auto stateUsed = dynamic_cast<Trait::TStateUsed*>(this);
		auto endID = Trait::TStateFactory::GetEndStateID();
		for (auto i = Trait::TStateFactory::GetBeginStateID();
			i != endID;
			i = getNextStateID(stateUsed))
		{
			getNextStateID = Trait::TStateFactory::GetStateFunction(i);
			assert(getNextStateID);
		}

		return 0;
	}

	unique_ptr<IInstruction> AsmDisassembler::GetResult() const
	{
		return unique_ptr<IInstruction>();
	}

}  // namespace Disassembler

