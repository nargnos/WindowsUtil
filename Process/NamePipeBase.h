#pragma once
#include "Common.h"
namespace Process
{
	namespace InterProcess
	{
		
		namespace Detail
		{
			using ::CallNamedPipe;
			using ::ConnectNamedPipe;
			using ::CreateNamedPipe;
			using ::DisconnectNamedPipe;
			using ::GetNamedPipeClientComputerName;
			using ::GetNamedPipeClientProcessId;
			using ::GetNamedPipeClientSessionId;
			using ::GetNamedPipeHandleState;
			using ::GetNamedPipeInfo;
			using ::GetNamedPipeServerProcessId;
			using ::GetNamedPipeServerSessionId;
			using ::ImpersonateNamedPipeClient;
			using ::PeekNamedPipe;
			using ::SetNamedPipeHandleState;
			using ::TransactNamedPipe;
			using ::WaitNamedPipe;
			using ::CreateFile;
			using ::WriteFile;
			using ::ReadFile;
			using ::StartThreadpoolIo;
			using ::CreateThreadpoolIo;
			using ::CloseHandle;

			enum class PipeState :char
			{
				WaitingToConnect,
				Connected,
				Broken,
				Disconnected,
				Closed
			};
			using Callback = _STD function<void(ULONG ioResult, ULONG_PTR numberOfBytesTransferred)>;
			struct CallbackOverlapped :public OVERLAPPED
			{
				Callback Func;
			};

			struct ResultType
			{
				bool Result;
				DWORD NumberOfBytesTransferred;
			};

			struct AsyncResultType
			{
				bool Result;
				struct _IoResult
				{
					ULONG IoResult;
					ULONG_PTR NumberOfBytesTransferred;
				};
				_STD future<_IoResult> AsyncResult;
			};
			template<bool IsAsync>
			class NamePipeBase
			{
			public:

				using ResultType = _STD conditional_t<IsAsync, Detail::AsyncResultType, Detail::ResultType>;

				NamePipeBase(HANDLE handle) :NamePipeBase()
				{
					InitIo(handle);
				}
				NamePipeBase() :
					state_(Detail::PipeState::WaitingToConnect),
					io_(nullptr),
					handle_(INVALID_HANDLE_VALUE)
				{

				}


				~NamePipeBase()
				{
					if (io_ != nullptr)
					{						
						CancelThreadpoolIo(io_);
						CloseThreadpoolIo(io_);
						io_ = nullptr;
					}
					Dispose();
				}
				void Dispose()
				{
					if (IsOpen())
					{
						Disconnect();
						Detail::CloseHandle(NativeHandle());
						SetHandle(INVALID_HANDLE_VALUE);
					}
				}
				bool IsConnected()
				{
					return state_ == Detail::PipeState::Connected;
				}
				HANDLE NativeHandle()
				{
					return handle_;
				}
				bool IsOpen()
				{
					return NativeHandle() != INVALID_HANDLE_VALUE;
				}
				auto Write(const char* buffer, size_t bufferSize)
				{
					assert(IsOpen());
					assert(state_ == Detail::PipeState::Connected);
					return _Write<IsAsync>(buffer, bufferSize);
				}
				auto Write(const char* buffer, size_t bufferSize, Detail::Callback&& cb)
				{
					assert(IsOpen());
					assert(state_ == Detail::PipeState::Connected);
					return _Write<IsAsync>(buffer, bufferSize, _STD move(cb));
				}
				auto Read(char* buffer, size_t bufferSize)
				{
					assert(IsOpen());
					assert(state_ == Detail::PipeState::Connected);
					return _Read<IsAsync>(buffer, bufferSize);
				}
				auto Read(char* buffer, size_t bufferSize, Detail::Callback&& cb)
				{
					assert(IsOpen());
					assert(state_ == Detail::PipeState::Connected);
					return _Read<IsAsync>(buffer, bufferSize, _STD move(cb));
				}

