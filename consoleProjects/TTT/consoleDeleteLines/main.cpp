
#include <QtCore/QCoreApplication>
#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h>

//row start with 0
void DeleteLine(int row)  
{  
    SMALL_RECT  rcScroll, rcClip;  
    COORD       crDest = {0, 8};  //������λ��
    CHAR_INFO   chFill;  

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;  
    GetConsoleScreenBufferInfo(hOut, &bInfo );     // ��ȡ����̨��Ϣ  

    rcScroll.Left =0;  
    rcScroll.Right = 20;  
    rcScroll.Top = 4;  
    rcScroll.Bottom = 4;           // ����Ҫ����������  

    rcClip = rcScroll;                              // ���òü�����  
    rcClip.Left = 0;
    rcClip.Right = 2;
    rcClip.Top = 5;
    rcClip.Bottom = 9;

    chFill.Attributes = bInfo.wAttributes;  
    //chFill.Char.AsciiChar = ' ';                    // ����Ҫ�����ı�������  

    ScrollConsoleScreenBuffer(hOut, &rcScroll, NULL, crDest, &chFill);  
    //���
    //�������ƶ�������
    //�ü�����
    //����������
    //����ַ���������ԭ���Ŀռ������ַ���
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

