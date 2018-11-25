/*
    File:   Sample.h
    Author: ***PSI***
    Date:   Sun Nov 25 09:25:47 2018
   
    Description:
       Sample Win32 C application declarations file.
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


// Enable strict type-checking of Windows handles.
#ifndef STRICT
#define STRICT
#endif // !defined(STRICT)

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>

#include <stdio.h>

#include "Resource.h"


// Define constants.


const int kMaxStringLength = 256;

const int kMaxNumLines     = 64;


// Define function prototypes.


// (Defined in "About.c".)
BOOL CALLBACK aboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
