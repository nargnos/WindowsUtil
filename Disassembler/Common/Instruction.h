#pragma once
#include "Common.h"
#include "Interface\IInstruction.h"
#include "ToStringBase.h"
namespace Disassembler
{
	/// <typeparam name="TToStringPolicy">
	/// ×Ö·û´®Êä³ö²ßÂÔ
	/// </typeparam>
	template<typename TInstruction, typename TToStringPolicy = ToStringBase<TInstruction>>
	class Instruction :public IInstruction
	{
	public:
		virtual void ToString(_STD ostringstream& strStream) const override
		{
			TToStringPolicy::ToString(dynamic_cast<const TInstruction*>(this), strStream);
		}
	};
}  // namespace Disassembler