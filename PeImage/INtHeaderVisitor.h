#pragma once
namespace PeDecoder
{
	class NtHeader32;
	class NtHeader64;
	__interface INtHeaderVisitor
	{
		void Visit(const NtHeader32& nt) const;
		void Visit(const NtHeader64& nt) const;
	};

	template<typename TFunc32, typename TFunc64>
	class NtHeaderVisitorBase:
		public INtHeaderVisitor
	{
	public:
		NtHeaderVisitorBase(TFunc32&& func32, TFunc64&& func64) :
			func32_(_STD move(func32)),
			func64_(_STD move(func64))
		{

		}
		virtual ~NtHeaderVisitorBase() = default;

		virtual void Visit(const NtHeader32 & nt) const override
		{
			func32_(nt);
		}
		virtual void Visit(const NtHeader64 & nt) const override
		{
			func64_(nt);
		}
	private:
		TFunc32 func32_;
		TFunc64 func64_;
	};
	template<typename TFunc32, typename TFunc64>
	auto MakeNtHeaderVisitor(TFunc32&& func32, TFunc64&& func64)
	{
		return NtHeaderVisitorBase<TFunc32, TFunc64>(_STD move(func32), _STD move(func64));
	}
}  // namespace PeDecoder
