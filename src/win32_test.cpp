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
 * 7. SDK���򾭵䲽��
 *      (1) ע�ᴰ����
 *      (2) ��������
 *      (3) ��Ϣѭ��
 *      (4) ��д������Ϣ������
 * 8. About hInstance?
 *      Ҳ�ԣ�Ҳ���ԣ�HINSTANCE�ǽ���ʵ�������������ʶÿ�����̵ģ����������
 *      ����������ϵͳ����WinMain�ģ�����ÿһ��Windows�µģ�C/C++�����ڱ���
 *      ʱ���������ڵ㺯������Win32�������Ϻ�����WinMainCRTStartup�������
 *      ������ͨ������ GetModuleHandle(NULL)�������������Ȼ�󴫸�WinMain�С�
 *      ���ڳ����оͿ��������ˣ���Ȼ�㲻����WinMain�д������Ĳ�����ֱ�ӵ���
 *      GetModuleHandle(NULL)Ҳ���ԡ�
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

    // ע�ᴰ��
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
        MessageBox( NULL, _T("ע�ᴰ�������"), _T("����"), MB_OK );
        return 0;
    }

    // ��������
    HWND newWind = CreateWindowEx( 0L, _T("MyWindowClass1111"), _T("beyondcode"),
            //WS_OVERLAPPEDWINDOW, 0, 0, 200, 200, NULL, NULL, hinst, NULL );
            //WS_VISIBLE, 0, 0, 200, 200, NULL, NULL, hinst, NULL );
            // WS_OVERLAPPED, 0, 0, 200, 200, NULL, NULL, hinst, NULL );
            WS_OVERLAPPED, 0, 0, 200, 200, HWND_DESKTOP, NULL, hinst, NULL );
    if( NULL==newWind )
    {
        DWORD a = GetLastError();
        TCHAR strSum[256] = {0};
        wsprintf(strSum, _T("�������ڳ���, hinst: %d, GetLastError: %d"), hinst, a);

        MessageBox( NULL, strSum, _T("����"), MB_OK );
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

