#pragma once
#include "Common.h"
#include "LoadDllBase.h"
#include "NtDllGetDllModulePolicy.h"
#include "DynamicCall.h"
#include "EnvironmentBlock.h"
namespace Process
{
	namespace LazyLoad
	{
		using Process::EnvironmentBlock::CLIENT_ID;
		using Process::EnvironmentBlock::PCLIENT_ID;
		using Process::EnvironmentBlock::MEMORY_INFORMATION_CLASS;
		using Process::LazyLoad::Detail::DynamicCall;
		using Process::LazyLoad::Detail::LoadDllBase;
		using Process::LazyLoad::Detail::NtDllGetDllModulePolicy;

		class NtDll
		{
		public:
			class LoadNtDll;
			static const LoadNtDll& Instance();

		private:
			NtDll() = delete;
			~NtDll() = delete;
			static LoadNtDll instance_;
		};

		class NtDll::LoadNtDll :
			public LoadDllBase<NtDllGetDllModulePolicy>
		{
		public:
			friend class NtDll;
			~LoadNtDll() = default;			

			// FIX: 先用仿函数来做,想到更好的再改
			DynamicCall<NTSTATUS WINAPI(
				_In_opt_ PWSTR SearchPath,
				_In_opt_ PULONG LoadFlags,
				_In_ PUNICODE_STRING Name,
				_Out_opt_ PVOID *BaseAddress
			), TLoadDllBase> LdrLoadDll;

			DynamicCall<NTSTATUS WINAPI(
				OUT PHANDLE ProcessHandle,
				IN ACCESS_MASK DesiredAccess,
				IN POBJECT_ATTRIBUTES ObjectAttributes,
				IN PCLIENT_ID ClientId
			), TLoadDllBase>
				NtOpenProcess;

			DynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ThreadHandle,
				_In_ PCONTEXT Context
			), TLoadDllBase>
				NtSetContextThread;

			DynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID *BaseAddress,
				_In_ SIZE_T *NumberOfBytesToProtect,
				_In_ ULONG NewAccessProtection,
				_Out_ PULONG OldAccessProtection
			), TLoadDllBase>
				NtProtectVirtualMemory;

			DynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID BaseAddress,
				_Out_ PVOID Buffer,
				_In_ SIZE_T NumberOfBytesToRead,
				_Out_opt_ PSIZE_T NumberOfBytesRead
			), TLoadDllBase>
				NtReadVirtualMemory;

			DynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID  BaseAddress,
				_In_ PVOID Buffer,
				_In_ SIZE_T NumberOfBytesToWrite,
				_Out_opt_ PSIZE_T NumberOfBytesWritten
			), TLoadDllBase>
				NtWriteVirtualMemory;

			DynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID BaseAddress,
				_In_ ULONG NumberOfBytesToFlush
			), TLoadDllBase>
				NtFlushInstructionCache;

			DynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_Inout_ _Outptr_result_buffer_(*RegionSize) PVOID *BaseAddress,
				_In_ ULONG_PTR ZeroBits,
				_Inout_ PSIZE_T RegionSize,
				_In_ ULONG AllocationType,
				_In_ ULONG Protect
			), TLoadDllBase>
				NtAllocateVirtualMemory;

			DynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID Address,
				_In_ MEMORY_INFORMATION_CLASS VirtualMemoryInformationClass,
				_Out_ PVOID VirtualMemoryInformation,
				_In_ SIZE_T Length,
				_Out_opt_ PSIZE_T ResultLength
			), TLoadDllBase>
				NtQueryVirtualMemory;

			DynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_Inout_ __drv_freesMem(Mem) PVOID *BaseAddress,
				_Inout_ PSIZE_T RegionSize,
				_In_ ULONG FreeType
			), TLoadDllBase>
				NtFreeVirtualMemory;
		protected:
			LoadNtDll();

		};

		

	}  // namespace LazyLoad
}  // namespace Process
