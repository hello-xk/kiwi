
#include <QtCore/QCoreApplication>

#include <iostream>
#include <string>
#include <windows.h>

std::string getPassword();

int main()
{
	std::cout << "Enter your password: ";
	std::string password = getPassword();
	std::cout << "\nOkay, your password was: " << password;
	std::cout << "\nJust to make sure everything still works, "
		"enter something: ";
	std::string other;
	std::getline(std::cin, other);
	std::cout << "Okay, you entered: " << other;
}

void doBackspace()
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if ((hOut = GetStdHandle(STD_OUTPUT_HANDLE)) &&
		GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		COORD pos = csbi.dwCursorPosition; // Get current position
		// Get position of last character
		if (pos.X > 0)
			--pos.X;
		else if (pos.Y > 0)
		{
			--pos.Y;
			pos.X = csbi.dwSize.X - 1;
		}
		// Overwrite that character with a space and move the cursor back
		DWORD unused;
		WriteConsoleOutputCharacter(hOut, (LPCWSTR)" ", 1, pos, &unused);
		SetConsoleCursorPosition(hOut, pos);
	}
}

void doLeft()
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if ((hOut = GetStdHandle(STD_OUTPUT_HANDLE)) &&
		GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		COORD pos = csbi.dwCursorPosition; // Get current position
		// Get position of last character
		if (pos.X > 0)
			--pos.X;
		else if (pos.Y > 0)
		{
			--pos.Y;
			pos.X = csbi.dwSize.X - 1;
		}
		// Overwrite that character with a space and move the cursor back
		//DWORD unused;
		//WriteConsoleOutputCharacter(hOut, (LPCWSTR)" ", 1, pos, &unused);
		SetConsoleCursorPosition(hOut, pos);
	}
}

void doRight()
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if ((hOut = GetStdHandle(STD_OUTPUT_HANDLE)) &&
		GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		COORD pos = csbi.dwCursorPosition; // Get current position
		// Get position of last character
		if (pos.X > 0)
			++pos.X;
		else if (pos.Y > 0)
		{
			--pos.Y;
			pos.X = csbi.dwSize.X - 1;
		}
		// Overwrite that character with a space and move the cursor back
		//DWORD unused;
		//WriteConsoleOutputCharacter(hOut, (LPCWSTR)" ", 1, pos, &unused);
		SetConsoleCursorPosition(hOut, pos);
	}
}


std::string getPassword()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir;
	DWORD unused;
	std::string ret;
	while (ReadConsoleInput(hIn, &ir, 1, &unused)) // Get key press
	{
		if (ir.EventType == KEY_EVENT)
		{
			DWORD keyState = ir.Event.KeyEvent.dwControlKeyState;
			if (ir.Event.KeyEvent.bKeyDown == TRUE &&
				(keyState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED |
				LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED)) == 0)
			{
				char ch = ir.Event.KeyEvent.uChar.AsciiChar;
				char scankey = ir.Event.KeyEvent.wVirtualScanCode;
				if (isprint(ch))
				{
					ret += ch;
					std::cout << '*' << std::flush;
				}
				else if (scankey == 75)
				{
					doLeft();
				}
				else if (scankey == 77)
				{
					doRight();
				}
				else if (ch == '\b' && !ret.empty()) // Backspace
				{
					ret.push_back(ch);
					doBackspace();
				}
				else if (ch == '\r' || ch == '\n') // Newline -- end of input
				{
					std::cout << std::endl;
					break;
				}
			}
		}
	}
	return ret;
}