				void Disconnect()
				{
					assert(IsOpen());
					if (state_ != Detail::PipeState::Disconnected && Detail::DisconnectNamedPipe(NativeHandle()))
					{
						state_ = Detail::PipeState::Disconnected;
					}
				}
			protected:
				NamePipeBase(const NamePipeBase&) = delete;
				const NamePipeBase& operator=(const NamePipeBase&) = delete;
				void SetHandle(HANDLE h)
				{
					handle_ = h;
				}
				void InitIo(HANDLE handle)
				{
					if (handle != INVALID_HANDLE_VALUE)
					{
						SetHandle(handle);
						_InitIo<IsAsync>();
					}
				}
				static _STD enable_if_t<IsAsync>
					WINAPI IoCallback(
						_Inout_     PTP_CALLBACK_INSTANCE instance,
						_Inout_opt_ PVOID                 context,
						_Inout_opt_ PVOID                 overlapped,
						_In_        ULONG                 ioResult,
						_In_        ULONG_PTR             numberOfBytesTransferred,
						_Inout_     PTP_IO                io
					)
				{
					auto ol = _STD unique_ptr<Detail::CallbackOverlapped>(static_cast<Detail::CallbackOverlapped*>(overlapped));
					assert(ol);
					if (ol->Func)
					{
						ol->Func(ioResult, numberOfBytesTransferred);
					}
				}


				template<bool async>
				_STD enable_if_t<async> _InitIo()
				{
					io_ = Detail::CreateThreadpoolIo(NativeHandle(), IoCallback, NULL, NULL);
				}
				template<bool async>
				_STD enable_if_t<!async> _InitIo()
				{
				}

				template<bool async, _STD enable_if_t<!async, bool> = async>
				ResultType _Write(const char* buffer, size_t bufferSize)
				{
					ResultType result{ false, 0 };
					result.Result = Detail::WriteFile(NativeHandle(), buffer, bufferSize, &result.NumberOfBytesTransferred, NULL) != 0;

					return result;
				}
				template<bool async, _STD enable_if_t<async, bool> = async>
				bool _Write(const char* buffer, size_t bufferSize, Detail::Callback&& cb)
				{
					auto param = new Detail::CallbackOverlapped();
					param->Func = _STD move(cb);
					assert(io_);
					Detail::StartThreadpoolIo(io_);
					auto ret = Detail::WriteFile(NativeHandle(), buffer, bufferSize, NULL, param);

					return ret || GetLastError() == ERROR_IO_PENDING;
				}
				template<bool async, _STD enable_if_t<async, bool> = async>
				ResultType _Write(const char* buffer, size_t bufferSize)
				{
					auto p = _STD make_shared<_STD promise<typename ResultType::_IoResult>>();
					ResultType result{ false, _STD move(p->get_future()) };

					result.Result = _Write<async>(buffer, bufferSize, [pms = _STD move(p)]
					(ULONG ioResult, ULONG_PTR numberOfBytesTransferred) mutable
					{
						typename ResultType::_IoResult result{ ioResult, numberOfBytesTransferred };
						pms->set_value(result);
					}) != 0;

					return result;
				}


				template<bool async, _STD enable_if_t<!async, bool> = async>
				ResultType _Read(char* buffer, size_t bufferSize)
				{
					ResultType result{ false, 0 };
					result.Result = Detail::ReadFile(NativeHandle(), buffer, bufferSize, &result.NumberOfBytesTransferred, NULL) != 0;

					return result;
				}
				template<bool async, _STD enable_if_t<async, bool> = async>
				bool _Read(char* buffer, size_t bufferSize, Detail::Callback&& cb)
				{

					auto param = new Detail::CallbackOverlapped();
					param->Func = _STD move(cb);
					assert(io_);
					Detail::StartThreadpoolIo(io_);
					auto ret = Detail::ReadFile(NativeHandle(), buffer, bufferSize, NULL, param);
					return ret || GetLastError() == ERROR_IO_PENDING;
				}
				template<bool async, _STD enable_if_t<async, bool> = async>
				ResultType _Read(char* buffer, size_t bufferSize)
				{
					auto p = _STD make_shared<_STD promise<typename ResultType::_IoResult>>();
					ResultType result{ false, _STD move(p->get_future()) };

					result.Result = _Read<async>(buffer, bufferSize, [pms = _STD move(p)]
					(ULONG ioResult, ULONG_PTR numberOfBytesTransferred) mutable
					{
						typename ResultType::_IoResult result{ ioResult, numberOfBytesTransferred };
						pms->set_value(result);
					}) != 0;

					return result;
				}


				Detail::PipeState state_;
				HANDLE handle_;
				PTP_IO io_;
			};
		}  // namespace Detail
	}  // namespace InterProcess
}  // namespace Process