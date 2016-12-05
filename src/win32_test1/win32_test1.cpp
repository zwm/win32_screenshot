// ----------------------------------------------------------------------------
// File Name        : win32_test1.cpp
// Description      : First time to study win32 programming!
// Revision History : 201611231843  File creat
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "win32_test1.h"

/******************************************************************************
 * 20161117 Study Contents
 * 1. What's CHAR and WCHAR?
 *      typedef char CHAR;      // asic char
 *      typedef wchar_t WCHAR;  // unicode char
 * 2. What's LPSTR and LPWSTR?
 *      typedef CHAR *LPSTR;
 *      typedef WCHAR *LPWSTR;
 *      typedef CONST CHAR *LPCSTR;
 *      typedef CONST WCHAR *LPCWSTR;
 * 3. What's TCHAR?
 *      #ifdef UNICODE
 *      typedef WCHAR TCHAR;
 *      #else
 *      typedef CHAR TCHAR;
 *    LPTSTR/LPCTSTR is the same!
 * 4. How to assign value to a TCHAR?
 *      use _T(), ex
 *      TCHAR tc = _T('A')
 * 5. Use wsprintf rather than sprintf!
 *      #ifdef UNICODE
 *      #define wsprintf wsprintfW
 *      #else
 *      #define wsprintf wsprintfA
 *      #endif
 * 20161119 Study Contents
 * 6. sprintf   : single-byte version c/c++ lib
 *    swprintf  : multi-byte version c/c++ lib
 *    wsprintf  : windows single/multi-byte version c/c++ lib
 * 7. SDK程序经典步骤
 *      (1) 注册窗口???
 *      (2) 创建窗口
 *      (3) 消息循环
 *      (4) 编写窗口消息处理函数
 * 8. About hInstance?
 *      也对，也不对，HINSTANCE是进程实例句柄，用来标识每个进程的，不过，这???
 *      参数并不是系统传给WinMain的，对于每一个Windows下的，C/C++程序，在编译
 *      时都会加上入口点函数，对Win32程序会加上函数：WinMainCRTStartup，在这个
 *      函数中通过调用 GetModuleHandle(NULL)来获得这个句柄，然后传给WinMain中???
 *      你在程序中就可以用它了，当然你不想用WinMain中传过来的参数，直接调用
 *      GetModuleHandle(NULL)也可以???
 * 20161123 Study Contents
 * 9. What's HINSTANCE?
 *      -- Code Related:
 *      DECLARE_HANDLE(HINSTANCE);
 *      #define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
 *      -- step1: struct HINSTANCE__ {int unused;};
 *      -- step2: typedef struct HINSTANCE__ * HINSTANCE
 *      -- last : HINSTANCE is a struct pointer, point to a struct contains just one int element
 * 10. What's UNREFERENCED_PARAMETER()?
 *      -- Code Related:
 *      #define UNREFERENCED_PARAMETER(P)          (P)
 *      -- Just trick complier to make unused parameter seems to be used!!
 *      -- To avoid generate unwanted warnings
 *
 *
 *
******************************************************************************/
// Compile Switch
#define MESSAGEBOX_SECTION      0

// 
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;
    HACCEL hAccelTable;

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_WIN32_TEST1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32_TEST1));

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32_TEST1));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_WIN32_TEST1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
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
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
        PostQuitMessage(0);
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
