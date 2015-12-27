#include "kiwi.h"

Kiwi::Kiwi()
{

}

Kiwi::~Kiwi()
{

}

void Kiwi::on_cmdline(char *cmd, int len)
{
	if (strncmp(cmd, "exit", strlen("exit")) == 0)
	{
		exit(0);
	}
	else if (strncmp(cmd, "clear", strlen("clear")) == 0)
	{
		system("cls");
		return;
	}
	system(cmd);
}