#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#define BKG_WINDOW_COLOR  RGB(235, 186, 244)
#define COLOR RGB(0, 0, 0)
#define BKG_EDIT_COLOR RGB(232, 207, 239)
#define TITLE_COLOR RGB(201, 65, 266)
#define BLACK RGB(0,0,0)
#define BUTTON_STATIC 1
#define BUTTON_EDIT 2
#define BUTTON_INPUT 3
#define BUTTON_SEND_TEXT 4
#define BUTTON_CLEAR 5
#define BUTTON_FORTE 6
#define BUTTON_ARIAL 7
#define BUTTON_COURIER 11
#define BUTTON_QUIT    12

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM); // declare Windows procedure

char szClassName[ ] = "Lab#1WindowsApp";   // make the class name into a global variable

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;               // the handle of the window
    MSG messages;            // here messages to the application are saved
    WNDCLASSEX wincl;        // Data structure for the windowclass

    // The Window structure
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      // this function is called by windows
    wincl.style = CS_DBLCLKS;                 // catch double-clicks
    wincl.cbSize = sizeof (WNDCLASSEX);

    // Use default icon and mouse-pointer
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 // no menu
    wincl.cbClsExtra = 0;                      // No extra bytes after the window class
    wincl.cbWndExtra = 0;                      // structure or the window instance
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush(BKG_WINDOW_COLOR); // specific color of the background

    if (!RegisterClassEx (&wincl))     // Register the window class, and if it fails quit the program
    {
        return 0;
    }

    hwnd = CreateWindowEx (
           0,                   // extended possibilites for variation
           szClassName,         // classname
           "Lab#1::Editor ",    // tTitle Text
           WS_OVERLAPPEDWINDOW, // default window
           350,//CW_USEDEFAULT, // window strat position
           200,//CW_USEDEFAULT, // where the window ends up on the screen
           400,                 // the programs width
           348,                 // and height in pixels
           HWND_DESKTOP,        // the window is a child-window to desktop
           NULL,                // no menu
           hThisInstance,       // program Instance handler
           NULL                 // no Window Creation data
           );

    ShowWindow (hwnd, nCmdShow);  // make the window visible on the screen

    while (GetMessage (&messages, NULL, 0, 0)) // Run the message loop. It will run until GetMessage() returns 0
    {
        TranslateMessage(&messages);  // Translate virtual-key messages into character messages
        DispatchMessage(&messages);  // Send message to WindowProcedure
    }

    return messages.wParam;  // The program return-value is 0 - The value that PostQuitMessage() gave
}

