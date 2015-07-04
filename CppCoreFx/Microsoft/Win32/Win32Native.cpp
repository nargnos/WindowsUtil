#include "Win32Native.h"

namespace Microsoft
{
	namespace Win32
	{
		using namespace LazyLoad;
		LPCWSTR _dllName_kernel32 = L"kernel32.dll";
		LPCWSTR _dllName_user32 = L"user32.dll";
		INIT_FUNC(BOOL,
			Beep, (
			_In_ DWORD dwFreq,
			_In_ DWORD dwDuration
			))
			DEF_FUNC_CODE(_dllName_kernel32, Beep, FALSE, (dwFreq, dwDuration));

		INIT_FUNC(BOOL,
			FillConsoleOutputCharacterW, (
			_In_ HANDLE hConsoleOutput,
			_In_ WCHAR  cCharacter,
			_In_ DWORD  nLength,
			_In_ COORD  dwWriteCoord,
			_Out_ LPDWORD lpNumberOfCharsWritten
			))
			DEF_FUNC_CODE(_dllName_kernel32, FillConsoleOutputCharacterW, FALSE, (hConsoleOutput, cCharacter, nLength, dwWriteCoord, lpNumberOfCharsWritten));

		INIT_FUNC(BOOL,
			FillConsoleOutputAttribute, (
			_In_ HANDLE hConsoleOutput,
			_In_ WORD   wAttribute,
			_In_ DWORD  nLength,
			_In_ COORD  dwWriteCoord,
			_Out_ LPDWORD lpNumberOfAttrsWritten
			))
			DEF_FUNC_CODE(_dllName_kernel32, FillConsoleOutputAttribute, FALSE, (hConsoleOutput, wAttribute, nLength, dwWriteCoord, lpNumberOfAttrsWritten));

		INIT_FUNC(BOOL,
			SetConsoleCursorPosition, (
			_In_ HANDLE hConsoleOutput,
			_In_ COORD dwCursorPosition
			))
			DEF_FUNC_CODE(_dllName_kernel32, SetConsoleCursorPosition, FALSE, (hConsoleOutput, dwCursorPosition));

		INIT_FUNC(BOOL,
			WriteFile, (
			_In_ HANDLE hFile,
			_In_reads_bytes_opt_(nNumberOfBytesToWrite) LPCVOID lpBuffer,
			_In_ DWORD nNumberOfBytesToWrite,
			_Out_opt_ LPDWORD lpNumberOfBytesWritten,
			_Inout_opt_ LPOVERLAPPED lpOverlapped
			))
			DEF_FUNC_CODE(_dllName_kernel32, WriteFile, FALSE, (
			hFile,
			lpBuffer,
			nNumberOfBytesToWrite,
			lpNumberOfBytesWritten,
			lpOverlapped
			));

		INIT_FUNC(DWORD,
			GetFileType, (
			_In_ HANDLE hFile
			))
			DEF_FUNC_CODE(_dllName_kernel32, GetFileType, NULL, (hFile));

		INIT_FUNC(BOOL,
			GetConsoleMode, (
			_In_ HANDLE hConsoleHandle,
			_Out_ LPDWORD lpMode
			))
			DEF_FUNC_CODE(_dllName_kernel32, GetConsoleMode, FALSE, (hConsoleHandle, lpMode));

		INIT_FUNC(BOOL,
			ReadConsoleOutputW, (
			_In_ HANDLE hConsoleOutput,
			_Out_writes_(dwBufferSize.X * dwBufferSize.Y) PCHAR_INFO lpBuffer,
			_In_ COORD dwBufferSize,
			_In_ COORD dwBufferCoord,
			_Inout_ PSMALL_RECT lpReadRegion
			))
			DEF_FUNC_CODE(_dllName_kernel32, ReadConsoleOutputW, FALSE, (
			hConsoleOutput,
			lpBuffer,
			dwBufferSize,
			dwBufferCoord,
			lpReadRegion
			));

