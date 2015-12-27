#include "cconsole.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>

//disable strncpy warning
#pragma warning (disable: 103)
#pragma warning (disable: 111)
#pragma warning (disable: 139)

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

#define KIWI_BACKSPACE	do{	if(m_len){putchar('\b');putchar(' ');putchar('\b');m_len-=1;} }while(0)

#define KIWI_NEWLINE do{ printf("\n");KIWI$; }while(0)
#define KIWI_DELLINE do{ for(int i = 0, size = m_len; i < size; ++i){ KIWI_BACKSPACE; } }while(0)

#define KIWI_AUTO_CMD(cmd) do{\
	for(int i = 0, size = m_len; i < size; ++i) { KIWI_BACKSPACE; }\
	printf("%s", cmd);\
	m_len += (strlen(cmd) > CConsole_MAX_LINE ? CConsole_MAX_LINE : strlen(cmd));\
	strncpy(m_buf, cmd, m_len);\
}while(0)

#define KIWI_ADD_CMDLINE_TO_HISTORY do {\
	if (m_len > 512) {\
		m_histories[m_origin] ? delete[] m_histories[m_origin] : 1==1;\
		m_histories[m_origin] = new char[CConsole_MAX_LINE+1];\
	}\
	strncpy(m_histories[m_origin], m_buf, m_len);\
	m_histories[m_origin][m_len] = '\0';\
	m_origin = (m_origin == CConsole_MAX_HISTORY-1 ? 0 : m_origin+1);\
	m_index = m_origin;\
}while (0)

#define KIWI_DUMP_HISTORY do {\
	for(int i = 0; i < CConsole_MAX_HISTORY; ++i) { if(m_histories[i][0]){printf("%s\n", m_histories[i]);} }\
}while(0)

#define KIWI_HISTORY_PREV do {\
	m_index = m_index == 0 ? CConsole_MAX_HISTORY-1 : m_index-1;\
	if (m_histories[m_index][0]) { KIWI_AUTO_CMD(m_histories[m_index]); }\
	else { m_index = m_index == CConsole_MAX_HISTORY-1 ? 0 : m_index+1; }\
}while(0)

#define KIWI_HISTORY_NEXT do {\
	m_index = m_index == CConsole_MAX_HISTORY-1 ? 0 : m_index+1;\
	if (m_histories[m_index][0]) { KIWI_AUTO_CMD(m_histories[m_index]); }\
	else { m_index = m_index == 0 ? CConsole_MAX_HISTORY-1 : m_index-1; }\
}while(0)

CConsole::CConsole()
: m_len(0)
, m_origin(0)
, m_index(0)
{
	for (int i = 0; i < CConsole_MAX_HISTORY; ++i)
	{
		m_histories[i] = new char[512+1];
		m_histories[i][0] = '\0';
	}
}

CConsole::~CConsole()
{
	for (int i = 0; i < CConsole_MAX_HISTORY; ++i)
	{
		if (m_histories[i])
		{
			delete[] m_histories[i];
			m_histories[i] = '\0';
		}
	}
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
			if (m_len > CConsole_MAX_LINE)
			{
				printf("command buffer full\n");
				break;
			}
			m_buf[m_len] = ch;
			m_len += 1;	
			break;
		case '\b': 
			KIWI_BACKSPACE;
			break;
		case 10:
		case 13:
			if (m_len) 
			{
				KIWI_ADD_CMDLINE_TO_HISTORY;
				putchar('\n');
				m_buf[m_len] = '\0';
				if (strncmp(m_buf, "history", strlen("history")) == 0)
				{
					KIWI_DUMP_HISTORY;
				} 
				else 
				{
					cmdline.emit(m_buf, m_len);
				}
			}
			KIWI_NEWLINE;
			break;
		case KEY_ASCII_ESC:
			KIWI_AUTO_CMD("exit");
			break;
		case KEY_ASCII_CTRL_C:
			puts("ctrl+C");
			break;
		case KEY_ASCII_CTRL_BACKSPACE:
			KIWI_DELLINE;
			break;
		case KEY_ASCII_TAB:
			puts("tabs");
			break;
		case KEY_32:
			ch = _getch();
			switch (ch)
			{
			case KEY_ASCII_DEL:puts("del");break;
			case KEY_ASCII_UP: KIWI_HISTORY_PREV;break;
			case KEY_ASCII_DOWN:KIWI_HISTORY_NEXT;break;
			case KEY_ASCII_LEFT:putchar('\b');break;
			case KEY_ASCII_RIGHT:puts("right");break;
			}
			break;

		case KEY_0:
			ch = _getch();
			switch(ch)
			{
			case KEY_ASCII_ALT_F4:
				KIWI_AUTO_CMD("exit");
				break;
			}
			break;
		}
	}
	return 0;
}