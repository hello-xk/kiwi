#pragma once

#define SIGSLOT_PURE_ISO
#include "sigslot.h"

#define CConsole_MAX_LINE	(2048)

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
	char m_buf[CConsole_MAX_LINE];
	int m_len;
};
