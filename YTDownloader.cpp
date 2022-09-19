// GO THROUGH AND COMMENT WHAT EACH LINE DOES
// COMMENT THE DIFFERENT SECTIONS AND HOW THEY WORK

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

static TCHAR szWindowClass[] = _T("YTDownloader"); // The main window class name.
static TCHAR szTitle[] = _T("YTDownloder"); // The string that appears in the application's title bar.
HINSTANCE hInst; // Stored instance handle for use in Win32 API calls such as FindResource
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Forward declarations of functions included in this code module:

int WINAPI WinMain( // entry point for a graphical Windows-based application. Essentially the main() function
    _In_ HINSTANCE hInstance, // current instance of the application
    _In_opt_ HINSTANCE hPrevInstance, // previous instance of the application (null)
    _In_ LPSTR     lpCmdLine, // application command line 
    _In_ int       nCmdShow // controls how the window is shown
)
{
    WNDCLASSEX wcex; // declaring window structure

//================ START WINDOW CONFIGURATION=====================//
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
//==================END WINDOW CONFIGURATION================//

    if (!RegisterClassEx(&wcex)) // checks to see if the registration of &wcex (window pointer) with windows OS failed.
    {
        MessageBox( // creates new message box for an error message
            NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("YTDownloader failed"),
            NULL
        );

        return 1; // return failure
    }

    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowEx( // creating the window
        WS_EX_OVERLAPPEDWINDOW, // An optional extended window style.
        szWindowClass, // the name of the application
        szTitle, // the text that appears in the title bar
        WS_OVERLAPPEDWINDOW, // the type of window to create
        CW_USEDEFAULT, CW_USEDEFAULT, // initial position (x, y)
        500, 500, // initial size (width, length)
        NULL, // the parent of this window
        NULL, // this application does not have a menu bar
        hInstance, // the first parameter from WinMain
        NULL // not used in this application
    );

    if (!hWnd) // checks to see if handle for window is true, if false:
    {
        MessageBox(NULL, // create new message box
            _T("Call to CreateWindow failed!"),
            _T("YTDownloader failed"),
            NULL);

        return 1; // return failure
    }

    ShowWindow( // make window visible
        hWnd, // the value returned from CreateWindow
        nCmdShow // the fourth parameter from WinMain

    );
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("This is a youtube video downloader!!!");

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, Windows desktop!"
        // in the top left corner.
        TextOut(hdc,
            5, 5,
            greeting, _tcslen(greeting));
        // End application-specific layout section.

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}