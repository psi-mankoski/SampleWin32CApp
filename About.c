/*
    File:   About.c
    Author: ***PSI***
    Date:   Sun Nov 25 09:28:07 2018
   
    Description:
       Sample Win32 C application "About" box implementation.
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


// Define functions.


static void
aboutDlg_OnCommand(HWND hWnd, int id, HWND hWndCtrl, UINT codeNotify)
{

    switch (id) {

      case IDOK:
          // OK button push or Enter keypress.
      case IDCANCEL:
          // Esc keypress.
          EndDialog(hWnd, TRUE);
          // Dismiss the about dialog box.
          break;

    }
}

static BOOL
aboutDlg_OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
    return TRUE;
}


BOOL CALLBACK
aboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
      case WM_COMMAND:
          // Notification from a control.
          return HANDLE_WM_COMMAND(hWnd, wParam, lParam, aboutDlg_OnCommand);

      case WM_INITDIALOG:
          // Initialization of controls complete.
          return HANDLE_WM_INITDIALOG(hWnd, wParam, lParam, aboutDlg_OnInitDialog);
    }

    return FALSE;
}
