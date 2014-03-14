#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <commdlg.h>
#include "resource.h"

using namespace std;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ListProc(HWND hwnd, UINT message, WPARAM, LPARAM);
BOOL    CALLBACK   AboutDlgProc  (HWND, UINT, WPARAM, LPARAM);

int idFocus;
WNDPROC OldScroll[3], oldlist;

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";

static char buffer[100];
static int index;
static HWND hwnd_listbox;

Labs tasks [6] = {
    "- Laboratory work #1 CO", "DL: 16 March",
    "- Laboratory work #1 WP", "DL: 25 February",
    "- Laboratory work #1 CA", "DL: 19 March",
    "- Laboratory work #1 CG", "DL: 21 March",
    "- Laboratory work #1 IDE","DL: 29 March",
    "- Laboratory work #2 WP" ,"DL: 11 March"};


int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    static CHOOSECOLOR cc;
    static COLORREF CrCustColors[16];

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;               /* Catch double-clicks */
    wincl.cbSize = sizeof (wincl);
    wincl.hIcon   = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));     // custom icon
    wincl.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));     // custom icon
    wincl.hCursor = LoadCursor (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CURSOR)); // custom cursor
    wincl.lpszMenuName = MAKEINTRESOURCE(IDI_MENU);                                  // custom menu
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND; // Use Windows's default colour as the background of the window

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Lab#2:: Scrolls",       /* Title Text */
           WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, /* default window */
           400,       /* Windows decides the position */
           200,       /* where the window ends up on the screen */
           340,                 /* The programs width */
           350,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInstance;
    static COLORREF crPrim[3] = {RGB (0, 150, 23), RGB (25, 200, 65), RGB (155, 35, 200)};
    static HWND   hwnd_Scroll_color, hwndLabel[3], hwndValue[3], hwnd_Scroll, hwnd_Scroll3, hwnd_text;
    static int id_red = 245, id_green = 230, id_blue = 28;
    static RECT rect;
    static TCHAR * szColorLabel[] = { TEXT("Color"), TEXT("Width"), TEXT("Height") };
    int    i, cxChar, cyChar, cxClient, cyClient, Scroll_ID, iWidth, iHeight, iHscrollMax, iHscrollPos;
    int    color_id = 0, posY=350, posX=340;


    TCHAR  szBuffer[10];
    HBRUSH hbrush;
    SCROLLINFO scr;
    HDC        hdc;
    TEXTMETRIC tm;

    hdc = GetDC(hwnd);
    GetTextMetrics(hdc, &tm);
    cxClient = tm.tmAveCharWidth;
    cyClient = tm.tmHeight;
    ReleaseDC(hwnd, hdc);

    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:

        hwnd_listbox = CreateWindow(TEXT("LISTBOX"), TEXT(" "),
                               WS_VISIBLE | WS_CHILD | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
                               30, 30,
                               150, 200,
                               hwnd,
                               (HMENU) IDC_LISTBOX,
                               NULL, NULL);

        for (i = 0; i < 6; i++)
        {
            SendMessage(hwnd_listbox,LB_ADDSTRING,0,(LPARAM)tasks[i].task);    // apend string to listbox
        }

        hwnd_Scroll = CreateWindow(TEXT("Scrollbar"), NULL,
                               WS_VISIBLE | WS_CHILD | WS_TABSTOP | SBS_HORZ, // styles of scrollbar
                               30, 240,
                               240, 20,
                               hwnd,
                               (HMENU) SCROLLBAR_1,
                               NULL, NULL);

        hwnd_Scroll_color = CreateWindow(TEXT("Scrollbar"), NULL,
                               WS_VISIBLE | WS_CHILD | WS_TABSTOP | SBS_VERT, // styles of scrollbar
                               200, 30,
                               20, 192,
                               hwnd,
                               (HMENU) SCROLLBAR_2,
                               NULL, NULL);

        hwnd_Scroll3 = CreateWindow(TEXT("Scrollbar"), NULL,
                               WS_VISIBLE | WS_CHILD | WS_TABSTOP | SBS_VERT, // styles of scrollbar
                               250, 30,
                               20, 192,
                               hwnd,
                               (HMENU) SCROLLBAR_3,
                               NULL, NULL);

        hInstance = ((LPCREATESTRUCT) lParam) -> hInstance;
        oldlist=(WNDPROC) SetWindowLong (hwnd_listbox,GWL_WNDPROC,(LPARAM)ListProc);
        break;

    case WM_SETCURSOR:

        if (LOWORD(lParam) == HTCLIENT)
        {
            SetCursor(LoadCursor(hInstance, MAKEINTRESOURCE(IDI_CURSOR)));
            return TRUE;
        }
        break;

    case WM_SIZE :
               cxChar = LOWORD (lParam) ;
               cyChar = HIWORD (lParam) ;

               MoveWindow(hwnd_listbox, 30, 30, cxChar/2+30, cyChar/2+60, TRUE);
               MoveWindow(hwnd_Scroll, 30, cyChar/2+100, cxChar/2+70, 20, TRUE);
               MoveWindow(hwnd_Scroll3, cxChar/2+120, 30, 20, cyChar/2+55, TRUE);
               MoveWindow(hwnd_Scroll_color, cxChar/2+80, 30, 20, cyChar/2+55, TRUE);

               SCROLLINFO si;
               si.cbSize = sizeof(si);
               si.fMask  = SIF_RANGE | SIF_PAGE;
               si.nMin   = 0;
               si.nMax  = ((350 - 70) / cyClient);
               si.nPage = iHeight / cyChar;
               SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

               si.cbSize = sizeof(si);
               si.fMask  = SIF_RANGE | SIF_PAGE;
               si.nMin   = 0;
               si.nMax  = ((340 - 20) / cxClient);
               si.nPage = iWidth / cxChar;
               SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

               return 0 ;

    case WM_COMMAND:

        if (LOWORD(wParam) == IDC_LISTBOX && (HIWORD(wParam)==LBN_DBLCLK))
            {
                index = SendMessage(hwnd_listbox,LB_GETCURSEL,0,0);
                sprintf(buffer,"%s",tasks[index].DL);
                MessageBox(hwnd, buffer, TEXT("Information"), MB_OK);
                SetFocus(hwnd_listbox);
            }

        switch(LOWORD(wParam))
        {
        case IDI_ABOUT:

            DialogBox(hInstance, MAKEINTRESOURCE(IDI_DIALOG), hwnd, AboutDlgProc);
            break;

        case IDI_EXIT:

            DestroyWindow(hwnd);
            break;

        case IDI_GREEN:

            break;

            default: return DefWindowProc (hwnd, message, wParam, lParam);
        }

    break;

        case WM_KEYDOWN:

            switch(wParam)
            {
            case KEY_E:
                {
                    if (GetAsyncKeyState(VK_LSHIFT))
                    {
                        DestroyWindow(hwnd);
                    }
                 break;
                }

            case F1:
                {
                    if (GetAsyncKeyState(VK_F1))
                    {
                        DialogBox(hInstance, MAKEINTRESOURCE(IDI_DIALOG), hwnd, AboutDlgProc);
                    }
                 break;
                }

            case KEY_C:
                {
                    if (GetAsyncKeyState(VK_SPACE))
                    {
                        id_red = id_red + 25;
                        id_green = id_green - 25;
                        id_blue = id_blue + 25;
                        InvalidateRect(hwnd_listbox, NULL, TRUE);
                    }
                 break;
                }

                default:
                    return DefWindowProc (hwnd, message, wParam, lParam);
            }
        break;

        case WM_CTLCOLORLISTBOX:

            SetBkMode((HDC)wParam,TRANSPARENT);
            hbrush=(HBRUSH) CreateSolidBrush RGB(id_red, id_green, id_blue);
            return(LRESULT) hbrush;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

 BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg,0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

LRESULT CALLBACK ListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == WM_KEYDOWN && wParam == VK_DELETE)
    {
        index = SendMessage(hwnd_listbox,LB_GETCURSEL,0,0);
        sprintf(buffer,"Did you finish this laboratory work? \n%s",tasks[index].DL);
            if (MessageBox(hwnd, buffer, TEXT("Information"), MB_YESNO) == IDYES)
            {
                SendMessage(hwnd_listbox, LB_DELETESTRING, index, 0);
            }
        SetFocus(hwnd_listbox);
    }

    if (message == WM_KEYDOWN && wParam == VK_RETURN)
    {
        index = SendMessage(hwnd_listbox,LB_GETCURSEL,0,0);
        sprintf(buffer,"%s",tasks[index].DL);
        MessageBox(hwnd, buffer, TEXT("Information"), MB_OK);
        SetFocus(hwnd_listbox);
    }

    return CallWindowProc(oldlist,hwnd,message,wParam,lParam);
}

