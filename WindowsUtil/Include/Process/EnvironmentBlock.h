#pragma once
#include <Windows.h>
#include <winternl.h>

namespace Peb
{
	// struct定义修改自reactos源码
	//
	// Loader Data Table Entry
	//
	typedef struct _LDR_DATA_TABLE_ENTRY_Ex
	{
		LIST_ENTRY InLoadOrderLinks;
		LIST_ENTRY InMemoryOrderModuleList;
		LIST_ENTRY InInitializationOrderModuleList;
		PVOID DllBase;
		PVOID EntryPoint;
		ULONG SizeOfImage;
		UNICODE_STRING FullDllName;
		UNICODE_STRING BaseDllName;
		ULONG Flags;
		USHORT LoadCount;
		USHORT TlsIndex;
		union
		{
			LIST_ENTRY HashLinks;
			struct
			{
				PVOID SectionPointer;
				ULONG CheckSum;
			};
		};
		union
		{
			ULONG TimeDateStamp;
			PVOID LoadedImports;
		};
		PVOID EntryPointActivationContext;
		PVOID PatchInformation;
	} LDR_DATA_TABLE_ENTRY_Ex, *PLDR_DATA_TABLE_ENTRY_Ex;


	typedef struct _PEB_FREE_BLOCK {
		struct _PEB_FREE_BLOCK *Next;
		ULONG Size;
	} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;
#define GDI_HANDLE_BUFFER_SIZE      34
#define TLS_MINIMUM_AVAILABLE 64    // winnt
	//
	// Loader Data stored in the PEB
	//
	typedef struct _PEB_LDR_DATA_Ex
	{
		ULONG Length;
		BOOLEAN Initialized;
		PVOID SsHandle;
		LIST_ENTRY InLoadOrderModuleList;
		LIST_ENTRY InMemoryOrderModuleList;
		LIST_ENTRY InInitializationOrderModuleList;
		PVOID EntryInProgress;
#if (NTDDI_VERSION >= NTDDI_WIN7)
		UCHAR ShutdownInProgress;
		PVOID ShutdownThreadId;
#endif
	} PEB_LDR_DATA_Ex, *PPEB_LDR_DATA_Ex;

