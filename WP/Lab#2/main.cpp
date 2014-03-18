#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <commdlg.h>
#include "resource.h"

using namespace std;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ListProc(HWND hwnd, UINT message, WPARAM, LPARAM);
LRESULT CALLBACK ScrollProc(HWND hwnd, UINT message, WPARAM, LPARAM);
BOOL    CALLBACK   AboutDlgProc  (HWND, UINT, WPARAM, LPARAM);

int idFocus;
WNDPROC old_scroll, oldlist;

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
    static HWND   hwnd_Scroll, hwnd_Scroll3, hwnd_Scroll_color, hwnd_text;
    static int id_red = 245, id_green = 230, id_blue = 28;
    static RECT rect;
    static TCHAR * szColorLabel[] = { TEXT("Color"), TEXT("Width"), TEXT("Height") };
    int    i, cxChar, cyChar, cxClient, cyClient, Scroll_ID, iscroll, iscrollh, iWidth, iHeight, iSysWidth, iSysHeight;
    static int  color_id = 0, posY = 200, posX = 400;


    TCHAR  szBuffer[10];
    HBRUSH hbrush;
    SCROLLINFO si;
    HDC        hdc;
    TEXTMETRIC tm;

    hdc = GetDC(hwnd);
    GetTextMetrics(hdc, &tm);
    cxChar = tm.tmAveCharWidth;
    cyChar = tm.tmHeight;
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
                               WS_VISIBLE | WS_CHILD | WS_TABSTOP | SBS_HORZ |SBS_BOTTOMALIGN, // styles of scrollbar
                               30, 240,
                               240, 20,
                               hwnd,
                               (HMENU) SCROLLBAR_1,
                               NULL, NULL);

        SetScrollRange(hwnd_Scroll, SB_CTL, 0, 400, FALSE);
        SetScrollPos(hwnd_Scroll, SB_CTL, 0, FALSE);

        hwnd_Scroll_color = CreateWindow(TEXT("Scrollbar"), NULL,
                               WS_VISIBLE | WS_CHILD | WS_TABSTOP | SBS_VERT | SBS_BOTTOMALIGN, // styles of scrollbar
                               200, 30,
                               20, 192,
                               hwnd,
                               (HMENU) SCROLLBAR_2,
                               NULL, NULL);

        SetScrollRange(hwnd_Scroll_color, SB_CTL, 0, 255, FALSE);
        SetScrollPos(hwnd_Scroll_color, SB_CTL, 0, FALSE);

        hwnd_Scroll3 = CreateWindow(TEXT("Scrollbar"), NULL,
                               WS_VISIBLE | WS_CHILD | WS_TABSTOP | SBS_VERT | SBS_BOTTOMALIGN, // styles of scrollbar
                               250, 30,
                               20, 192,
                               hwnd,
                               (HMENU) SCROLLBAR_3,
                               NULL, NULL);

        SetScrollRange(hwnd_Scroll3, SB_CTL, 0, 200, FALSE);
        SetScrollPos(hwnd_Scroll3, SB_CTL, 0, FALSE);

        hwnd_text   = CreateWindow(TEXT("static"), TEXT("Laboratory Work"),
                               WS_VISIBLE | WS_CHILD , // styles of button
                               30, 5,
                               192, 20,
                               hwnd,
                               (HMENU) BUTTON_STATIC,
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
        {
               cxClient= LOWORD (lParam) ;
               cyClient = HIWORD (lParam) ;

               MoveWindow(hwnd_listbox, 30, 30, cxClient/2+30, cyClient/2+60, TRUE);
               MoveWindow(hwnd_Scroll, 30, cyClient/2+100, cxClient/2+70, 20, TRUE);
               MoveWindow(hwnd_Scroll3, cxClient/2+120, 30, 20, cyClient/2+55, TRUE);
               MoveWindow(hwnd_Scroll_color, cxClient/2+80, 30, 20, cyClient/2+55, TRUE);

            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((340 - 100) / cyChar);
            si.nPage = cyClient / cyChar;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((350 - 40) / cxChar);
            si.nPage = cxClient / cxChar;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

               break;
        }

 case WM_VSCROLL :

if((HWND)lParam == hwnd_Scroll_color)
{
    switch(LOWORD(wParam))
    {
        case SB_PAGEDOWN:

            color_id = color_id + Color;
            break;

        case SB_LINEDOWN:

            color_id=min(255,color_id + 10);
            break;

        case SB_PAGEUP:

            color_id = color_id - Color;
            break;

        case SB_LINEUP:

            color_id = max(0, color_id - 10);
            break;

        case SB_TOP:

            color_id = 0;
            break;

        case SB_BOTTOM:

            color_id = 255;
            break;

        case SB_THUMBPOSITION:
            break;

        case SB_THUMBTRACK:

            color_id = HIWORD(wParam);
            break;

            default: break;

            break;
            }

    SetScrollPos(hwnd_Scroll_color, SB_CTL, color_id, TRUE);
    InvalidateRect(hwnd_text,NULL,TRUE);
}
    if((HWND)lParam == hwnd_Scroll3)
{
    switch(LOWORD(wParam))
    {
        case SB_PAGEDOWN:

            posY = posY + 20;
            break;

        case SB_LINEDOWN:

            posY = min(200, posY - 10);
            break;

        case SB_PAGEUP:

            posY = posY - 20;
            break;

        case SB_LINEUP:

            posY = max(0, posY + 10);
            break;

        case SB_TOP:

            posY = 0;
            break;

        case SB_BOTTOM:

            posY = 200;
            break;

        case SB_THUMBPOSITION:
            break;

        case SB_THUMBTRACK:

            posY = HIWORD(wParam);
            break;

            default: break;

            break;
            }

    SetScrollPos(hwnd_Scroll3, SB_CTL , 200 - posY, TRUE);
    SetWindowPos(hwnd, HWND_TOP, posX, posY, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
}

else
{
    si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
		GetScrollInfo(hwnd, SB_HORZ, &si);
        int    y = si.nPos;

        switch(LOWORD(wParam))
				{
					case SB_TOP:

						si.nPos = si.nMin;
					break;

					case SB_BOTTOM:

						si.nPos = si.nMax;
					break;

					case SB_LINEUP:

						si.nPos -= 1;
					break;

					case SB_LINEDOWN:
						si.nPos += 1;
					break;

					case SB_PAGEUP:
						si.nPos -= si.nPage;
					break;

					case SB_PAGEDOWN:
						si.nPos += si.nPage;
					break;

					case SB_THUMBTRACK:
						si.nPos = si.nTrackPos;
					break;

					default:
						break;
				}

				si.fMask = SIF_POS;
				SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
				GetScrollInfo(hwnd, SB_HORZ, &si);

				if(si.nPos != y)
                {
					ScrollWindow(hwnd, 0, cyChar * (y - si.nPos), NULL, NULL);
					UpdateWindow(hwnd);
				}

    }
break;


 case WM_HSCROLL :

if((HWND)lParam == hwnd_Scroll)
{
    switch(LOWORD(wParam))
    {
        case SB_PAGEDOWN:

            posX = posX + 20;
            break;

        case SB_LINEDOWN:

            posX = min(200, posX - 10);
            break;

        case SB_PAGEUP:

            posX= posX - 20;
            break;

        case SB_LINEUP:

            posX = max(0, posX + 10);
            break;

        case SB_TOP:

            posX = 0;
            break;

        case SB_BOTTOM:

            posX = 200;
            break;

        case SB_THUMBPOSITION:
            break;

        case SB_THUMBTRACK:

            posX = HIWORD(wParam);
            break;

            default: break;

            break;
            }

    SetScrollPos(hwnd_Scroll, SB_CTL , 200 - posX, TRUE);
    SetWindowPos(hwnd, HWND_TOP, posX, posY, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
}

    else
    {
        si.cbSize = sizeof(si);
					si.fMask = SIF_ALL;
					GetScrollInfo(hwnd, SB_HORZ, &si);

					int x = si.nPos;
					switch(LOWORD(wParam))
					{
						case SB_LINELEFT:
							si.nPos -= 1;
						break;

						case SB_LINERIGHT:
							si.nPos += 1;
						break;

						case SB_PAGELEFT:
							si.nPos -= si.nPage;
						break;

						case SB_PAGERIGHT:
							si.nPos += si.nPage;
						break;

						case SB_THUMBPOSITION:
							si.nPos = si.nTrackPos;
						break;

						default:break;
					}

					si.fMask = SIF_POS;
					SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
					GetScrollInfo(hwnd, SB_HORZ, &si);

					if(si.nPos != x)
					{
						ScrollWindow(hwnd, cxChar * (x - si.nPos), 0, NULL, 0);
						UpdateWindow(hwnd);
					}
    }
			break;

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

        case IDI_DEFAULT:

            id_red = 245;
            id_green = 230;
            id_blue = 28;
            InvalidateRect(hwnd_listbox, NULL, TRUE);

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

        case WM_CTLCOLORSTATIC:

            SetTextColor((HDC)wParam,RGB(color_id + 20, 100, 255 - color_id));
            SetBkMode((HDC)wParam,TRANSPARENT);
            hbrush=(HBRUSH)GetStockObject(NULL_BRUSH);
            return(LRESULT) hbrush;


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

