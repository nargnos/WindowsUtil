#pragma once
#include "Common.h"

#include "Disassembler_Trait.h"
#include "Interface\IDisassembler.h"
#include "Interface\IStateUsed.h"
namespace Disassembler
{
	// 参数为子类
	template<typename TChild, typename TTrait = Disassembler_Trait<TChild>>
	class DisassemblerBase
		:public IDisassembler,
		protected IStateUsed<TTrait>
	{
	public:
		typedef TTrait TTrait;
		typedef typename TTrait::TOpcodeDataWapper TOpcodeDataWapper;
		typedef typename TTrait::TStorage TStorage;
		typedef typename TTrait::TStateFactory TStateFactory;
		DisassemblerBase()
		{
			auto isChild = std::is_base_of<IDisassembler, TChild>::value;
			assert(isChild);
		}

		~DisassemblerBase()
		{
		}
		virtual unsigned int Parse(void * pos) override
		{
			auto storage = GetStorage();
			storage->SetInitialPosition(pos);
			TStateFactory::NextStateFunction getNextStateID = NULL;
			auto stateUsed = dynamic_cast<TTrait::TStateUsed*>(this);
			auto endID = TStateFactory::GetEndStateID();

			for (auto i = TStateFactory::GetBeginStateID(); i != endID; i = getNextStateID(stateUsed))
			{
				getNextStateID = TStateFactory::GetStateFunction(i);
				assert(getNextStateID);
			}

			if (storage->IsSuccess())
			{
				// TODO: 内部的指针偏移还有很多未完成
				return storage->GetCurrentPosition() - pos;
			}
			return 0;
		}
	protected:
		TOpcodeDataWapper opcodeDataWapper;
		TStorage storage;

		virtual TOpcodeDataWapper* GetOpcodeDataWapper() override
		{
			return &opcodeDataWapper;
		}
		virtual TStorage* GetStorage() override
		{
			return &storage;
		}
	};
}  // namespace Disassembler
