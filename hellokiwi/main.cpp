//
//#include <QtCore/QCoreApplication>
//#include <QtGui/QApplication>
//
//#include "mainwindow.h"
//
////GNU GPL V2, 2015-02-07
//#include <QtGlobal>
//#include <windows.h>
//#define CONSOLE_COLUMNS 80
//#define CONSOLE_ROWS    5000
//#define YOURCONSOLETITLE "Your_Console_Title"
//#define WINBOOL int
//
//typedef struct{
//
//    CONSOLE_SCREEN_BUFFER_INFOEX conScreenBuffInfoEX;
//
//    HANDLE con_screenbuf;
//    HWND hwndConsole;
//    HMENU consoleMenu ;
//    QString consoleTitle;
//
//    QString localMsg;
//    QString errorMessage;
//    WINBOOL errorCode;
//
//} consoleT;
//
//static consoleT *console;
//
//BOOL WINAPI catchCTRL( DWORD ctrlMsg ){
//
//    if( ctrlMsg == CTRL_C_EVENT ){
//
//        HWND hwndWin = GetConsoleWindow();
//        ShowWindow(hwndWin,SW_FORCEMINIMIZE);
//    }
//
//    return TRUE;
//}
//
//void removeCloseMenu(){
//
//    int i;
//
//    for( i = 0; i < 10; i++){
//
//        console->hwndConsole = FindWindowW( NULL, console->consoleTitle.toStdWString().data());
//
//        if(console->hwndConsole != NULL)
//            break;
//    }
//
//    if( !(console->errorCode = 0) && (console->hwndConsole == NULL))
//        console->errorMessage += QString("\nFindWindowW error: %1 \n").arg(console->errorCode);
//
//    if( !(console->errorCode = 0) &&  !(console->consoleMenu = GetSystemMenu( console->hwndConsole, FALSE )) )
//        console->errorMessage += QString("GetSystemMenu error: %1 \n").arg(console->errorCode);
//
//    if(!(console->errorCode = DeleteMenu( console->consoleMenu, SC_CLOSE, MF_BYCOMMAND )))
//        console->errorMessage += QString("DeleteMenu error: %1 \n").arg(console->errorCode);
//}
//
//void initialiseConsole(){
//
//    console->conScreenBuffInfoEX.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
//    console->consoleMenu = NULL;
//    console->consoleTitle = YOURCONSOLETITLE;
//    console->con_screenbuf = INVALID_HANDLE_VALUE;
//    console->errorCode = 0;
//    console->errorMessage = "";
//    console->hwndConsole = NULL;
//    console->localMsg = "";
//
//    if(!(console->errorCode = FreeConsole()))
//        console->errorMessage += QString("\nFreeConsole error: %1 \n").arg(console->errorCode);
//
//    if(!(console->errorCode = AllocConsole()))
//        console->errorMessage += QString("\nAllocConsole error: %1 \n").arg(console->errorCode);
//
//    if( (console->errorCode = -1) && (INVALID_HANDLE_VALUE ==(console->con_screenbuf = CreateConsoleScreenBuffer( GENERIC_WRITE | GENERIC_READ,0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL))))
//        console->errorMessage += QString("\nCreateConsoleScreenBuffer error: %1 \n").arg(console->errorCode);
//
//    if(!(console->errorCode = SetConsoleActiveScreenBuffer(console->con_screenbuf)))
//        console->errorMessage += QString("\nSetConsoleActiveScreenBuffer error: %1 \n").arg(console->errorCode);
//
//    if(!(console->errorCode = GetConsoleScreenBufferInfoEx(console->con_screenbuf, &console->conScreenBuffInfoEX)))
//        console->errorMessage += QString("\nGetConsoleScreenBufferInfoEx error: %1 \n").arg(console->errorCode);
//
//    console->conScreenBuffInfoEX.dwSize.X = CONSOLE_COLUMNS;
//    console->conScreenBuffInfoEX.dwSize.Y = CONSOLE_ROWS;
//
//    if(!(console->errorCode = SetConsoleScreenBufferInfoEx(console->con_screenbuf, &console->conScreenBuffInfoEX)))
//        console->errorMessage += QString("\nSetConsoleScreenBufferInfoEx error: %1 \n").arg(console->errorCode);
//
//    if(!(console->errorCode = SetConsoleTitleW(console->consoleTitle.toStdWString().data())))
//        console->errorMessage += QString("SetConsoleTitle error: %1 \n").arg(console->errorCode);
//
//    SetConsoleCtrlHandler(NULL, FALSE);
//    SetConsoleCtrlHandler(catchCTRL, TRUE);
//
//    removeCloseMenu();
//
//    if(console->errorMessage.length() > 0){
//        //TODO errmsg
//    }
//
//}
//
////void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
////    if((console->con_screenbuf != INVALID_HANDLE_VALUE)){
////
////        switch (type) {
////
////        case QtDebugMsg:
////            console->localMsg = console->errorMessage + "Debug: " + msg;
////            WriteConsoleW(console->con_screenbuf, console->localMsg.toStdWString().data(), console->localMsg.toStdWString().length(), NULL, NULL );
////            WriteConsoleA(console->con_screenbuf, "\n--\n", 4, NULL, NULL );
////            break;
////
////        case QtWarningMsg:
////            console->localMsg = console->errorMessage + "Warning: " + msg;
////            WriteConsoleW(console->con_screenbuf, console->localMsg.toStdWString().data(), console->localMsg.toStdWString().length() , NULL, NULL );
////            WriteConsoleA(console->con_screenbuf, "\n--\n", 4, NULL, NULL );
////            break;
////
////        case QtCriticalMsg:
////            console->localMsg = console->errorMessage + "Critical: " + msg;
////            WriteConsoleW(console->con_screenbuf, console->localMsg.toStdWString().data(), console->localMsg.toStdWString().length(), NULL, NULL );
////            WriteConsoleA(console->con_screenbuf, "\n--\n", 4, NULL, NULL );
////            break;
////
////        case QtFatalMsg:
////            console->localMsg = console->errorMessage + "Fatal: " + msg;
////            WriteConsoleW(console->con_screenbuf, console->localMsg.toStdWString().data(), console->localMsg.toStdWString().length(), NULL, NULL );
////            WriteConsoleA(console->con_screenbuf, "\n--\n", 4, NULL, NULL );
////            abort();
////        }
////    }
////}
////
////
////
//
//
//#include <iostream>
//using namespace std;
//
//
//class Console : public QObject
//{
//public:
//	bool eventFilter(QObject *target, QEvent *event);
//};
//
//bool Console::eventFilter(QObject *target, QEvent *event)
//{
//	Q_UNUSED(target);
//	if (event->type() == QEvent::KeyPress)
//	{
//		printf("a");
//	}
//
//	return true;
//}

#include "kiwi.h"
#include "sigslot.h"
#include "cconsole.h"

class CConsole1
{
public:
	sigslot::signal2<char *, int> sig;
};

class Kiwi1 : public sigslot::has_slots<>
{
public:
	void on_sig(char * , int);
};

void Kiwi1::on_sig(char * a, int b)
{
	printf("Sig is OK");
}

int main(int argc, char **argv)
{
	argc;argv;
	//CConsole ccon;
	//Kiwi kiwi;
	//ccon.cmdline.connect(&kiwi, &Kiwi::on_cmdline);
	//ccon.cmdline("ok", 1);
	//system("pause");
	//return 0;

	CConsole ccon;
	Kiwi kiwi;
	ccon.cmdline.connect(&kiwi, &Kiwi::on_cmdline);
	return ccon.exec();
 }

