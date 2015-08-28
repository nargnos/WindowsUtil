#pragma once
#include <Microsoft\Win32\Win32Native.h>
//#include <boost\thread.hpp>
//#include <boost\throw_exception.hpp>
namespace Console
{
	using namespace Microsoft::Win32;

	class Console
	{
	public:
		
		Console();

		~Console();
		void Beep()
		{
			_Beep(800, 200);
		}
		void Beep(int frequency, int duration)
		{
			if ((frequency < 0x25) || (frequency > 0x7fff))
			{
				boost::throw_exception(std::exception("ArgumentOutOfRange"));
			}
			if (duration <= 0)
			{
				boost::throw_exception(std::exception("ArgumentOutOfRange")); 
			}
			_Beep(frequency, duration);
		}
		void SetColor(BYTE color)
		{
			defaultColors = color;
		}
		WORD GetColor()
		{
			return defaultColors;
		}
		bool BreakEvent(int controlType)
		{
			//threadPool.create_thread(BreakEvent);
			return false; 
		}
		void Clear()
		{
			COORD dwWriteCoord = { 0 };
			if (consoleOutputHandle == INVALID_HANDLE_VALUE)
			{
				boost::throw_exception(std::exception("INVALID_HANDLE_VALUE"));
			}
			CONSOLE_SCREEN_BUFFER_INFO bufferInfo = GetBufferInfo();
			int nLength = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;
			DWORD pNumCharsWritten = 0;
			if (!_FillConsoleOutputCharacterW(consoleOutputHandle, ' ', nLength, dwWriteCoord, &pNumCharsWritten))
			{
				boost::throw_exception(std::exception("WinIOError"));
			}
			pNumCharsWritten = 0;
			if (!_FillConsoleOutputAttribute(consoleOutputHandle, bufferInfo.wAttributes, nLength, dwWriteCoord, &pNumCharsWritten))
			{
				boost::throw_exception(std::exception("WinIOError"));
			}
			if (!_SetConsoleCursorPosition(consoleOutputHandle, dwWriteCoord))
			{
				boost::throw_exception(std::exception("WinIOError"));
			}
		}
		void MoveBufferArea(int sourceLeft, int sourceTop, int sourceWidth, int sourceHeight, int targetLeft, int targetTop)
		{
			MoveBufferArea(sourceLeft, sourceTop, sourceWidth, sourceHeight, targetLeft, targetTop, ' ', 0xfff0& defaultColors);
		}

		
		void MoveBufferArea(int sourceLeft, int sourceTop, int sourceWidth, int sourceHeight, int targetLeft, int targetTop, char sourceChar,  BYTE color)
		{
			
			COORD dwSize = GetBufferInfo().dwSize;
			if ((sourceLeft < 0) || (sourceLeft > dwSize.X))
			{
				boost::throw_exception(std::exception("sourceLeft"));
			}

			if ((sourceTop < 0) || (sourceTop > dwSize.Y))
			{
				boost::throw_exception(std::exception("sourceTop"));
			}
			if ((sourceWidth < 0) || (sourceWidth >(dwSize.X - sourceLeft)))
			{
				boost::throw_exception(std::exception("sourceWidth"));
			}
			if ((sourceHeight < 0) || (sourceTop >(dwSize.Y - sourceHeight)))
			{
				boost::throw_exception(std::exception("sourceHeight"));
			}
			if ((targetLeft < 0) || (targetLeft > dwSize.X))
			{
				boost::throw_exception(std::exception("targetLeft"));
			}
			if ((targetTop < 0) || (targetTop > dwSize.Y))
			{
				boost::throw_exception(std::exception("targetTop"));
			}
			if ((sourceWidth != 0) && (sourceHeight != 0))
			{
				bool flag;
				DWORD char_infoArraySize = sourceWidth * sourceHeight;
				PCHAR_INFO char_infoArray = new CHAR_INFO[char_infoArraySize];
				dwSize.X = (SHORT)sourceWidth;
				dwSize.Y = (SHORT)sourceHeight;
				COORD bufferCoord;
				SMALL_RECT readRegion;
				readRegion.Left = (SHORT)sourceLeft;
				readRegion.Right = (SHORT)((sourceLeft + sourceWidth) - 1);
				readRegion.Top = (SHORT)sourceTop;
				readRegion.Bottom = (SHORT)((sourceTop + sourceHeight) - 1);

				flag = _ReadConsoleOutputW(consoleOutputHandle, char_infoArray, dwSize, bufferCoord,&readRegion);
				
				if (!flag)
				{
					boost::throw_exception(std::exception("WinIOError"));
				}
				COORD dwWriteCoord;
				dwWriteCoord.X = (WORD)sourceLeft;

				//Win32Native.Color color = (Win32Native.Color) ((short)(ConsoleColorToColorAttribute(sourceBackColor, true) | ConsoleColorToColorAttribute(sourceForeColor, false)));
				WORD wColorAttribute = (WORD)color;
				for (int i = sourceTop; i < (sourceTop + sourceHeight); i++)
				{
					DWORD num2;
					dwWriteCoord.Y = (short)i;
					if (!_FillConsoleOutputCharacterW(consoleOutputHandle, sourceChar, sourceWidth, dwWriteCoord, &num2))
					{
						boost::throw_exception(std::exception("WinIOError"));
					}
					if (!_FillConsoleOutputAttribute(consoleOutputHandle, wColorAttribute, sourceWidth, dwWriteCoord, &num2))
					{
						boost::throw_exception(std::exception("WinIOError"));
					}
				}
				SMALL_RECT writeRegion;
				writeRegion.Left = (WORD)targetLeft;
				writeRegion.Right = (WORD)(targetLeft + sourceWidth);
				writeRegion.Top = (WORD)targetTop;
				writeRegion.Bottom = (WORD)(targetTop + sourceHeight);
				auto char_infoRef2 = char_infoArray;
				if (char_infoArray == NULL || char_infoArraySize == 0)
				{
					char_infoRef2 = NULL;
				}
				flag = _WriteConsoleOutputW(consoleOutputHandle, char_infoRef2, dwSize, bufferCoord, &writeRegion);

				delete[] char_infoArray; 

			}
			
		}

