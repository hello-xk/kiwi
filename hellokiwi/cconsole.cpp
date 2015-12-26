#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "cconsole.h"

#define KEY_ASCII_ESC			(27)
#define KEY_ASCII_TAB			(9)
#define KEY_ASCII_CTRL_C	(3)
#define KEY_ASCII_CTRL_BACKSPACE		(127)

//start with -32
#define KEY_32						(-32)
#define KEY_ASCII_DEL			(83)
#define KEY_ASCII_UP				(72)
#define KEY_ASCII_DOWN		(80)
#define KEY_ASCII_LEFT			(75)
#define KEY_ASCII_RIGHT		(77)

//start with 0
#define KEY_0							(0)
#define KEY_ASCII_ALT_F4		(107)

#define KIWI$ do{ printf("kiwi$ ");m_len=0; }while(0)
#define KIWI_NEWLINE	do{ printf("\n");KIWI$; }while(0)

#define KIWI_BACKSPACE	do{\
	if(m_len) {\
	putchar('\b');putchar(' ');putchar('\b');m_len-=1;\
	} }while(0)

#define KIWI_AUTO_CMD(cmd) do{\
	for(int i = 0, size = m_len; i < size; ++i) {\
	KIWI_BACKSPACE;\
	}\
	printf(cmd);m_len+=strlen(cmd);\
 }while(0)

CConsole::CConsole()
: m_len(0)
{

}

CConsole::~CConsole()
{

}

int CConsole::exec()
{
	puts("Welcome Kiwi [Version v0.01]\n");
	KIWI$;

	while(1)
	{
		char ch = _getch();	
		switch (ch)
		{
		default:
			putchar(ch);
			m_len += 1;	
			break;
		case '\b': 
			KIWI_BACKSPACE;
			break;
		case 10:
			cmdline.emit(m_buf, m_len);
			KIWI_NEWLINE;
			break;
		case 13:
			cmdline.emit(m_buf, m_len);
			KIWI_NEWLINE;
			break;
		case KEY_ASCII_ESC:
			KIWI_AUTO_CMD("exit");
			break;
		case KEY_ASCII_CTRL_C:
			puts("ctrl+C");
			break;
		case KEY_ASCII_CTRL_BACKSPACE:
			puts("ctrl+backspace");
			break;
		case KEY_ASCII_TAB:
			puts("tabs");
			break;
		case KEY_32:
			ch = _getch();
			switch (ch)
			{
			case KEY_ASCII_DEL:puts("del");break;
			case KEY_ASCII_UP: puts("up");break;
			case KEY_ASCII_DOWN:puts("down");break;
			case KEY_ASCII_LEFT:puts("left");break;
			case KEY_ASCII_RIGHT:puts("right");break;
			}
			break;

		case KEY_0:
			ch = _getch();
			switch(ch)
			{
			case KEY_ASCII_ALT_F4:puts("alt+F4");break;
			}
			break;
		}
	}
	return 0;
}