//Header Files
#include <windows.h>

#include "Window.h"
//Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

/*
* Though looks nothing inside function, following 3 things are there
* Function calling convention:
* 1) Where to keep this function in memory
* 2) If function has 2 or more than 2 parameters, how to pass them as left to right OR right to left 
*	Little Endian / Big Endian
*/

//Global Variable Declarations
#define ID_NUMBERS 5001

//Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Local Variable Declarations
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");

	//Code

	//WNDCLASS Initialization
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//Registration of WndClassEx
	RegisterClassEx(&wndClass);

	//Creating the Window
	hwnd = CreateWindow(szAppName,
						TEXT("AGS"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);

	//Show Window
	ShowWindow(hwnd, iCmdShow);

	//Update the Window
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//Local Variable Declarations
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;


	//Code
	switch (iMsg)
	{
	case WM_CHAR:
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is my Message Box"), TEXT("Message"), MB_OK);
		break;

	case WM_CREATE:
		hThread1 = CreateThread(	NULL, //Security attributes
								0, // Size of thread stack = size of process stack
								(LPTHREAD_START_ROUTINE)ThreadProcOne, 
								(LPVOID)hwnd, //Thread function parameters
								0, 
								NULL);

		hThread2 = CreateThread(	NULL, //Security attributes
								0, // Size of thread stack = size of process stack
								(LPTHREAD_START_ROUTINE)ThreadProcTwo, 
								(LPVOID)hwnd, //Thread function parameters
								0, 
								NULL);
		break;

	case WM_TIMER:
		break;

	case WM_PAINT: // OS sent whenever there Window repaint/redraw is needed. It is SW message
		break;

	case WM_DESTROY:
		PostQuitMessage(0); //On runtime process text memory doesnt overwritten
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
	//Varaible declarations
	HDC hdc;
	TCHAR str[255];
	LONG i;

	//Code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 0));

	for(i = 0; i < 32767; i++)
	{
		wsprintf(str, TEXT("Numbers in Increamenting Order : %d"), i);
		TextOut(hdc, 10, 5, str, wcslen((wchar_t *)str));
	}
	ReleaseDC((HWND)param, hdc);

	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	//Varaible declarations
	HDC hdc;
	TCHAR str[255];
	INT i;

	//Code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(255, 255, 255));
	SetTextColor(hdc, RGB(0, 255, 255));

	for(i = 32767; i > 0; i--)
	{
		wsprintf(str, TEXT("Numbers in Decrementing Order : %d"), i);
		TextOut(hdc, 10, 25, str, wcslen((wchar_t *)str));
	}
	ReleaseDC((HWND)param, hdc);

	return 0;
}

//Commands: 
// cl.exe /c /EHsc Window.cpp
// cl.exe /c /EHsc /D UNICODE Window.cpp
// link.exe Window.obj user32.lib gdi32.lib /subsystem:WINDOWS
