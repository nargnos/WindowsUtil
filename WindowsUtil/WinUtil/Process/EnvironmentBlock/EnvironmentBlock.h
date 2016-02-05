#pragma once
#include <Windows.h>
#include <winternl.h>
#include <cassert>
namespace Process
{
	namespace EnvironmentBlock
	{
#define NtCurrentProcess()                      ((HANDLE)(LONG_PTR)-1)
#define NtCurrentThread()                       ((HANDLE)(LONG_PTR)-2)
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
		typedef struct _NLS_USER_INFO
		{
			WCHAR iCountry[80];
			WCHAR sCountry[80];
			WCHAR sList[80];
			WCHAR iMeasure[80];
			WCHAR iPaperSize[80];
			WCHAR sDecimal[80];
			WCHAR sThousand[80];
			WCHAR sGrouping[80];
			WCHAR iDigits[80];
			WCHAR iLZero[80];
			WCHAR iNegNumber[80];
			WCHAR sNativeDigits[80];
			WCHAR iDigitSubstitution[80];
			WCHAR sCurrency[80];
			WCHAR sMonDecSep[80];
			WCHAR sMonThouSep[80];
			WCHAR sMonGrouping[80];
			WCHAR iCurrDigits[80];
			WCHAR iCurrency[80];
			WCHAR iNegCurr[80];
			WCHAR sPosSign[80];
			WCHAR sNegSign[80];
			WCHAR sTimeFormat[80];
			WCHAR s1159[80];
			WCHAR s2359[80];
			WCHAR sShortDate[80];
			WCHAR sYearMonth[80];
			WCHAR sLongDate[80];
			WCHAR iCalType[80];
			WCHAR iFirstDay[80];
			WCHAR iFirstWeek[80];
			WCHAR sLocale[80];
			WCHAR sLocaleName[85];
			LCID UserLocaleId;
			LUID InteractiveUserLuid;
			CHAR InteractiveUserSid[68];  // SECURITY_MAX_SID_SIZE to make ros happy
			ULONG ulCacheUpdateCount;
		} NLS_USER_INFO, *PNLS_USER_INFO;

		typedef struct _KSYSTEM_TIME {
			ULONG LowPart;
			LONG High1Time;
			LONG High2Time;
		} KSYSTEM_TIME, *PKSYSTEM_TIME;

		typedef struct _BASE_STATIC_SERVER_DATA
		{
			UNICODE_STRING WindowsDirectory;
			UNICODE_STRING WindowsSystemDirectory;
			UNICODE_STRING NamedObjectDirectory;
			USHORT WindowsMajorVersion;
			USHORT WindowsMinorVersion;
			USHORT BuildNumber;
			USHORT CSDNumber;
			USHORT RCNumber;
			WCHAR CSDVersion[128];
			SYSTEM_BASIC_INFORMATION SysInfo;
			SYSTEM_TIMEOFDAY_INFORMATION TimeOfDay;
			PVOID IniFileMapping;
			NLS_USER_INFO NlsUserInfo;
			BOOLEAN DefaultSeparateVDM;
			BOOLEAN IsWowTaskReady;
			UNICODE_STRING WindowsSys32x86Directory;
			BOOLEAN fTermsrvAppInstallMode;
			TIME_ZONE_INFORMATION tziTermsrvClientTimeZone;
			KSYSTEM_TIME ktTermsrvClientBias;
			ULONG TermsrvClientTimeZoneId;
			BOOLEAN LUIDDeviceMapsEnabled;
			ULONG TermsrvClientTimeZoneChangeNum;
		} BASE_STATIC_SERVER_DATA, *PBASE_STATIC_SERVER_DATA;
		// 定义结束

		typedef enum class _LdrDataTableModuleList
		{
			InLoadOrderModuleList,
			InMemoryOrderModuleList,
			InInitializationOrderModuleList
		}LdrDataTableModuleList;



		// ldr双链表迭代器，可以用3种方式遍历
		class LdrDataTableEntryReader
		{
		public:

			explicit LdrDataTableEntryReader(LdrDataTableModuleList desList);
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

		typedef enum _MEMORY_INFORMATION_CLASS {
			MemoryBasicInformation,
			MemoryWorkingSetList,
			MemorySectionName,
			MemoryBasicVlmInformation
		} MEMORY_INFORMATION_CLASS;
	}  // namespace EnvironmentBlock
}  // namespace Process
