
#include <QtCore/QCoreApplication>

// 屏幕缓冲滚动，ScreenBufferScrollDemo
// 模拟屏幕缓冲满的情况下，自动丢弃第一行数据，后续上移一行
// 建议使用vs2005以上版本编译 unicode编码
#include <windows.h> 
#include <iostream>
#include <tchar.h>
using std::wcout;
using std::endl;

int main(int argc, char* argv[])
{
    // 输出中文
    std::wcout.imbue(std::locale("chs"));

    // 设置控制台标题栏
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
    // 建议验证下，这个区域大小很大，在我的机器上是300行x80列
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

    // 如果你在程序运行完了都没看到效果，建议尝试下如下方法
    // 在控制台窗口拉动滚动条，直到最下面，看看有无绿底红色的一行a字符
    system("pause");
s    return 0;
}