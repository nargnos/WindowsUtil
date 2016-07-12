#pragma once
#include "Common.h"
#include "NamePipeBase.h"
namespace Process
{
	namespace InterProcess
	{
		enum class PipeDirection :DWORD
		{
			In = PIPE_ACCESS_INBOUND,
			Out = PIPE_ACCESS_OUTBOUND,
			InOut = PIPE_ACCESS_DUPLEX
		};
		enum class PipeTransmissionMode :DWORD
		{
			Byte = PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
			Message = PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE
		};

		enum class PipeOptions :DWORD
		{
			WriteThrough = FILE_FLAG_WRITE_THROUGH,
			None = 0,
			// Asynchronous = FILE_FLAG_OVERLAPPED
		};

		// TODO: 需要尽量弄得像c#的NamedPipeServerStream，看有没有办法继承iostream
		// UNDONE: 测试不够,接口设计得不是很好，有空再弄
		template<bool IsAsync>
		class NamePipeServer :
			public Detail::NamePipeBase<IsAsync>
		{
		public:
			static const unsigned char MaxAllowedServerInstances = PIPE_UNLIMITED_INSTANCES;
			// \\.\pipe\pipename
			NamePipeServer(LPCTSTR name,
				PipeDirection direction = PipeDirection::InOut,
				size_t maxNumberOfInstances = MaxAllowedServerInstances,
				PipeTransmissionMode transmissionMode = PipeTransmissionMode::Byte,
				PipeOptions options = PipeOptions::None,
				int inBufferSize = 0,
				int outBufferSize = 0) :
				NamePipeBase<IsAsync>(Create(name,
					direction,
					maxNumberOfInstances,
					transmissionMode,
					options,
					inBufferSize,
					outBufferSize))
			{

			}

			~NamePipeServer() = default;

			auto WaitForConnection()
			{
				return _WaitForConnection<IsAsync>();
			}
			auto WaitForConnection(_STD function<void(ULONG)>&& cb)
			{
				return _WaitForConnection<IsAsync>(_STD forward<_STD function<void(ULONG)>>(cb));
			}



		protected:
			static HANDLE Create(LPCTSTR name,
				PipeDirection direction,
				size_t maxNumberOfInstances,
				PipeTransmissionMode transmissionMode,
				PipeOptions options,
				int inBufferSize,
				int outBufferSize)
			{
				assert(maxNumberOfInstances <= MaxAllowedServerInstances);
				return Detail::CreateNamedPipe(name,
					static_cast<DWORD>(direction) | static_cast<DWORD>(options) | (IsAsync ? FILE_FLAG_OVERLAPPED : 0),
					static_cast<DWORD>(transmissionMode),
					maxNumberOfInstances,
					outBufferSize,
					inBufferSize,
					0,
					NULL
				);
			}

			template<bool async, _STD enable_if_t<!async, bool> = async>
			auto _WaitForConnection()
			{
				assert(IsOpen());
				auto result = Detail::ConnectNamedPipe(NativeHandle(), NULL) != 0;
				if (result)
				{
					state_ = Detail::PipeState::Connected;
				}
				return result;
			}
			template<bool async, _STD enable_if_t<async, bool> = async>
			auto _WaitForConnection()
			{
				auto p = _STD make_shared< _STD promise<bool>>();
				auto result = p->get_future();
				auto ret = _WaitForConnection<async>([pms = p](ULONG result) mutable
				{
					pms->set_value(result == S_OK);
				});
				if (!ret && GetLastError() != ERROR_IO_PENDING)
				{
					p->set_value(false);
				}
				return result;
			}

			template<bool async, _STD enable_if_t<async, bool> = async>
			bool _WaitForConnection(_STD function<void(ULONG)>&& cb)
			{
				assert(IsAsync);
				assert(IsOpen());
				auto param = new Detail::CallbackOverlapped();
				param->Func = [func = _STD move(cb), this](ULONG result, ULONG_PTR) mutable
				{
					if (result == 0)
					{
						state_ = Detail::PipeState::Connected;
					}
					if (func)
					{
						func(result);
					}
				};
				Detail::StartThreadpoolIo(io_);
				return Detail::ConnectNamedPipe(NativeHandle(), param) != 0;
			}
		};

		template<bool IsAsync>
		class NamePipeClient :
			public Detail::NamePipeBase<IsAsync>
		{
		public:
			NamePipeClient(LPCTSTR name,
				PipeDirection direction = PipeDirection::InOut,
				PipeOptions options = PipeOptions::None) :
				NamePipeBase<IsAsync>(),
				name_(name)
			{
				static DWORD optionTable[]{ GENERIC_READ ,GENERIC_WRITE , GENERIC_READ | GENERIC_WRITE };
				direction_ = optionTable[static_cast<DWORD>(direction) - 1];
				options_ = static_cast<DWORD>(options) | (IsAsync ? FILE_FLAG_OVERLAPPED : 0);
			}
			// TODO: 阻塞到连接上为止
			bool Connect()
			{
				assert(!IsOpen());
				auto handle = Create(name_, direction_, options_);
				if (handle == INVALID_HANDLE_VALUE)
				{
					return false;
				}

				InitIo(handle);
				state_ = Detail::PipeState::Connected;
				return true;
			}
			~NamePipeClient() = default;

		protected:
			LPCTSTR name_;
			DWORD direction_;
			DWORD options_;

			static HANDLE Create(LPCTSTR name,
				DWORD direction,
				DWORD options)
			{
				return Detail::CreateFile(
					name,
					direction,
					0,
					NULL,
					OPEN_EXISTING,
					options,
					NULL);
			}
		};

	}  // namespace InterProcess
}  // namespace Process