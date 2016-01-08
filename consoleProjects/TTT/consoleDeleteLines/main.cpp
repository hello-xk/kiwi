
#include <QtCore/QCoreApplication>
#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h>

//row start with 0
void DeleteLine(int row)  
{  
    SMALL_RECT  rcScroll, rcClip;  
    COORD       crDest = {0, 8};  //滚动到位置
    CHAR_INFO   chFill;  

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;  
    GetConsoleScreenBufferInfo(hOut, &bInfo );     // 获取控制台信息  

    rcScroll.Left =0;  
    rcScroll.Right = 20;  
    rcScroll.Top = 4;  
    rcScroll.Bottom = 4;           // 设置要滚动的区域  

    rcClip = rcScroll;                              // 设置裁剪区域  
    rcClip.Left = 0;
    rcClip.Right = 2;
    rcClip.Top = 5;
    rcClip.Bottom = 9;

    chFill.Attributes = bInfo.wAttributes;  
    //chFill.Char.AsciiChar = ' ';                    // 设置要填充的文本和属性  

    ScrollConsoleScreenBuffer(hOut, &rcScroll, NULL, crDest, &chFill);  
    //句柄
    //滚动或移动的区域
    //裁剪区域
    //滚动到坐标
    //填充字符（滚动后原本的空间填充的字符）
}  

int main(int argc, char *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            printf("%d", i);
        }
        printf("\n");
    }
    printf("start to delete the line 5");
    system("pause");
    DeleteLine(5);
    system("pause");
}

