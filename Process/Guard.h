#pragma once
#include <memory>

class Guard
{
public:
	struct IGuard
	{
		virtual void Run() const = 0;
		virtual ~IGuard() = default;
	};
	template<typename TFunc>
	class Func :public IGuard
	{
	public:
		explicit Func(TFunc&& func) :
			func_(_STD forward<TFunc>(func))
		{
		}

		virtual void Run() const override
		{
			func_();
		}

	private:
		TFunc func_;
	};

	template<typename TFunc>
	explicit Guard(TFunc&& func) :
		func_(_STD make_unique<Func<TFunc>>(_STD forward<TFunc>(func)))
	{
	}

	~Guard()
	{
		if (func_)
		{
			func_->Run();
			func_ = nullptr;
		}
	}
	Guard(Guard&& guard)
	{
		func_ = _STD move(guard.func_);
	}
private:
	_STD unique_ptr<IGuard> func_;
};

