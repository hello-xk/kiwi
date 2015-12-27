#pragma once

//use sigslot default setting 
//use SIGSLOT_PURE_ISO cause compile failed when connect
#include "sigslot.h"

#define CConsole_MAX_LINE (2048)
#define CConsole_MAX_HISTORY (100)

class CConsole
{
public:
	CConsole();
	~CConsole();
	int exec();

	/*
	 * CConsole ccon;
	 * ccon.cmdline.connect(&handler, &handler::onCmdline);
	 */
	sigslot::signal2<char *, int> cmdline;
	
private:
	char m_buf[CConsole_MAX_LINE+1];
	int m_len;

	char* m_histories[CConsole_MAX_HISTORY];
	int m_origin;
	int m_index;
};
