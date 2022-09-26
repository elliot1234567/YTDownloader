// GO THROUGH AND COMMENT WHAT EACH LINE DOES
// COMMENT THE DIFFERENT SECTIONS AND HOW THEY WORK

#include <windows.h>
#include <shobjidl.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <shobjidl.h>
#include <shlobj_core.h>
#include <Python.h>
#include <clocale>
#include <cstdlib>
#include <string>
#include <atlstr.h>
#include <iostream>

// Global variables

static TCHAR szWindowClass[] = _T("YTDownloader"); // The main window class name.
static TCHAR szTitle[] = _T("YTDownloder"); // The string that appears in the application's title bar.
static LPWSTR youtubeLink;
static char* yt;
HINSTANCE hInst; // Stored instance handle for use in Win32 API calls such as FindResource
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Forward declarations of functions included in this code module:

std::string utf8_encode(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

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
//==================END WINDOW CONFIGURATION======================//

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

    HWND download = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"DOWNLOAD",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        140,         // x position 
        400,         // y position 
        200,        // Button width
        50,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL // Pointer not needed.
    );
    HWND ytLink = CreateWindow(
        L"EDIT",  // Predefined class; Unicode assumed 
        L"YOUTUBE LINK",      // Button text 
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,  // Styles 
        10,         // x position 
        100,         // y position 
        400,        // Button width
        20,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL // Pointer not needed.
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

//================================START DOWNLOAD BUTTON===============================//
        if (SendMessage(download, BM_GETSTATE, 0, 0)) {
            int textLength = GetWindowTextLength(ytLink);
            LPWSTR pszMem = (LPWSTR)VirtualAlloc((LPVOID)NULL,
                (DWORD)(textLength + 1), MEM_COMMIT,
                PAGE_READWRITE);
            GetWindowText(ytLink, pszMem, textLength + 1);
            Py_Initialize();
            // CODE TO RUN PYTHON FUNCTION
            PyObject* output = PyUnicode_FromString("C:\\Users\\Elliot Scher\\Videos");
            PyObject* ytlink = PyUnicode_FromString(utf8_encode(pszMem).c_str());
            PyObject* pName, * pModule, * pFunc, * pArgs, * pValue;
            pName = PyUnicode_FromString((char*)"Downloader");
            pModule = PyImport_Import(pName);
            pFunc = PyObject_GetAttrString(pModule, (char*)"download");
            pArgs = PyTuple_Pack(2, (char*)ytlink, (char*)output);
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_Finalize();
        }
//================================END DOWNLOAD BUTTON===============================//

        
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