// testsigslot.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "sigslot.h"

//using namespace sigslot;

class CConsole
{
public:
	sigslot::signal2<char *, int> sig;
};

class Kiwi : public sigslot::has_slots<>
{
public:
	void on_sig(char * , int);
};

void Kiwi::on_sig(char * a, int b)
{
	printf("Sig is OK");
}

int _tmain(int argc, _TCHAR* argv[])
{

	CConsole ccon;
	Kiwi kiwi;
	ccon.sig.connect(&kiwi, &Kiwi::on_sig);
	ccon.sig("ok", 1);
	system("pause");
	return 0;
}

