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
 * 6. sprintf   : single-byte version c/c++ lib
 *    swprintf  : multi-byte version c/c++ lib
 *    wsprintf  : windows single/multi-byte version c/c++ lib
 * 7. SDK程序经典步骤
 *      (1) 注册窗口类
 *      (2) 创建窗口
 *      (3) 消息循环
 *      (4) 编写窗口消息处理函数
 * 8. About hInstance?
 *      也对，也不对，HINSTANCE是进程实例句柄，用来标识每个进程的，不过，这个
 *      参数并不是系统传给WinMain的，对于每一个Windows下的，C/C++程序，在编译
 *      时都会加上入口点函数，对Win32程序会加上函数：WinMainCRTStartup，在这个
 *      函数中通过调用 GetModuleHandle(NULL)来获得这个句柄，然后传给WinMain中。
 *      你在程序中就可以用它了，当然你不想用WinMain中传过来的参数，直接调用
 *      GetModuleHandle(NULL)也可以。
 *
******************************************************************************/
// Compile Switch
#define MESSAGEBOX_SECTION      0

// Function Declearation
LRESULT CALLBACK WinMessageProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

// main
int _tmain(int argc, _TCHAR* argv[])
{
    // messagebox test
#if (MESSAGEBOX_SECTION == 1)
    // ASIIC constant dispaly
    MessageBoxA(NULL,"Hellobeyondcode","Title",MB_OK);
#elif (MESSAGEBOX_SECTION == 2)
    // ASIIC/UNICODE variable dispaly
    LPTSTR title = _T("Title");
    LPTSTR content = _T("Hello World!");
    MessageBox(NULL, content, title,MB_OK);
#elif (MESSAGEBOX_SECTION == 3)
    // Display number in messagebox using "wsprintf"
    int sum = 0;
    LPTSTR title = _T("Title");
    TCHAR strSum[256] = {0};
    for(int i=0; i<10; i++)
        sum += i;
    wsprintf(strSum, _T("%d"), sum);
    MessageBox(NULL, strSum, title,MB_OK);
#endif

    // 注册窗口
    HINSTANCE hinst = GetModuleHandle(NULL);
    WNDCLASSEX wc;
    wc.cbSize = sizeof( wc );
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
    wc.hInstance = hinst;
    wc.lpfnWndProc = WinMessageProc;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = _T("MyWindowClass1111");
    if( !RegisterClassEx( &wc ) )
    {
        MessageBox( NULL, _T("注册窗口类出错"), _T("出错"), MB_OK );
        return 0;
    }

    // 创建窗口
    HWND newWind = CreateWindowEx( 0L, _T("MyWindowClass1111"), _T("beyondcode"),
            //WS_OVERLAPPEDWINDOW, 0, 0, 200, 200, NULL, NULL, hinst, NULL );
            //WS_VISIBLE, 0, 0, 200, 200, NULL, NULL, hinst, NULL );
            // WS_OVERLAPPED, 0, 0, 200, 200, NULL, NULL, hinst, NULL );
            WS_OVERLAPPED, 0, 0, 200, 200, HWND_DESKTOP, NULL, hinst, NULL );
    if( NULL==newWind )
    {
        DWORD a = GetLastError();
        TCHAR strSum[256] = {0};
        wsprintf(strSum, _T("创建窗口出错, hinst: %d, GetLastError: %d"), hinst, a);

        MessageBox( NULL, strSum, _T("出错"), MB_OK );
        //return 0;
    }
    // ShowWindow( newWind, nShowCmd );
    ShowWindow( newWind, 12 );
    UpdateWindow( newWind );

    // return
    return 0;

}

LRESULT CALLBACK WinMessageProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    return 0;
}

