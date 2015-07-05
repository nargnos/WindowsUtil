#pragma once
#include <Windows.h>
#include <Process\LazyLoad\LazyLoad.h>
namespace Microsoft
{
	namespace Win32
	{
		DEF_FUNC(BOOL, 
			Beep, (
			_In_ DWORD dwFreq,
			_In_ DWORD dwDuration
			));

		DEF_FUNC(BOOL,
			FillConsoleOutputCharacterW, (
			_In_ HANDLE hConsoleOutput,
			_In_ WCHAR  cCharacter,
			_In_ DWORD  nLength,
			_In_ COORD  dwWriteCoord,
			_Out_ LPDWORD lpNumberOfCharsWritten
			));

		DEF_FUNC(BOOL,
			FillConsoleOutputAttribute, (
			_In_ HANDLE hConsoleOutput,
			_In_ WORD   wAttribute,
			_In_ DWORD  nLength,
			_In_ COORD  dwWriteCoord,
			_Out_ LPDWORD lpNumberOfAttrsWritten
			));

		DEF_FUNC(BOOL,
			SetConsoleCursorPosition, (
			_In_ HANDLE hConsoleOutput,
			_In_ COORD dwCursorPosition
			));

		DEF_FUNC(BOOL,
			WriteFile, (
			_In_ HANDLE hFile,
			_In_reads_bytes_opt_(nNumberOfBytesToWrite) LPCVOID lpBuffer,
			_In_ DWORD nNumberOfBytesToWrite,
			_Out_opt_ LPDWORD lpNumberOfBytesWritten,
			_Inout_opt_ LPOVERLAPPED lpOverlapped
			));

		DEF_FUNC(DWORD,
			GetFileType, (
			_In_ HANDLE hFile
			));

		DEF_FUNC(BOOL,
			GetConsoleMode, (
			_In_ HANDLE hConsoleHandle,
			_Out_ LPDWORD lpMode
			));
		DEF_FUNC(BOOL,
			ReadConsoleOutputW,(
			_In_ HANDLE hConsoleOutput,
			_Out_writes_(dwBufferSize.X * dwBufferSize.Y) PCHAR_INFO lpBuffer,
			_In_ COORD dwBufferSize,
			_In_ COORD dwBufferCoord,
			_Inout_ PSMALL_RECT lpReadRegion
			));

		DEF_FUNC(BOOL,
			WriteConsoleOutputW,(
			_In_ HANDLE hConsoleOutput,
			_In_reads_(dwBufferSize.X * dwBufferSize.Y) CONST CHAR_INFO *lpBuffer,
			_In_ COORD dwBufferSize,
			_In_ COORD dwBufferCoord,
			_Inout_ PSMALL_RECT lpWriteRegion
			));

		DEF_FUNC(BOOL,
			ReadConsoleInputW, (
			_In_ HANDLE hConsoleInput,
			_Out_writes_to_(nLength, *lpNumberOfEventsRead) PINPUT_RECORD lpBuffer,
			_In_ DWORD nLength,
			_Out_ _Deref_out_range_(<= , nLength) LPDWORD lpNumberOfEventsRead
			));

		DEF_FUNC(BOOL,
			SetConsoleTextAttribute,(
			_In_ HANDLE hConsoleOutput,
			_In_ WORD wAttributes
			));

		DEF_FUNC(BOOL,
			SetConsoleScreenBufferSize,(
			_In_ HANDLE hConsoleOutput,
			_In_ COORD dwSize
			));


		DEF_FUNC(BOOL,
			SetConsoleWindowInfo,(
			_In_ HANDLE hConsoleOutput,
			_In_ BOOL bAbsolute,
			_In_ CONST SMALL_RECT *lpConsoleWindow
			));
		DEF_FUNC(COORD,
			GetLargestConsoleWindowSize,(
			_In_ HANDLE hConsoleOutput
			));

		DEF_FUNC(SHORT,
			GetKeyState,(
			_In_ int nVirtKey));

		DEF_FUNC(HANDLE,
			GetStdHandle, (
			_In_ DWORD nStdHandle
			));

		DEF_FUNC(BOOL,
			GetConsoleCursorInfo,(
			_In_ HANDLE hConsoleOutput,
			_Out_ PCONSOLE_CURSOR_INFO lpConsoleCursorInfo
			));

		DEF_FUNC(BOOL,
			SetConsoleCursorInfo,(
			_In_ HANDLE hConsoleOutput,
			_In_ CONST CONSOLE_CURSOR_INFO *lpConsoleCursorInfo
			));

		DEF_FUNC(UINT,
			GetConsoleCP, (
			VOID
			));
		DEF_FUNC(BOOL,
			SetConsoleCP, (
			_In_ UINT wCodePageID
			));

		DEF_FUNC(BOOL,
			PeekConsoleInputW, (
			_In_ HANDLE hConsoleInput,
			_Out_writes_(nLength) PINPUT_RECORD lpBuffer,
			_In_ DWORD nLength,
			_Out_ LPDWORD lpNumberOfEventsRead
			));
		DEF_FUNC(UINT,
			GetConsoleOutputCP, (
			VOID
			));
		DEF_FUNC(BOOL,
			SetConsoleOutputCP, (
			_In_ UINT wCodePageID
			));
		DEF_FUNC(BOOL,
			SetConsoleTitleW, (
			_In_ LPCWSTR lpConsoleTitle
			));

		DEF_FUNC(BOOL,
			SetConsoleMode, (
			_In_ HANDLE hConsoleHandle,
			_In_ DWORD dwMode
			));
		DEF_FUNC(BOOL,
			SetConsoleCtrlHandler, (
			_In_opt_ PHANDLER_ROUTINE HandlerRoutine,
			_In_ BOOL Add
			));

	}
}