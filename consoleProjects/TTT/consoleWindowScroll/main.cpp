
#include <QtCore/QCoreApplication>

#include <windows.h>
#include <stdio.h>
#include <conio.h>

HANDLE hStdout; 

//向上移动Rows，相对于0,0坐标而言，相对于buffer开始而言
int ScrollByAbsoluteCoord(int iRows)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	SMALL_RECT srctWindow; 

	// Get the current screen buffer size and window position. 

	if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo)) 
	{
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError()); 
		return 0;
	}

	// Set srctWindow to the current window size and location. 

	srctWindow = csbiInfo.srWindow; //可视窗口相对于buffer(0,0,x,y)的坐标

	// Check whether the window is too close to the screen buffer top

	if ( srctWindow.Top >= iRows ) 
	{ 
		srctWindow.Top -= (SHORT)iRows;     // move top up
		srctWindow.Bottom -= (SHORT)iRows;  // move bottom up

		if (! SetConsoleWindowInfo( 
			hStdout,          // screen buffer handle 
			TRUE,             // absolute coordinates 绝对坐标
			&srctWindow))     // specifies new location 
		{
			printf("SetConsoleWindowInfo (%d)\n", GetLastError()); 
			return 0;
		}
		return iRows;
	}
	else
	{
		printf("\nCannot scroll; the window is too close to the top.\n");
		return 0;
	}
}

//向上移动Rows，相对于当前位置而言
int ScrollByRelativeCoord(int iRows)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	SMALL_RECT srctWindow; 

	// Get the current screen buffer window position. 

	if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo)) 
	{
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError()); 
		return 0;
	}

	// Check whether the window is too close to the screen buffer top

	if (csbiInfo.srWindow.Top >= iRows) 
	{ 
		srctWindow.Top =- (SHORT)iRows;     // move top up
		srctWindow.Bottom =- (SHORT)iRows;  // move bottom up 
		srctWindow.Left = 0;         // no change 
		srctWindow.Right = 0;        // no change 

		if (! SetConsoleWindowInfo( 
			hStdout,          // screen buffer handle 
			FALSE,            // relative coordinates 非绝对坐标，即相对坐标
			&srctWindow))     // specifies new location 
		{
			printf("SetConsoleWindowInfo (%d)\n", GetLastError()); 
			return 0;
		}
		return iRows;
	}
	else
	{
		printf("\nCannot scroll; the window is too close to the top.\n");
		return 0;
	}
}

int main( void )
{
	int i;

	printf("\nPrinting twenty lines, then scrolling up five lines.\n");
	printf("Press any key to scroll up ten lines; ");
	printf("then press another key to stop the demo.\n");
	for(i=0; i<=20; i++)
		printf("%d\n", i);

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 

	system("pause");
	if(ScrollByAbsoluteCoord(5))
		_getch();
	else 
	{
		system("pause");
		return 0;
	}

	system("pause");
	if(ScrollByRelativeCoord(10))
		_getch();
	else
	{
		system("pause");
		return 0;
	}
}
