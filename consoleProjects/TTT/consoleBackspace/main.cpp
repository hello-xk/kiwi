
#include <QtCore/QCoreApplication>

#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h>

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
        WriteConsole(hOut, (LPCWSTR)"1", 1, &unused, &unused);
        //WriteConsoleOutputCharacter(hOut, (LPCWSTR)" ", 1, pos, &unused);
        //SetConsoleCursorPosition(hOut, pos);
    }
}

std::string getPassword()
{
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    INPUT_RECORD ir;
    DWORD unused;
    std::string ret;
    //if (! IsValidCodePage(65001))
    //{
    //    std::cout << "不支持UTF-8";
    //    system("pause");
    //    return "";
    //}
    //if (! SetConsoleCP(65001) )
    //{
    //    std::cout << "设置UTF-8失败";
    //    system("pause");
    //    return "";
    //}
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
                if (ir.Event.KeyEvent.uChar.UnicodeChar)
                {
                   // std::wcout.imbue(std::locale("chs"));
                   //std::wcout.imbue(std::locale(std::locale(),"",LC_CTYPE));
                   // _TCHAR* s1 = _T"我们";
                   // std::wcout << s1;
                   // std::wcout << 12345; //this will print 12,345，because imbue
                    WCHAR wStr = (WCHAR )ir.Event.KeyEvent.uChar.UnicodeChar;
                    int nCount = WideCharToMultiByte(CP_ACP, 0, &wStr, 1, NULL, 0, NULL, NULL); 
                    char *pStr = new char[nCount+1];  
                    nCount = WideCharToMultiByte(CP_ACP, 0, &wStr, 1, pStr, nCount, NULL, NULL); 
                    pStr[nCount] = '\0';
                    WriteConsole(hOut, (LPCWSTR)pStr, 1, &unused, &unused);
                    //std::cout << pStr << std::flush;
                    //std::wcout << ir.Event.KeyEvent.uChar.UnicodeChar << std::flush;
                }
                else if (isprint(ch))
                {
                    ret += ch;
                    std::cout << ch << std::flush;
                }
                else if (ch == '\b' && !ret.empty()) // Backspace
                {
                    //ret.pop_back();
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