	typedef struct _PEB_Ex {
		BOOLEAN InheritedAddressSpace;      // These four fields cannot change unless the
		BOOLEAN ReadImageFileExecOptions;   //
		BOOLEAN BeingDebugged;              //
		BOOLEAN SpareBool;                  //
		HANDLE Mutant;                      // INITIAL_PEB structure is also updated.

		PVOID ImageBaseAddress;
		PPEB_LDR_DATA_Ex Ldr;
		struct _RTL_USER_PROCESS_PARAMETERS *ProcessParameters;
		PVOID SubSystemData;
		PVOID ProcessHeap;
		PVOID FastPebLock;
		PVOID FastPebLockRoutine;
		PVOID FastPebUnlockRoutine;
		ULONG EnvironmentUpdateCount;
		PVOID KernelCallbackTable;
		HANDLE EventLogSection;
		PVOID EventLog;
		PPEB_FREE_BLOCK FreeList;
		ULONG TlsExpansionCounter;
		PVOID TlsBitmap;
		ULONG TlsBitmapBits[2];         // relates to TLS_MINIMUM_AVAILABLE
		PVOID ReadOnlySharedMemoryBase;
		PVOID ReadOnlySharedMemoryHeap;
		PVOID *ReadOnlyStaticServerData;
		PVOID AnsiCodePageData;
		PVOID OemCodePageData;
		PVOID UnicodeCaseTableData;

		// Useful information for LdrpInitialize
		ULONG NumberOfProcessors;
		ULONG NtGlobalFlag;

		// Passed up from MmCreatePeb from Session Manager registry key

		LARGE_INTEGER CriticalSectionTimeout;
		ULONG HeapSegmentReserve;
		ULONG HeapSegmentCommit;
		ULONG HeapDeCommitTotalFreeThreshold;
		ULONG HeapDeCommitFreeBlockThreshold;

		// Where heap manager keeps track of all heaps created for a process
		// Fields initialized by MmCreatePeb.  ProcessHeaps is initialized
		// to point to the first free byte after the PEB and MaximumNumberOfHeaps
		// is computed from the page size used to hold the PEB, less the fixed
		// size of this data structure.

		ULONG NumberOfHeaps;
		ULONG MaximumNumberOfHeaps;
		PVOID *ProcessHeaps;

		//
		//
		PVOID GdiSharedHandleTable;
		PVOID ProcessStarterHelper;
		PVOID GdiDCAttributeList;
		PVOID LoaderLock;

		// Following fields filled in by MmCreatePeb from system values and/or
		// image header.

		ULONG OSMajorVersion;
		ULONG OSMinorVersion;
		ULONG OSBuildNumber;
		ULONG OSPlatformId;
		ULONG ImageSubsystem;
		ULONG ImageSubsystemMajorVersion;
		ULONG ImageSubsystemMinorVersion;
		ULONG ImageProcessAffinityMask;
		ULONG GdiHandleBuffer[GDI_HANDLE_BUFFER_SIZE];
	} PEB_Ex, *PPEB_Ex;
	typedef struct _CLIENT_ID
	{
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	} CLIENT_ID, *PCLIENT_ID;
#define STATIC_UNICODE_BUFFER_LENGTH 261
#define WIN32_CLIENT_INFO_LENGTH 31
#define WIN32_CLIENT_INFO_SPIN_COUNT 1
	typedef struct _GDI_TEB_BATCH
	{
		ULONG  Offset;
		HANDLE HDC;
		ULONG  Buffer[0x136];
	} GDI_TEB_BATCH;
	typedef struct _TEB_Ex {
		NT_TIB NtTib;
		PVOID  EnvironmentPointer;
		CLIENT_ID ClientId;
		PVOID ActiveRpcHandle;
		PVOID ThreadLocalStoragePointer;
		PPEB_Ex ProcessEnvironmentBlock;
		ULONG LastErrorValue;
		ULONG CountOfOwnedCriticalSections;
		PVOID CsrClientThread;
		PVOID Win32ThreadInfo;          // PtiCurrent
		ULONG Win32ClientInfo[WIN32_CLIENT_INFO_LENGTH];    // User32 Client Info
		PVOID WOW32Reserved;           // used by WOW
		LCID CurrentLocale;
		ULONG FpSoftwareStatusRegister;
		PVOID SystemReserved1[54];      // Used by FP emulator
		PVOID Spare1;                   // unused
		NTSTATUS ExceptionCode;         // for RaiseUserException
		UCHAR SpareBytes1[40];
		PVOID SystemReserved2[10];                      // Used by user/console for temp obja
		GDI_TEB_BATCH GdiTebBatch;      // Gdi batching
		ULONG gdiRgn;
		ULONG gdiPen;
		ULONG gdiBrush;
		CLIENT_ID RealClientId;
		HANDLE GdiCachedProcessHandle;
		ULONG GdiClientPID;
		ULONG GdiClientTID;
		PVOID GdiThreadLocalInfo;
		PVOID UserReserved[5];          // unused
		PVOID glDispatchTable[280];     // OpenGL
		ULONG glReserved1[26];          // OpenGL
		PVOID glReserved2;              // OpenGL
		PVOID glSectionInfo;            // OpenGL
		PVOID glSection;                // OpenGL
		PVOID glTable;                  // OpenGL
		PVOID glCurrentRC;              // OpenGL
		PVOID glContext;                // OpenGL
		ULONG LastStatusValue;
		UNICODE_STRING StaticUnicodeString;
		WCHAR StaticUnicodeBuffer[STATIC_UNICODE_BUFFER_LENGTH];
		PVOID DeallocationStack;
		PVOID TlsSlots[TLS_MINIMUM_AVAILABLE];
		LIST_ENTRY TlsLinks;
		PVOID Vdm;
		PVOID ReservedForNtRpc;
		PVOID DbgSsReserved[2];
		ULONG HardErrorsAreDisabled;
		PVOID Instrumentation[16];
		PVOID WinSockData;              // WinSock
		ULONG GdiBatchCount;
		ULONG Spare2;
		ULONG Spare3;
		ULONG Spare4;
		PVOID ReservedForOle;
		ULONG WaitingOnLoaderLock;
	} TEB_Ex;
	typedef TEB_Ex *PTEB_Ex;

#define NtCurrentPeb (((PTEB_Ex)NtCurrentTeb())->ProcessEnvironmentBlock)

	// 定义结束

	enum LdrDataTableModuleList
	{
		InLoadOrderModuleList,
		InMemoryOrderModuleList,
		InInitializationOrderModuleList
	};
	// ldr双链表迭代器
	class LdrDataTableEntryReader
	{
	public:

		LdrDataTableEntryReader(LdrDataTableModuleList desList);
		LdrDataTableEntryReader(PPEB_Ex peb, LdrDataTableModuleList desList);
		LdrDataTableEntryReader(PPEB_LDR_DATA_Ex ldr, LdrDataTableModuleList desList);
		~LdrDataTableEntryReader();
		bool Next();
		PLDR_DATA_TABLE_ENTRY_Ex Current();
		void Reset();
	private:
		PLIST_ENTRY ModuleListHead;
		PLIST_ENTRY TmpEntry;
		PLDR_DATA_TABLE_ENTRY_Ex Module;
		LdrDataTableModuleList desList;
	};
	HINSTANCE __stdcall FindLoadedModuleHandle(LPCWSTR name);
}