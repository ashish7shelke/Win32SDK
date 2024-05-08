//Header Files
#include <windows.h>

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

// int main(int argc, char *argv[], char *envp[]);
// int main(int argc, char* argv[], char* envp[]);
// int wmain(int argc, wchar_t* argv[], wchar_t* envp[]);

//Entry Point Function
/*
	HINSTANCE hInstance 		->	H stands for handle - 32 bit unsigned int - unique integer
			-> Process  - Execution Unit - It has PId (Process Identifier)
			-> Process has 4 stages - Creation, Execution, Suspension, Termination
			-> Program has 2 sections - Source code has Instructions(Operations) & Data 
										This source code is divided into 2 sections
										1) Text (Instruction) 2) Data - inside Obj file
			-> PID Process is created and it executes methods/ procedures/ function in *.exe program
			-> Programs is executed in Memory i.e Stack
			-> Running program in memory with stack is called Process.

			-> Multiple instances of same program, OS created different processes
			-> Program is stored in secondary storage device and always runs on primary memory RAM
			-> Loader loads *.exe to RAM
			-> Program needs free electronic space to get executed
			->   -------------------
			->	|		STACK		|
			->   -------------------
			->	|		DATA		|
			->   -------------------
			-> 	|		TEXT		|
			-> 	 -------------------
			-> If multiple instance of program then TEXT section has similar data DATA & STACK is different
			-> In multiple instance TEXT data is wasting in duplicating TEXT.
			-> If TEXT is kept common memory can be saved -> TEXT is shared among multiple instance on program.
			-> In WINDOW, when processes shares TEXT section each process is called as Instance
			-> Instance is terminology brought in Window OS.

	HINSTANCE hPrevInstance 	-> Instance before present instance is called as PrevInstance - This parameter is kept till now for backward compatibility
								-> After Windows 3.1 (1993) hPrevInstance is always NULL -> As Window became multitasking, multithreading, multiuser
								-> From 80286 CPU multitasking is enabled as memory protection unit feature enabled
								-> Windows before Window 3.1 are single tasking or real mode OS
								-> To make Window enable with multitasking on real mode HW, SW multi tasking/ threading emulation (Cooperative multitasking / SW multi tasking)
								-> For this Windows created DPMI (Dos Protected Memory Interface) - SW enabled virtual protected mode
								-> It feels multitasking, actually not on actual HW.
								-> After 1993 Preemptive Multitasking is enabled - OS dictates multitasking

	LPSTR lpszCmdLine 			-> Command Line Arguments - wchar_t* argv[]
	int iCmdShow 				-> Window Size option - Default - SW_NORMAL

	return value	-> 0, -1 Erronious Exit Error, +1 Abortive exit status

	WINAPI -> #define strict
			-> Where to keep in memory 
			-> How to pass parameters to function
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Local Variable Declarations
	WNDCLASSEX wndClass; // Window Class Extended (12 Member)
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");

	//Code

	//WNDCLASS Initialization
	wndClass.cbSize = sizeof(WNDCLASSEX); // Count of Bytes size to be allocated to class
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // CS - Class Size | Horizontal Re Draw | Vertical Redraw
	wndClass.cbClsExtra = 0; // Extra information of class in count of bytes
	wndClass.cbWndExtra = 0; // Extra information of window in counts of window
	wndClass.lpfnWndProc = WndProc; // Callback function to Window Procedure (long pointer)
	wndClass.hInstance = hInstance; // Handle of current instance provided by cmd as WinMain parameter
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // Handle of brush - Handle to Graphic Device Interface Object (HGDIOBJ)GetStockObject() can give Brush, Pen or Font handle
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Handle of Icon - Default System Icon, 1st Param - Instance Handle, when we have own icon then pass hInstance otherwise Pass NULL so OS provides default icon
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Handle to Cursor - Default system Cursor
	wndClass.lpszClassName = szAppName; // Predefined Window Class Name or Custom name
	wndClass.lpszMenuName = NULL; // If menu then pass otherwise NULL
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Small Icon Handle for explorer 

	//Registration of WndClassEx
	RegisterClassEx(&wndClass); // Register custom window class, return value unique un-mutable string called as Atom

	//Creating the Window
	hwnd = CreateWindow(szAppName,		//Window name, here it is custom windoe name. Predifined window can be used as dialogue box
						TEXT("AGS"),	// Windows caption bar text e.g. Notepad. TEXT convert normal text to unicode
						WS_OVERLAPPEDWINDOW, //This window will be on top of the screen
											 /// WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE
						CW_USEDEFAULT,		// Rectangle Left TOP X - Default 
						CW_USEDEFAULT,		// Rectangle Left TOP Y
						CW_USEDEFAULT,		// Rectangle Width
						CW_USEDEFAULT,		// Rectangle Height
						NULL,				// Which is a parent window handle - Default is Desktop window handle - NULL indicates take desktop window as parent
						NULL,				// Menu handle
						hInstance,			// Instance handle
						NULL);				// Anything extra we want to provide to window, give it in this parameter

	//Show Window
	ShowWindow(hwnd, iCmdShow);	// Show window, how to show - by iCmdShow e.g SW_MAXIMIZE. 

	//Update the Window
	UpdateWindow(hwnd);	// It paints window's background (rectangular area - Client Area) using brush 

	//Message Loop
	/*
	///  Some activity by user on window.
	///  OS gets this activity/Event and gets to know which window caption is active.
	///  OS takes MSG struct and fills it with event with unique msg id. (hwnd, uint imsg, wparam, lparam, time, co-ordinate) 
	///  OS keeps this msg in message pool. Such multiple MSGs are kept in message pool
	///  Every window has its message queue (as like straw). This queue filled with windows related messages
	///  Window translates this msg, and forward this msg to WndProc
	///  This getMessage, translate and dispatch happen in the while loop called as message loop
	*/
	while (GetMessage(&msg, NULL, 0, 0)) //If no message then program stucks here
	// When there WM_QUIT message GetMessage returns false
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); //Forward this msg to WndProc
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//Local Variable Declarations

	// Local static is more preffered than global variable declaration
	TCHAR str[255];

	//Code
	switch (iMsg)
	{
	case WM_CREATE: //EVENT_DELIGATE - .net / LISTERNER - JAVa
	// Its always first message to wndproc
	// This comes directly from OS. Not from messsage loop. This message is not posted
	// This message is received only once
	// If we need something lifetime of window. We should create those things in WM_CREATE message
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
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam)); 
}

//Commands: 
// cl.exe /c /EHsc Window.cpp
// cl.exe /c /EHsc /D UNICODE Window.cpp
// link.exe Window.obj user32.lib gdi32.lib /subsystem:WINDOWS