		/*Stream OpenStandardError()
		{
			return OpenStandardError(0x100);
		}

		Stream OpenStandardError(int bufferSize)
		{
			if (bufferSize < 0)
			{
				return NULL;
			}
			return GetStandardFile(-12, FileAccess.Write, bufferSize);
		}*/

	private:
		boost::thread_group threadPool;
		HANDLE consoleInputHandle;
		HANDLE consoleOutputHandle;
		HANDLE consoleOutErrHandle;

		BYTE defaultColors;
		const INT DefaultConsoleBufferSize = 0x100;
		int haveReadDefaultColors;
		bool wasErrorRedirected;
		bool wasOutRedirected;
		const INT CapsLockVKCode = 20;
		const INT MaxBeepFrequency = 0x7fff;
		const INT MaxConsoleTitleLength = 0x5fb4;
		const INT MinBeepFrequency = 0x25;
		const INT NumberLockVKCode = 0x90;
		CONSOLE_SCREEN_BUFFER_INFO GetBufferInfo(bool throwOnNoConsole, OUT bool succeeded)
		{
			
		}
		CONSOLE_SCREEN_BUFFER_INFO GetBufferInfo()
		{
			bool flag;
			return GetBufferInfo(true, flag);
		}
		bool ConsoleHandleIsWritable(HANDLE outErrHandle)
		{
			DWORD num;
			byte bytes = 0x41;
			return (_WriteFile(outErrHandle, &bytes, 0, &num, NULL) != 0);
		}
		void ControlCDelegate(PVOID data){}

		bool IsAltKeyDown(INPUT_RECORD& ir)
		{
			return ((ir.Event.KeyEvent.dwControlKeyState & (RIGHT_ALT_PRESSED | LEFT_ALT_PRESSED)) != 0);
		}

		bool IsHandleRedirected(HANDLE ioHandle)
		{
			DWORD num2;
			return (((_GetFileType(ioHandle) & 2) != 2) || !_GetConsoleMode(ioHandle, &num2));
		}


		bool IsKeyDownEvent(INPUT_RECORD& ir)
		{
			return ((ir.EventType == KEY_EVENT) && ir.Event.KeyEvent.bKeyDown);
		}


		bool IsModKey(INPUT_RECORD& ir)
		{
			WORD virtualKeyCode = ir.Event.KeyEvent.wVirtualKeyCode;
			if (((virtualKeyCode < 0x10) || (virtualKeyCode > 0x12)) && ((virtualKeyCode != 20) && (virtualKeyCode != 0x90)))
			{
				return (virtualKeyCode == 0x91);
			}
			return true;
		}


	};

}