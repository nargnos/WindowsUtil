#pragma once
namespace PeDecoder
{
	template<typename TInterface, typename TType32, typename TFunc32, typename TType64, typename TFunc64>
	class VisitorBase :
		public TInterface
	{
	public:
		VisitorBase(TFunc32&& func32, TFunc64&& func64) :
			func32_(_STD forward<TFunc32>(func32)),
			func64_(_STD forward<TFunc64>(func64))
		{

		}
		virtual ~VisitorBase() = default;

		virtual void Visit(const TType32 & nt) const override
		{
			func32_(nt);
		}
		virtual void Visit(const TType64 & nt) const override
		{
			func64_(nt);
		}
	private:
		TFunc32 func32_;
		TFunc64 func64_;
	};
}  // namespace PeDecoder