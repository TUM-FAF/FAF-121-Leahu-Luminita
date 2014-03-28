#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <commdlg.h>
#include <iostream>
#include "resource.h"

using namespace std;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ListProc(HWND hwnd, UINT message, WPARAM, LPARAM);
LRESULT CALLBACK ScrollProc(HWND hwnd, UINT message, WPARAM, LPARAM);
BOOL    CALLBACK   AboutDlgProc  (HWND, UINT, WPARAM, LPARAM);

WNDPROC oldlist;

// Make the class name into a global variable
char szClassName[ ] = "CodeBlocksWindowsApp";

// global variables
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
    HWND hwnd;               // This is the handle for our window
    MSG messages;            // Here messages to the application are saved
    WNDCLASSEX wincl;        // Data structure for the windowclass

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof (wincl);
    wincl.hIcon   = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));     // custom icon
    wincl.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));     // custom icon
    wincl.hCursor = LoadCursor (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CURSOR)); // custom cursor
    wincl.lpszMenuName = MAKEINTRESOURCE(IDI_MENU);                                  // custom menu
    wincl.cbClsExtra = 0;                                 // no extra bytes after the window class
    wincl.cbWndExtra = 0;                                 // structure or the window instance
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;      // use Windows's default colour as the background of the window

    if (!RegisterClassEx (&wincl))                        // register the window class, and if it fails quit the program
        return 0;

    hwnd = CreateWindowEx (
           0,                                             // extended possibilites for variation
           szClassName,                                   // classname
           "Lab#2:: Scrolls",                             // tTitle Text
           WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, // window's styles
           400,                                           // window`s start positiop
           200,                                           // where the window ends up on the screen
           340,                                           // the inital window`s width
           350,                                           // and height in pixels
           HWND_DESKTOP,                                  // the window is a child-window to desktop
           NULL,                                          // no menu
           hThisInstance,                                 // program Instance handler
           NULL                                           // no Window Creation data
           );

    // make the window visible on the screen
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // run the message loop. It will run until GetMessage() returns 0
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);                      // translate virtual-key messages into character messages
        DispatchMessage(&messages);                       // send message to WindowProcedure
    }

    return messages.wParam;                 // the program return-value is 0 - The value that PostQuitMessage() gave
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInstance;                                             // handle to an instance
    static HWND   hwnd_scroll_width, hwnd_scroll_height, hwnd_scroll_color, hwnd_text;  // handles to main window
    static int id_red = 245, id_green = 230, id_blue = 28;                  // indexes for RGB
    int    i;                                                               // index for loop
    int    cxChar, cyChar;                                                  // store the average width and height of the font
    int    cxClient, cyClient;                                              // store the width and height of the window
    static int  color_id = 0, posY = 200, posX = 400;                       // idexes for scrollbars

    HBRUSH hbrush;                                                          // handle to brush
    SCROLLINFO si;                                                          // contains scroll bar parameters, which will be used in ScrollInfo funcrion
    HDC        hdc;                                                         // handle to device context (DC)
    TEXTMETRIC tm;                                                          // contains basic information about a physical font

    hdc = GetDC(hwnd);                                                      // retrieves a handle to a DC for the client area
    GetTextMetrics(hdc, &tm);                                               // fills the specified buffer with the metrics for the currently selected font
    cxChar = tm.tmAveCharWidth;                                             // average width of the font
    cyChar = tm.tmHeight;                                                   // height of the font
    ReleaseDC(hwnd, hdc);                                                   // releases a DC

    switch (message)                                                        // handle the messages
    {
        case WM_CREATE:

            hwnd_listbox = CreateWindow(TEXT("LISTBOX"), TEXT(" "),                             // button's type and caption
                                   WS_VISIBLE | WS_CHILD | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,   // button's styles
                                   30, 30,                                                      // button's position on main window
                                   150, 200,                                                    // button's width and height
                                   hwnd,                                                        // handle to main window
                                   (HMENU) IDC_LISTBOX,                                         // button's ID
                                   NULL, NULL);                                                 // extra parameteres

            for (i = 0; i < 6; i++)
            {
                SendMessage(hwnd_listbox,LB_ADDSTRING,0,(LPARAM)tasks[i].task);                 // apend string to listbox
            }

            hwnd_scroll_width = CreateWindow(TEXT("Scrollbar"), NULL,
                                   WS_VISIBLE | WS_CHILD | WS_TABSTOP | SBS_HORZ |SBS_BOTTOMALIGN, // styles of scrollbar
                                   30, 240,
                                   240, 20,
                                   hwnd,
                                   (HMENU) SCROLLBAR_W,
                                   NULL, NULL);

            SetScrollRange(hwnd_scroll_width, SB_CTL, 0, 200, FALSE);   // sets the minimum and maximum scroll box positions
            SetScrollPos(hwnd_scroll_width, SB_CTL, 0, FALSE);          // sets the position of the scroll box (thumb)

            hwnd_scroll_color = CreateWindow(TEXT("Scrollbar"), NULL,
                                   WS_VISIBLE | WS_CHILD | WS_TABSTOP | SBS_VERT | SBS_BOTTOMALIGN, // styles of scrollbar
                                   200, 30,
                                   20, 192,
                                   hwnd,
                                   (HMENU) SCROLLBAR_C,
                                   NULL, NULL);

            SetScrollRange(hwnd_scroll_color, SB_CTL, 0, 255, FALSE);
            SetScrollPos(hwnd_scroll_color, SB_CTL, 0, FALSE);

            hwnd_scroll_height = CreateWindow(TEXT("Scrollbar"), NULL,
                                   WS_VISIBLE | WS_CHILD | WS_TABSTOP | SBS_VERT | SBS_BOTTOMALIGN, // styles of scrollbar
                                   250, 30,
                                   20, 192,
                                   hwnd,
                                   (HMENU) SCROLLBAR_H,
                                   NULL, NULL);

            SetScrollRange(hwnd_scroll_height, SB_CTL, 0, 200, FALSE);
            SetScrollPos(hwnd_scroll_height, SB_CTL, 0, FALSE);

            hwnd_text   = CreateWindow(TEXT("static"), TEXT("Laboratory Work"),
                                   WS_VISIBLE | WS_CHILD ,
                                   30, 5,
                                   192, 20,
                                   hwnd,
                                   (HMENU) BUTTON_STATIC,
                                   NULL, NULL);

            hInstance = ((LPCREATESTRUCT) lParam) -> hInstance;                          // handle to instance for custom cursor
            oldlist=(WNDPROC) SetWindowLong (hwnd_listbox,GWL_WNDPROC,(LPARAM)ListProc);
            break;

        case WM_SETCURSOR:

            if (LOWORD(lParam) == HTCLIENT)
            {
                SetCursor(LoadCursor(hInstance, MAKEINTRESOURCE(IDI_CURSOR)));           // set custom cursor over child windows
                return TRUE;
            }
            break;

        case WM_SIZE :
        {
            cxClient = LOWORD (lParam) ;
            cyClient = HIWORD (lParam) ;

            // make windows to fit on resize
            MoveWindow(hwnd_listbox, 30, 30, cxClient/2+30, cyClient/2+60, TRUE);
            MoveWindow(hwnd_scroll_width, 30, cyClient/2+100, cxClient/2+70, 20, TRUE);
            MoveWindow(hwnd_scroll_height, cxClient/2+120, 30, 20, cyClient/2+55, TRUE);
            MoveWindow(hwnd_scroll_color, cxClient/2+80, 30, 20, cyClient/2+55, TRUE);

            // get all information about vertical scroll
            si.cbSize = sizeof(si);                     // specifies the size, in bytes
            si.fMask = SIF_RANGE | SIF_PAGE;            // specifies the scroll bar parameters to set or retrieve
            si.nMin = 0;                                // the minimum scrolling position
            si.nMax = ((340 - 100) / cyChar);           // the maximum scrolling position
            si.nPage = cyClient / cyChar;               // the page size, in device units
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);    // sets the parameters of a scroll bar

            // get all information about horizontal scroll
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((350 - 40) / cxChar);
            si.nPage = cxClient / cxChar;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

        break; // end of case statement
        }

        case WM_VSCROLL :
        {
            if((HWND)lParam == hwnd_scroll_color)    // set the custom scroll, which change the text color
            {
                switch(LOWORD(wParam))
                {
                    case SB_PAGEDOWN:

                    color_id = color_id + 15;
                    break;

                    case SB_LINEDOWN:

                        color_id=min(255,color_id + 10);
                        break;

                    case SB_PAGEUP:

                        color_id = color_id - 15;
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

            SetScrollPos(hwnd_scroll_color, SB_CTL, color_id, TRUE);
            InvalidateRect(hwnd_text,NULL,TRUE);
        }

            if((HWND)lParam == hwnd_scroll_height)   // set custom scroll, which change the window`s height
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

            SetScrollPos(hwnd_scroll_height, SB_CTL , 200 - posY, TRUE);
            SetWindowPos(hwnd, HWND_TOP, posX, posY, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
            }

            else                                     // set the default scroll
            {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwnd, SB_VERT, &si);

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

                        si.nPos = si.nPos - 1;
                        break;

                    case SB_LINEDOWN:

                        si.nPos = si.nPos + 1;
                        break;

                    case SB_PAGEUP:

                        si.nPos = si.nPos - si.nPage;
                        break;

                    case SB_PAGEDOWN:

                        si.nPos = si.nPos + si.nPage;
                        break;

                    case SB_THUMBTRACK:

                        si.nPos = si.nTrackPos;
                        break;

                    default: break;
                break;
                }

                si.fMask = SIF_POS;
                SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
                GetScrollInfo(hwnd, SB_VERT, &si);

                if(si.nPos != y)
                {
                    ScrollWindow(hwnd, 0, cyChar * (y - si.nPos), NULL, NULL);
                    UpdateWindow(hwnd);
                }
            }   // end else statement
        break;
        }       // end case statement

        case WM_HSCROLL :
        {
            if((HWND)lParam == hwnd_scroll_width)
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
                break;  // end of switch statement
                }

            SetScrollPos(hwnd_scroll_width, SB_CTL , 200 - posX, TRUE);
            SetWindowPos(hwnd, HWND_TOP, posX, posY, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
            } // end of if statement

            else
            {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwnd, SB_HORZ, &si);

                int x = si.nPos;
                switch(LOWORD(wParam))
                {
                    case SB_LINELEFT:

                        si.nPos = si.nPos - 1;
                    break;

                    case SB_LINERIGHT:

                        si.nPos = si.nPos + 1;
                    break;

                    case SB_PAGELEFT:

                        si.nPos = si.nPos - si.nPage;
                    break;

                    case SB_PAGERIGHT:

                        si.nPos = si.nPos + si.nPage;
                    break;

                    case SB_THUMBPOSITION:

                        si.nPos = si.nTrackPos;
                    break;

                    default:break;
                break;  // end of switch statement
                }

                si.fMask = SIF_POS;
                SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
                GetScrollInfo(hwnd, SB_HORZ, &si);

                if(si.nPos != x)
                {
                    ScrollWindow(hwnd, cxChar * (x - si.nPos), 0, NULL, 0);
                    UpdateWindow(hwnd);
                }
            }    // end of else
        break;   // end of case statement
        }

        case WM_COMMAND:
        {
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

                default:
                    return DefWindowProc (hwnd, message, wParam, lParam);
            break; // end of switch statement
            }

        break;
        }

        case WM_KEYDOWN:   // keyboard input
        {
            switch(wParam)
            {
                case KEY_E:  // LeftSHIFT + E
                {
                    if (GetAsyncKeyState(VK_LSHIFT))
                    {
                        DestroyWindow(hwnd);
                    }
                break;
                }

                case F1:   // F1
                {
                    if (GetAsyncKeyState(VK_F1))
                    {
                        DialogBox(hInstance, MAKEINTRESOURCE(IDI_DIALOG), hwnd, AboutDlgProc);
                    }
                 break;
                }

                case KEY_C:   // SPACE + C
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

                default: return DefWindowProc (hwnd, message, wParam, lParam);
            break;   // end of switch statement
            }
        break;       // end of case statement
        }

        case WM_CTLCOLORSTATIC:
        {
            SetTextColor((HDC)wParam,RGB(color_id + 20, 100, 255 - color_id)); // text color
            SetBkMode((HDC)wParam,TRANSPARENT);                                // transparent background
            hbrush=(HBRUSH)GetStockObject(NULL_BRUSH);                         // handle to brush, no background color
            return(LRESULT) hbrush;
        }

        case WM_CTLCOLORLISTBOX:
        {
            SetBkMode((HDC)wParam,TRANSPARENT);
            hbrush=(HBRUSH) CreateSolidBrush RGB(id_red, id_green, id_blue);  // handle to brush, listbox color
            return(LRESULT) hbrush;
        }

        case WM_DESTROY:
        {
           PostQuitMessage (0);       // send a WM_QUIT to the message queue
            break;
        }

        default:                      // for messages that we don't deal with
            return DefWindowProc (hwnd, message, wParam, lParam);
     }      // end of switch statement
return 0;   // end of WinProcedure
}

 BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) // works with DialogBox
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

LRESULT CALLBACK ListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)   // works with listbox
{
    if(message == WM_KEYDOWN && wParam == VK_DELETE)
    {
        index = SendMessage(hwnd_listbox,LB_GETCURSEL,0,0);
        sprintf(buffer,"Did you finish this laboratory work? \n%s",tasks[index].DL);
            if (MessageBox(hwnd, buffer, TEXT("Information"), MB_YESNO) == IDYES)
            {
                SendMessage(hwnd_listbox, LB_DELETESTRING, index, 0);
            }
        SetFocus(hwnd_listbox); // set focus to listbox, means that DELETE will work only inside of the listbox
    }

    if (message == WM_KEYDOWN && wParam == VK_RETURN)
    {
        index = SendMessage(hwnd_listbox,LB_GETCURSEL,0,0);
        sprintf(buffer,"%s",tasks[index].DL);
        MessageBox(hwnd, buffer, TEXT("Information"), MB_OK);
        SetFocus(hwnd_listbox); // ENTER will work only inside of the listbox
    }

    return CallWindowProc(oldlist,hwnd,message,wParam,lParam);
}

