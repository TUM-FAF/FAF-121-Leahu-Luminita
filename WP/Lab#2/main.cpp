#include <windows.h>
#include <commdlg.h>
#include "resource.h"

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
//ScrollProcedure(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK   AboutDlgProc  (HWND, UINT, WPARAM, LPARAM);

int idFocus;
WNDPROC OldScroll[3];

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";

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
    static HWND hwnd_listbox;
    static COLORREF crPrim[3] = {RGB (0, 150, 23), RGB (25, 200, 65), RGB (155, 35, 200)};
    static HWND   hwnd_Scroll_color, hwndLabel[3], hwndValue[3], hwnd_Scroll, hwnd_Scroll3, hwnd_text;
    static int color[3];
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
                               WS_VISIBLE | WS_CHILD,
                               30, 30,
                               150, 200,
                               hwnd,
                               (HMENU) BUTTON_LISTBOX,
                               NULL, NULL);

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

               MoveWindow(hwnd_listbox, 30, 30, cxChar/2-10, cyChar/2+60, TRUE);
               MoveWindow(hwnd_Scroll, 30, cyChar/2+100, cxChar/2+70, 20, TRUE);
               MoveWindow(hwnd_Scroll3, cxChar/2+80, 30, 20, cyChar/2+55, TRUE);
               MoveWindow(hwnd_Scroll_color, cxChar/2+40, 30, 20, cyChar/2+55, TRUE);

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
        switch(LOWORD(wParam))
        {
        case IDI_ABOUT:
            DialogBox(hInstance, MAKEINTRESOURCE(IDI_DIALOG), hwnd, AboutDlgProc);
            break;

        case IDI_EXIT:
            DestroyWindow(hwnd);
        }
        break;
        break;

        case WM_VSCROLL:
            if ((HWND)lParam == hwnd_Scroll_color)
            {
                switch(LOWORD(wParam))
                {
                case SB_PAGEDOWN:

                    color_id = color_id + 15;
                    break;

                case SB_LINEDOWN:

                    color_id = min (255, color_id + 1);
                    break;

                case SB_PAGEUP:

                    color_id = color_id - 15;
                    break;

                case SB_LINEUP:

                    color_id = max (0, color_id - 1);
                    break;

                case SB_TOP:

                    color_id = 0;
                    break;

                case SB_BOTTOM:

                    color_id = 255;
                    break;

                case SB_THUMBPOSITION:
                case SB_THUMBTRACK:

                    color_id = HIWORD(wParam);
                    break;

                default: break;
                }
                SetScrollPos(hwnd_Scroll_color, SB_CTL, color_id ,TRUE);
                InvalidateRect(hwnd, )
            }
/*            if((HWND)lParam==hwndScrollVPOS)
            {
                switch(LOWORD(wParam))
                {
                case SB_PAGEDOWN:
                    posY-=Y_PAGE_MOVE;
                case SB_LINEDOWN:
                    posY=max(0,posY-Y_LINE_MOVE);
                    break;
                case SB_PAGEUP:
                    posY+=Y_PAGE_MOVE;
                case SB_LINEUP:
                    posY=min(200,posY+Y_LINE_MOVE);
                    break;
                case SB_TOP:
                    posY=200;
                    break;
                case SB_BOTTOM:
                    posY=0;
                    break;
                case SB_THUMBPOSITION:
                    posY=HIWORD(wParam);
                    break;
                default: break;
                }

                SetScrollPos(hwnd_Scroll,SB_CTL,200-posY,TRUE);
                SetWindowPos(hwnd,HWND_TOP,posX,posY,0,0,SWP_SHOWWINDOW|SWP_NOSIZE);
            }*/
            return 0;

        case WM_CTLCOLORLISTBOX:

            SetBkMode((HDC)wParam,TRANSPARENT);
            hbrush=(HBRUSH) CreateSolidBrush(Color);
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

