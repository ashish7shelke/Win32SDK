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
	TCHAR str[255] = TEXT("Hello World !!!");
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;

	//Code
	switch (iMsg)
	{
	case WM_PAINT: // OS sent whenever there Window repaint/redraw is needed. It is SW message
		// 8 Situation when OS wants to repaint window
		// 1) Window first time created and has to shown -> whole OS is responsible 
		// 2) Whenever we move window with caption bar -> whole OS is responsible
		// 3) Whenever window menu is requested, after menu disapper, repaint is done to redraw coverred area -> whole OS is responsible
		// 4) When draggin other window over window -> whole OS is responsible
		// 5) Whenever mouse cursor moved over window -> whole OS is responsible
		// 6) Resize -> Its developer responsibility
		// 7) Whenever window is covered by other window -> while uncovering window repaint is done -> Its developer responsibility
		// 8) Whenever window is scrolled -> Its developer responsibility
		// Developer cant send this message
		// With Win32 API developer can request for paint
		// UpdateWindow this msg sent - InvalidateRect function posts 
		// All HW event come through message loop. but SW messages not compulsary to come from message loop
		
		// Device context - structure to represent graphics device (GDI - Graphic Device Interface) is specialist to paint on window
		// HDC - HAndle to device context
		// There are 5 ways to get handle
		// 1) CreateDC 2) GetWindowDc 3) GetDc 4) CreateCompatibleDc 5) BeginPaint
		// 
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 255, 0));
		DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		//wsprintf(str, TEXT("WM_DESTROY Message is Received"));
		//MessageBox(hwnd, str, TEXT("Message"), MB_OK);
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