//  This function is called by the Windows function DispatchMessage()

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwnd_edit, hwnd_input, hwnd_send_text, hwnd_clear,
                hwnd_forte, hwnd_arial, hwnd_courier, hwnd_quit; // handles to the child window control
    static char* mess = new char[100];                          // inputed by user message
    static int cxChar, cyChar;                                 // stores LOWORD and HIWORD
    static HFONT font_arial, font_courier, font_forte, font,
                 text_font, custom_font, font_text;          // custom fonts which will be created
    HDC hdc = NULL;                                         // handle for device context
    RECT rect;                                             // defines the coordinates of the rectagle
    LRESULT textSize;                                     // specifies the text size
    PAINTSTRUCT ps;                                      // used to paint the client area of a window.
    HBRUSH new_brush;                                   // used to create a new background for window

    switch (message)                                  // handle the messages
    {
    case WM_CREATE:

        hwnd_edit = CreateWindow(TEXT("EDIT"), TEXT(" "),         // edit window class name, no window caption
                               WS_VISIBLE | WS_CHILD | WS_BORDER,// window styles, make border
                               20, 45,                          // initial horizontal | vertical position of the window
                               100, 120,                       // width | height
                               hwnd,                          // handle of the parent window
                               (HMENU) BUTTON_EDIT,          // specifies the child-window identifier (BUTTON_EDIT)
                               NULL, NULL);                 // aditional parameters, not used

        hwnd_input = CreateWindow("BUTTON", "Input",                   // button window
                               WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON ,
                               120, 170,
                               100, 25,
                               hwnd,
                               (HMENU) BUTTON_INPUT,
                               NULL, NULL);

        hwnd_send_text = CreateWindow(TEXT("EDIT"), TEXT(" "),       // edit window
                               WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | WS_VSCROLL
                               | ES_READONLY | ES_AUTOVSCROLL,
                               NULL, NULL,
                               100, 120,
                               hwnd,
                               (HMENU) BUTTON_SEND_TEXT,
                               NULL, NULL);

        hwnd_clear = CreateWindow(TEXT("BUTTON"), TEXT("CLEAR"),
                               WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                               150, 170,
                               100, 25,
                               hwnd,
                               (HMENU) BUTTON_CLEAR,
                               NULL, NULL);

        hwnd_forte = CreateWindow(TEXT("BUTTON"), TEXT("FORTE"),
                               WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON ,
                               20, 200,
                               200, 75,
                               hwnd,
                               (HMENU) BUTTON_FORTE,
                               NULL, NULL);

        hwnd_arial = CreateWindow(TEXT("BUTTON"), TEXT("ARIAL"),
                               WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                               370, 150,
                               100, 25,
                               hwnd,
                               (HMENU) BUTTON_ARIAL,
                               NULL, NULL);

        hwnd_courier = CreateWindow(TEXT("BUTTON"), TEXT("COURIER"),
                               WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                               370, 150,
                               100, 25,
                               hwnd,
                               (HMENU) BUTTON_COURIER,
                               NULL, NULL);

        hwnd_quit  = CreateWindow(TEXT("BUTTON"), TEXT("QUIT"),
                               WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                               NULL, NULL,
                               NULL, NULL,
                               hwnd,
                               (HMENU) BUTTON_QUIT,
                               NULL, NULL);
        break;

    case WM_SIZE:

        cxChar = LOWORD(lParam);
        cyChar = HIWORD(lParam);

        // these functions make elements to rezise too, when window is resized
        MoveWindow(hwnd_send_text, 20, 45, cxChar/2-20, cyChar/2+10, TRUE);
        MoveWindow(hwnd_forte, cxChar/2+20, 55, 100, 30.25, TRUE);
        MoveWindow(hwnd_arial, cxChar/2+20, 90, 100, 30.25, TRUE);
        MoveWindow(hwnd_courier, cxChar/2+20, 125, 100, 30.25, TRUE);
        MoveWindow(hwnd_clear, cxChar/2+20, 160, 100, 30.25, TRUE);
        MoveWindow(hwnd_edit, 20, cyChar/2+70, cxChar/2-20, cyChar/2-80, TRUE);
        MoveWindow(hwnd_input, cxChar/2+20, cyChar/2+75, 100, 30.25, TRUE);
        MoveWindow(hwnd_quit, cxChar/2+20, cyChar/2+109.25, 100, 30.25, TRUE);

        break;

    case WM_GETMINMAXINFO:                              // set the minimum window size
        {
           LPMINMAXINFO pInfo = (LPMINMAXINFO) lParam;
           pInfo ->ptMinTrackSize.x = 320;             // minimal width
           pInfo ->ptMinTrackSize.y = 348;            // minimal height
        }
        break;

    case WM_COMMAND:

        switch(LOWORD(wParam))
        {
        case BUTTON_INPUT:

            textSize = SendMessage(hwnd_edit, WM_GETTEXT, 100, (LPARAM)mess); // text size
            mess[textSize] = _T('\0');                                       // initialization with null character
            SendMessage(hwnd_send_text, EM_REPLACESEL, 0, (LPARAM)mess);    // add inputed text to window
            SendMessage(hwnd_edit, WM_SETTEXT,NULL, (LPARAM) " ");         // erase edit window
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;

        case BUTTON_ARIAL:

            font = CreateFont(0, 0, 0, 0, FW_DONTCARE, false, false, false,
                              DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, FF_DONTCARE, TEXT("Arial"));// creat Arial font, using default parameters
            SendMessage(hwnd_send_text, WM_SETFONT, (WPARAM)font, TRUE);  // output changed text on the screen, in send_text window
            break;

        case BUTTON_FORTE:

            font = CreateFont(0, 0, 0, 0, FW_DONTCARE, false, false, false,
                              DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, FF_DONTCARE, TEXT("Forte")); // create Forte font
            SendMessage(hwnd_send_text, WM_SETFONT, (WPARAM)font, TRUE);
            break;

        case BUTTON_COURIER:

            font = CreateFont(0, 0, 0, 0, FW_DONTCARE, false, false, false,
                              DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, FF_DONTCARE, TEXT("Courier")); // create Courier font
            SendMessage(hwnd_send_text, WM_SETFONT, (WPARAM)font, TRUE);
            break;

        case BUTTON_CLEAR:

            SendMessage(hwnd_send_text, WM_SETTEXT, NULL, NULL);      // erase the data from send_text window
            break;

        case BUTTON_QUIT:

            DestroyWindow(hwnd);                                // exit from program
            break;
        }
    break;

        case WM_SYSCOMMAND:                                 // change behavior of different window actions
                switch(wParam)
                {
                case SC_MINIMIZE:

                    SetWindowPos(hwnd, HWND_TOP, 20, 20, 700, 700, SWP_SHOWWINDOW);  // change dimensions and window position
                    break;

                case SC_MAXIMIZE:

                    if (MessageBox(hwnd, "Do you want to resize the window?", "Attention!", MB_YESNO) == IDYES)
                    {
                        SetWindowPos(hwnd, HWND_TOP, 500, 200, 550, 400, SWP_SHOWWINDOW); // return the window in initial position, after minimize
                    }
                    break;

                case SC_CLOSE:

                    MessageBox(hwnd, "Press QUIT button", " Attention!", MB_OK);     // desplay mesage box
                    break;

                default:
                    return  DefWindowProc(hwnd, message, wParam, lParam);
                }
                break;                        // switch break
            break;                           //  case break

        case WM_PAINT:                     // makes a request to paint a portion of an application's window.
            {

            hdc = BeginPaint(hwnd, &ps); //function prepares the  window for painting

            // create 3 fonts for buttons and one for text
            font_courier = CreateFont(0 , 0, 0, 0, FW_DONTCARE, false, false, false,
                                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                      DEFAULT_QUALITY, FF_DONTCARE, "Courier");
            font_forte   = CreateFont(0, 0, 0, 0, FW_DONTCARE, false, false, false,
                                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                      DEFAULT_QUALITY, FF_DONTCARE, "Forte");
            font_arial   = CreateFont(0, 0, 0, 0, FW_DONTCARE, false, false, false,
                                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                      DEFAULT_QUALITY, FF_DONTCARE, "Arial");
            font_text    = CreateFont(10, 0, 0, 0, FW_DONTCARE, false, false, false,
                                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                      DEFAULT_QUALITY, FF_DONTCARE, "Bodnoni MT");

            //sending informaton about fonts to buttons
            SendMessage(hwnd_courier, WM_SETFONT, WPARAM(font_courier), TRUE);
            SendMessage(hwnd_forte, WM_SETFONT, WPARAM(font_forte), TRUE);
            SendMessage(hwnd_arial, WM_SETFONT, WPARAM(font_arial), TRUE);

            SetBkMode(hdc, TRANSPARENT);  // set transparent background
            GetClientRect(hwnd, &rect);  // retrieves the coordinates of a window's client area

            text_font  = (HFONT)SelectObject(hdc, font_forte);   // setting new font for text
            SetTextColor(hdc, TITLE_COLOR);                     // setting new text color
            DrawText(hdc, " Let's play ", -1, &rect, DT_CENTER | DT_TOP);  // text which will pe shown
            DrawText(hdc, "\n with fonts", -1, &rect, DT_CENTER | DT_TOP);

            custom_font = (HFONT)SelectObject(hdc, font_text);
            SetTextColor (hdc, BLACK);
            DrawText(hdc, "WP, 2014", -1, &rect, DT_SINGLELINE | DT_BOTTOM | DT_LEFT);

            EndPaint(hwnd, &ps);           // end paint
            }
            break;

        case WM_CTLCOLOREDIT:              // change color for edit window
             {
                if(BUTTON_EDIT == GetDlgCtrlID((HWND)lParam))
                    {
                        hdc = (HDC)wParam;
                        new_brush = CreateSolidBrush(BKG_EDIT_COLOR);  // create a new color for window
                        SetBkMode(hdc, TRANSPARENT); //setting transparent background, otherwise the line
                                                    // where text is typing will be of default color
                        return (LONG)new_brush;
                     }
             }
            break;

        case WM_DESTROY:
            PostQuitMessage (0);       // send a WM_QUIT to the message queue
            break;
        default:                      // for messages that we don't deal with
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
