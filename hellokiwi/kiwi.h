#pragma once

#include "sigslot.h"
#include <QObject>

class Kiwi : public QObject, public sigslot::has_slots<>
{
	Q_OBJECT

public:
	Kiwi();
	~Kiwi();

//sigslot
public:
	void on_cmdline(char *cmd, int len);
};