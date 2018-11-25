/*
    File:   Sample.c
    Author: ***PSI***
    Date:   Sun Nov 25 09:26:10 2018
   
    Description:
       Sample Win32 C application implementation.

       This is the skeleton of a Win32 application in the C
       programming language.  It is intended as as starting
       point for projects requiring the basic "boilerplate"
       to create a single document window, handle events, and
       display an "about" box.

       ***NOTE:  This is simply a conceptual work in progress!!!
       In paricular, it does not yet actually compile or run with
       any particular Win32 tool chain!!***
*/


/*
 *  Copyright (c) 2018 Joseph J. Mankoski ***PSI***
 *  
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation files
 *  (the "Software"), to deal in the Software without restriction,
 *  including without limitation the rights to use, copy, modify, merge,
 *  publish, distribute, sublicense, and/or sell copies of the Software,
 *  and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 *  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 *  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */


// Include declarations files.


#include "Sample.h"


// Define global variables.


// Name of the application's class.
const TCHAR szAppName[] = TEXT("Sample");

// Title of the application's main window.
const TCHAR szTitle[] = TEXT("Sample Window");

// Coordinates of output window origin.
int gXOrigin, gYOrigin;

// Main application instance handle.
HINSTANCE gHInstance;

// Main application window handle.
HWND gMainWindow;

BOOL gDisplayInitialized = FALSE;

int gFirstLine, gLastLine, gNumLines, gCurrentNumLines;
int gXPosition, gYPosition, gLineHeight;

TCHAR gMessage[kMaxStringLength][kMaxNumLines];


// Define functions.


static void
doAbout(HWND hWnd)
{
    DialogBox(gHInstance, MAKEINTRESOURCE(IDD_ABOUT_DIALOG), hWnd, (DLGPROC) aboutDlgProc);
}

static void
doProcess(HWND hWnd)
{
    // TODO:  Insert code to implement the application's main processing here.
    //        (Whatever that may be.)
}

static void
doSave(HWND hWnd)
{
    // TODO:  Insert code to implement the application's "save" function here.
}

static void
doLoad(HWND hWnd)
{
    // TODO:  Insert code to implement the application's "load" function here.
}

static void
mainWindow_OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
    switch (id) {
      case IDM_ABOUT:
          doAbout(hWnd);
          return;

      case IDM_EXIT:
          DestroyWindow(hWnd);
          return;

      case IDM_CLEAR:
          ClearDisplay();
          return;

      case IDM_PROCESS:
          doProcess(hWnd);
          return;

      case IDM_SAVE:
          doSave(hWnd);
          return;

      case IDM_LOAD:
          doLoad(hWnd);
          return;

      default:
          FORWARD_WM_COMMAND(hWnd, id, hWndCtl, codeNotify, DefWindowProc);
    }
}

static void
mainWindow_OnDestroy(HWND hWnd)
{
    PostQuitMessage(0);
}

void
InitializeDisplay(void)
{
    HDC hdc;
    TEXTMETRIC tm;

    hdc = GetDC(gMainWindow);

    GetTextMetrics(hdc, &tm);

    gLineHeight = tm.tmHeight + tm.tmExternalLeading;

    ReleaseDC(gMainWindow, hdc);

    gDisplayInitialized = TRUE;
}

void
ClearDisplay(void)
{
    gFirstLine = gLastLine = 0;
    gNumLines = 0;
    gXPosition = gXOrigin;
    gYPosition = gYOrigin;

    for (int line = 0; line < kMaxNumLines; line++)
      _tcscpy(gMessage[line], TEXT(""));

    RedrawDisplay();
}

void
RedrawDisplay(void)
{
    RECT rect;

    GetClientRect(gMainWindow, &rect);
    rect.left = gXOrigin;
    rect.top  = gYOrigin;

    InvalidateRect(gMainWindow, &rect, TRUE);
}

void
Display(TCHAR *format, ...)
{
    va_list args;

    va_start(args, format);
    vsprintf(gMessage[gLastLine], format, args);
    va_end(args);

    gLastLine = (gLastLine + 1) % kMaxNumLines;

    if (gNumLines < kMaxNumLines - 1)
      gNumLines++;
    else {
        gNumLines = kMaxNumLines;
        gFirstLine = (gFirstLine + 1) % kMaxNumLines;
    }

    RedrawDisplay();
}

