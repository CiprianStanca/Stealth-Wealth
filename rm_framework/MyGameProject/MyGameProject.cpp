// MyGameProject.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MyGameProject.h"

#define MAX_LOADSTRING 100

// Global Variables:

HWND g_hWnd;
HINSTANCE g_hInst;	
// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
CGame * g_pGame;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);



int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MYGAMEPROJECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYGAMEPROJECT));

	//create main game object
	g_pGame = new MyGame();

	//prime message
	PeekMessage(&msg, g_hWnd, NULL, NULL, PM_REMOVE);

	//enter main loop
	while (msg.message != WM_QUIT)
		{
		if (PeekMessage(&msg, g_hWnd, NULL, NULL, PM_REMOVE))
			{
			TranslateMessage(&msg);//translate +dispatch to event queue
			DispatchMessage(&msg);
			}
			else
			{
			// clear screen and depth buffer
			CGraphics::PrepareToRender();
			CGraphics::DrawTestObject();
			g_pGame->DoFrame();
			CGraphics::FinishRenderingFrame();
			}
		}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYGAMEPROJECT));
	wcex.hCursor		= LoadCursor(NULL, IDC_CROSS);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MYGAMEPROJECT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance; // Store instance handle in our global variable

   g_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), g_hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:

		CGraphics::DestroyGraphicsWindow(hWnd);
		hWnd=NULL;
		g_hWnd=NULL;
		PostQuitMessage(0);
		break;

	case WM_CREATE:

		CGraphics::InitializeGraphics(hWnd);
		break;

	case WM_SIZE:

		int height,width;
		height = HIWORD(lParam);	// retrieve width and height
		width = LOWORD(lParam);

		CGraphics::SetWindowSize(width, height);
		break;

	case WM_MOUSEMOVE:
	{
		POINT * pMousePos = new POINT();
		int mid_x = CGraphics::GetWidth() >> 1;
		int mid_y = CGraphics::GetHeight() >> 1;

		//Get the 2D mouse cursor (x,y) position	
		GetCursorPos(pMousePos);

		//check mouse not moved	
		if ((pMousePos->x == mid_x) && (pMousePos->y == mid_y)) return 0;

		float x_rel, y_rel;

		// Set mouse cursor to center of window 
		if (CMouseManager::Instance()->GetMouseAnchoredToCentreScreen())
		{
			//mouse anchored to centre of screen
			SetCursorPos(mid_x, mid_y);
			x_rel = (float)(pMousePos->x - mid_x) / mid_x;
			y_rel = (float)(pMousePos->y - mid_y) / mid_y;
		}

		else
		{
			//get window position
			LPRECT myrect = new RECT;
			GetWindowRect(g_hWnd, myrect);
			int WinTitleBarHeight = 48;
			//not clamping cursor to centre - calculate relative position
			x_rel = (float)((pMousePos->x - myrect->left) / (float)(CGraphics::GetWidth()));
			y_rel = (float)((pMousePos->y - myrect->top - WinTitleBarHeight) / (float)(CGraphics::GetHeight()));
		}
		//if mouse moved we can tell the MouseManager about it
		//it will forward the information to any registered listeners
		CMouseManager::Instance()->mouseMoved(x_rel, y_rel);



	}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
