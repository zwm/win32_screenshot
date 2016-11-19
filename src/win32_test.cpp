// ----------------------------------------------------------------------------
// File Name        : win32_test.cpp
// Description      : First time to study win32 programming!
// Revision History : 201611191250  File creat
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "windows.h"

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
 *
 *
******************************************************************************/

LRESULT CALLBACK WinMessageProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
#define MESSAGEBOX_SECTION      0

// main
int _tmain(int argc, _TCHAR* argv[])
{
    // messagebox test
    int sum = 0;
    LPTSTR title = _T("Title");
    LPTSTR content = _T("Hello World!");
    TCHAR strSum[256] = {0};
    for(int i=0; i<10; i++)
        sum += i;
    wsprintf(strSum, _T("%d"), sum);
	// MessageBoxA(NULL,"Hellobeyondcode","Title",MB_OK);
	// MessageBox(NULL, content, title,MB_OK);
	MessageBox(NULL, strSum, title,MB_OK);
	//MessageBox();
	//TCHAR c = _T('A');
/*
	WNDCLASSEX wc;
wc.cbSize = sizeof( wc );
wc.style = CS_VREDRAW | CS_HREDRAW;
wc.cbClsExtra = 0;
wc.cbWndExtra = 0;
wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
wc.hCursor = LoadCursor( NULL, IDC_ARROW );
wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
//wc.hInstance = hInstance;
wc.lpfnWndProc = WinMessageProc;
wc.lpszMenuName = NULL;
wc.lpszClassName = _T("MyWindowClass");
if( !RegisterClassEx( &wc ) )
{
MessageBox( NULL, _T("注册窗口类出错"), _T("出错"), MB_OK );
return 0;
}


HWND newWind = CreateWindowEx( 0L, _T("MyWindowClass"), _T("beyondcode"),
WS_OVERLAPPEDWINDOW, 0, 0, 200, 200, NULL, NULL, hInstance, NULL );
if( NULL==newWind )
{
MessageBox( NULL, _T("创建窗口出错"), _T("出错"), MB_OK );
return 0;
}
ShowWindow( newWind, nShowCmd );
UpdateWindow( newWind );


*/

    // return
	return 0;

}