// Put up a message box with an informational message.
void DisplayMessage(TCHAR *format, ...)
{
    va_list args;
    TCHAR theMessage[255];

    va_start(args, format);
    wvsprintf(theMessage, format, args);
    va_end(args);

    MessageBox(NULL, theMessage, TEXT("Note"), MB_ICONINFORMATION);
}

// Display the error message associated with the last Win32 API function call.
void DisplayError(TCHAR *messagePrefix)
{
    DWORD eMsgLen, lastError = GetLastError();
    TCHAR *lpvSysMsg;
    
    eMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                            FORMAT_MESSAGE_FROM_SYSTEM, NULL, lastError,
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                            (LPTSTR) &lpvSysMsg, 0, NULL);

    TCHAR theMessage[255];
    _stprintf(theMessage, TEXT("%s: %s"), messagePrefix, lpvSysMsg);

    MessageBox(NULL, theMessage, TEXT("Oops!"), MB_ICONEXCLAMATION);

    HeapFree(GetProcessHeap(), 0, lpvSysMsg);
}

static void
mainWindow_OnPaint(HWND hWnd)
{
    HDC hdc;
    RECT rect;
    PAINTSTRUCT ps;
    int linePos, numLinesToDisplay;

    if (!gDisplayInitialized)
      return;

    hdc = BeginPaint(hWnd, &ps);

    GetClientRect(hWnd, &rect);
    gCurrentNumLines = (rect.bottom - rect.top - gYOrigin) / gLineHeight;

    numLinesToDisplay = min(gNumLines, gCurrentNumLines);

    if (gFirstLine <= gLastLine)
      linePos = gLastLine - numLinesToDisplay;
    else {
        if (gLastLine >= numLinesToDisplay)
          linePos = gLastLine - numLinesToDisplay;
        else
          linePos = kMaxNumLines + (gLastLine - numLinesToDisplay);
    }

    gYPosition = gYOrigin;
    for (int line = 0; line < numLinesToDisplay; line++) {
        ExtTextOut(hdc, gXPosition, gYPosition, NULL, NULL, gMessage[linePos], _tcslen(gMessage[linePos]), NULL);
        gYPosition += gLineHeight;
        linePos = (linePos + 1) % kMaxNumLines;
    }

    EndPaint(hWnd, &ps);
}

LRESULT CALLBACK
mainWindowWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
      case WM_COMMAND:
          return HANDLE_WM_COMMAND(hWnd, wParam, lParam, mainWindow_OnCommand);

      case WM_DESTROY:
          return HANDLE_WM_DESTROY(hWnd, wParam, lParam, mainWindow_OnDestroy);

      case WM_PAINT:
          return HANDLE_WM_PAINT(hWnd, wParam, lParam, mainWindow_OnPaint);

      default:
          return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

BOOL
InitApplication(HINSTANCE hInstance)
{
    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc = (WNDPROC) mainWindowWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
    wc.lpszClassName = szAppName;

    return RegisterClass(&wc);
}

BOOL
InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    DWORD dwStyle = WS_OVERLAPPEDWINDOW;

    if ((hWnd = CreateWindow(szAppName, szTitle, dwStyle,0, 0,
                             CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
                             hInstance, NULL)) == NULL) {
        return FALSE;
    }

    if (!IsWindow(hWnd))
      return FALSE;

    gXOrigin = 0;
    gYOrigin = 0;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    gMainWindow = hWnd;

    InitializeDisplay();
    ClearDisplay();

    return TRUE;
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    MSG message;
    HACCEL hAccel;

    if (hPrevInstance == NULL) {
        if (InitApplication(hInstance) == FALSE)
          return FALSE;
    }

    if (InitInstance(hInstance, nCmdShow) == FALSE)
      return FALSE;

    // Save the instance handle globally, since there's no obvious way to get
    //  it under WindowsCE.
    gHInstance = hInstance;

    hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

    while (GetMessage(&message, NULL, 0, 0) == TRUE) {
        if (!TranslateAccelerator(message.hwnd, hAccel, &message)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    return message.wParam;
}
