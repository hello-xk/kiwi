
#include <QtCore/QCoreApplication>

// ��Ļ���������ScreenBufferScrollDemo
// ģ����Ļ������������£��Զ�������һ�����ݣ���������һ��
// ����ʹ��vs2005���ϰ汾���� unicode����
#include <windows.h> 
#include <iostream>
#include <tchar.h>
using std::wcout;
using std::endl;

int main(int argc, char* argv[])
{
    // �������
    std::wcout.imbue(std::locale("chs"));

    // ���ÿ���̨������
    SetConsoleTitle((LPCWSTR)_T("ScreenBufferScrollDemo"));

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) 
    {
        wcout << TEXT("GetStdHandle failed with ") << GetLastError() << endl; 
        return 1;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
    // Get the screen buffer size.
    if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo)) 
    {
        wcout << TEXT("GetConsoleScreenBufferInfo failed ") << GetLastError() << endl; 
        return 1;
    }

    SMALL_RECT srctScrollRect, srctClipRect; 
    COORD coordDest; 
    // The scrolling rectangle is the bottom 15 rows of the screen buffer.
    // ������֤�£���������С�ܴ����ҵĻ�������300��x80��
    srctScrollRect.Top = csbiInfo.dwSize.Y - 16; 
    srctScrollRect.Bottom = csbiInfo.dwSize.Y - 1; 
    srctScrollRect.Left = 0; 
    srctScrollRect.Right = csbiInfo.dwSize.X - 1; 

    // The destination for the scroll rectangle is one row up.
    coordDest.X = 0; 
    coordDest.Y = csbiInfo.dwSize.Y - 17; 

    // The clipping rectangle is the same as the scrolling rectangle. 
    // The destination row is left unchanged.
    srctClipRect = srctScrollRect; 

    // Fill the bottom row with green blanks. 
    CHAR_INFO chiFill; 
    chiFill.Attributes = BACKGROUND_GREEN | FOREGROUND_RED; 
    chiFill.Char.UnicodeChar = 'a'; 

    // Scroll up one line. 
    if(!ScrollConsoleScreenBuffer(  
        hStdout,         // screen buffer handle 
        &srctScrollRect, // scrolling rectangle 
        &srctClipRect,   // clipping rectangle 
        coordDest,       // top left destination cell 
        &chiFill))       // fill character and color
    {
        printf("ScrollConsoleScreenBuffer failed %d\n", GetLastError()); 
        return 1;
    }

    // ������ڳ����������˶�û����Ч�������鳢�������·���
    // �ڿ���̨����������������ֱ�������棬���������̵׺�ɫ��һ��a�ַ�
    system("pause");
s    return 0;
}