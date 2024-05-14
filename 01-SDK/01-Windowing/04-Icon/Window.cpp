//Header Files
#include <windows.h>
#include "Window.h"
//Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
* Though looks nothing inside function, following 3 things are there
* Function calling convention:
* 1) Where to keep this function in memory
* 2) If function has 2 or more than 2 parameters, how to pass them as left to right OR right to left 
*	Little Endian / Big Endian
*/

//Global Variable Declarations

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
	TCHAR str[255];

	//Code
	switch (iMsg)
	{
	case WM_CREATE:
		wsprintf(str, TEXT("WM_CREATE Message is Received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;

	case WM_KEYDOWN:
		wsprintf(str, TEXT("WM_KEYDOWN Message is Received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;

	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("WM_LBUTTONDOWN Message is Received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;

	case WM_RBUTTONDOWN:
		wsprintf(str, TEXT("WM_RBUTTONDOWN Message is Received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;

	/*case WM_SETFOCUS:
		wsprintf(str, TEXT("WM_SETFOCUS Message is Received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;

	case WM_KILLFOCUS:
		wsprintf(str, TEXT("WM_KILLFOCUS Message is Received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;*/

	case WM_DESTROY:
		wsprintf(str, TEXT("WM_DESTROY Message is Received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		//PostQuitMessage(0); //On runtime process text memory doesnt overwritten
		// Thats why text is shared between multiple process.
		PostMessage(hwnd, WM_QUIT, 0, 0L);
		//Almost all with few exceptions Win32API can be sent/post by using Post and Send message function
		//WM_QUIT is SW message that is posted and sent
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

//Commands: 
// cl.exe /c /EHsc Window.cpp
// cl.exe /c /EHsc /D UNICODE Window.cpp
// link.exe Window.obj user32.lib gdi32.lib /subsystem:WINDOWS