		INIT_FUNC(BOOL,
			WriteConsoleOutputW,(
			_In_ HANDLE hConsoleOutput,
			_In_reads_(dwBufferSize.X * dwBufferSize.Y) CONST CHAR_INFO *lpBuffer,
			_In_ COORD dwBufferSize,
			_In_ COORD dwBufferCoord,
			_Inout_ PSMALL_RECT lpWriteRegion
			))
			DEF_FUNC_CODE(_dllName_kernel32, WriteConsoleOutputW, FALSE, (
			hConsoleOutput,
			lpBuffer,
			dwBufferSize,
			dwBufferCoord,
			lpWriteRegion
			));

		INIT_FUNC(BOOL,
			ReadConsoleInputW, (
			_In_ HANDLE hConsoleInput,
			_Out_writes_to_(nLength, *lpNumberOfEventsRead) PINPUT_RECORD lpBuffer,
			_In_ DWORD nLength,
			_Out_ _Deref_out_range_(<= , nLength) LPDWORD lpNumberOfEventsRead
			))
			DEF_FUNC_CODE(_dllName_kernel32, ReadConsoleInputW, FALSE, (
			hConsoleInput,
			lpBuffer,
			nLength,
			lpNumberOfEventsRead
			));

		INIT_FUNC(BOOL,
			SetConsoleTextAttribute,(
			_In_ HANDLE hConsoleOutput,
			_In_ WORD wAttributes
			))
			DEF_FUNC_CODE(_dllName_kernel32, SetConsoleTextAttribute, FALSE, (
			hConsoleOutput,
			wAttributes
			));

		INIT_FUNC(BOOL,
			SetConsoleScreenBufferSize, (
			_In_ HANDLE hConsoleOutput,
			_In_ COORD dwSize
			))
			DEF_FUNC_CODE(_dllName_kernel32, SetConsoleScreenBufferSize, FALSE, (
			hConsoleOutput,
			dwSize
			));

		INIT_FUNC(BOOL,
			SetConsoleWindowInfo, (
			_In_ HANDLE hConsoleOutput,
			_In_ BOOL bAbsolute,
			_In_ CONST SMALL_RECT *lpConsoleWindow
			))
			DEF_FUNC_CODE(_dllName_kernel32, SetConsoleWindowInfo, FALSE, (
			hConsoleOutput,
			bAbsolute,
			lpConsoleWindow
			));

		INIT_FUNC(COORD,
			GetLargestConsoleWindowSize, (
			_In_ HANDLE hConsoleOutput
			))
			DEF_FUNC_CODE(_dllName_kernel32, GetLargestConsoleWindowSize, COORD(), (hConsoleOutput));

		INIT_FUNC(SHORT,
			GetKeyState, (
			_In_ int nVirtKey))
			DEF_FUNC_CODE(_dllName_user32, GetKeyState, 0, (nVirtKey));

		INIT_FUNC(HANDLE,
			GetStdHandle, (
			_In_ DWORD nStdHandle
			))
			DEF_FUNC_CODE(_dllName_kernel32, GetStdHandle, NULL, (nStdHandle));


		INIT_FUNC(BOOL,
			GetConsoleCursorInfo, (
			_In_ HANDLE hConsoleOutput,
			_Out_ PCONSOLE_CURSOR_INFO lpConsoleCursorInfo
			))
			DEF_FUNC_CODE(_dllName_kernel32, GetConsoleCursorInfo, FALSE, (
			hConsoleOutput,
			lpConsoleCursorInfo
			));

		INIT_FUNC(BOOL,
			SetConsoleCursorInfo, (
			_In_ HANDLE hConsoleOutput,
			_In_ CONST CONSOLE_CURSOR_INFO *lpConsoleCursorInfo
			))
			DEF_FUNC_CODE(_dllName_kernel32, SetConsoleCursorInfo, FALSE, (
			hConsoleOutput,
			lpConsoleCursorInfo
			));
	}
}