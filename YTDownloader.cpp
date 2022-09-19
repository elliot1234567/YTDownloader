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

//================ START WINDOW CONFIGURATION===============//
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

    //============START MAIN MESSAGE LOOP============//
    MSG msg; // declaring new messaage
    while( // while :-) lol
        GetMessage( // call to get the message
            &msg, // message pointer
            NULL, // window handle to get message (null means it gets from any window)
            0, // the message
            0 // additional message information
        )
    ){
        TranslateMessage(&msg); // translates message into characters
        DispatchMessage(&msg); // sends message to wndproc
    }

    return (int)msg.wParam; // returns message
    //============END MAIN MESSAGE LOOP============//
}

LRESULT CALLBACK WndProc( // creating WndProc function
    HWND hWnd, // window handle
    UINT message, // message
    WPARAM wParam, // additional message information
    LPARAM lParam // additional message information
)
{
    PAINTSTRUCT ps; // declare paintstruct object
    HDC hdc; // handle to device context
    TCHAR greeting[] = _T("This is a youtube video downloader!!!"); // greeting

    switch (message) { // switch :-) lol
    case WM_PAINT: // when request is sent to paint part of the window
        hdc = BeginPaint(hWnd, &ps); // initialize device context handle as a beginpaint object
        TextOut(
            hdc, // device context handle object
            5, 5, // coordinates
            greeting, _tcslen(greeting) // greeting
        );
        EndPaint(hWnd, &ps); // ends paint
        break; // breaks out of case
    case WM_DESTROY: // when window is destroyed
        PostQuitMessage(0); // terminatation message
        break; // breaks out of case
    case WM_CLOSE: // when window is closed
        if (MessageBox(hWnd, L"Really quit?", L"YTDownloader", MB_OKCANCEL) == IDOK) // message box asking user if they meant to quit
        {
            DestroyWindow(hWnd); // closes application
        }
        break;// breaks out of case
    default: // default case
        return DefWindowProc( // handle other messages
            hWnd, // window handle
            message, // message
            wParam, // additional message information
            lParam // additional message information
        );
        break; // breaks out of case
    }
    return 0; // return success
}