#pragma once
namespace Process
{
	namespace InterProcess
	{
		// UNDONE: 
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

				NamePipeBase() :
					state_(Detail::PipeState::WaitingToConnect),
					io_(nullptr),
					handle_(nullptr)
				{
				}

				~NamePipeBase()
				{
					if (io_ != nullptr)
					{
						CancelThreadpoolIo(io_);
						CloseThreadpoolIo(io_);
					}
					Dispose();
				}
				void Dispose()
				{
					if (IsOpen())
					{
						Disconnect();
						Detail::CloseHandle(NativeHandle());
						SetHandle(nullptr);
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
					return NativeHandle() != nullptr;
				}
				auto Write(const char* buffer, size_t bufferSize)
				{
					assert(NativeHandle());
					assert(state_ == Detail::PipeState::Connected);
					return _Write<IsAsync>(buffer, bufferSize);
				}
				auto Write(const char* buffer, size_t bufferSize, Detail::Callback&& cb)
				{
					assert(NativeHandle());
					assert(state_ == Detail::PipeState::Connected);
					return _Write<IsAsync>(buffer, bufferSize, _STD move(cb));
				}
				auto Read(char* buffer, size_t bufferSize)
				{
					assert(NativeHandle());
					assert(state_ == Detail::PipeState::Connected);
					return _Read<IsAsync>(buffer, bufferSize);
				}
				auto Read(char* buffer, size_t bufferSize, Detail::Callback&& cb)
				{
					assert(NativeHandle());
					assert(state_ == Detail::PipeState::Connected);
					return _Read<IsAsync>(buffer, bufferSize, _STD move(cb));
				}

				void Disconnect()
				{
					assert(NativeHandle());
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
				_STD enable_if_t<async> InitIo()
				{
					io_ = Detail::CreateThreadpoolIo(NativeHandle(), IoCallback, NULL, NULL);
				}
				template<bool async>
				_STD enable_if_t<!async> InitIo()
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


		template<bool IsAsync>
		class NamePipeServer :public Detail::NamePipeBase<IsAsync>
		{
		public:
			static const unsigned char MaxAllowedServerInstances = PIPE_UNLIMITED_INSTANCES;
			// \\.\pipe\pipename
			NamePipeServer(LPCTSTR name = nullptr,
				PipeDirection direction = PipeDirection::InOut,
				size_t maxNumberOfInstances = 1,
				PipeTransmissionMode transmissionMode = PipeTransmissionMode::Byte,
				PipeOptions options = PipeOptions::None,
				int inBufferSize = 0,
				int outBufferSize = 0)
			{
				assert(maxNumberOfInstances <= MaxAllowedServerInstances);
				auto handle = Detail::CreateNamedPipe(name,
					static_cast<DWORD>(direction) | static_cast<DWORD>(options) | (IsAsync ? FILE_FLAG_OVERLAPPED : 0),
					static_cast<DWORD>(transmissionMode),
					maxNumberOfInstances,
					outBufferSize,
					inBufferSize,
					0,
					NULL
				);
				if (handle != INVALID_HANDLE_VALUE)
				{
					SetHandle(handle);
					InitIo<IsAsync>();
				}
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
			template<bool async, _STD enable_if_t<!async, bool> = async>
			auto _WaitForConnection()
			{
				assert(NativeHandle());
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
				assert(NativeHandle());
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




	}  // namespace InterProcess
}  // namespace Process