#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include <iostream>

 using namespace std;

POINT pointPen;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

int get_width(HWND);                        // width of border
int get_eraser_width(HWND);                 // width of eraser tool
COLORREF get_color(HWND, HWND, HWND);       // color of border
COLORREF get_color_fill(HWND, HWND, HWND);  // color for fill

/*  Make the class name into a global variable  */
char szClassName[ ] = "labul 3";
HINSTANCE hInstance;

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;               // This is the handle for our window
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                        /* No menu */
    wincl.cbClsExtra = 0;                             /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                             /* structure or the window instance */
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(240, 240, 240));  /* Use Windows's default colour as the background of the window */

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Lab#3::Paint",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           700,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

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
    static HWND hwnd_pen, hwnd_line, hwnd_rect, hwnd_ellipse, hwnd_eraser, hwnd_width, hwnd_eraser_width;
    static HWND hwnd_red, hwnd_green, hwnd_blue, hwnd_rgb, hwnd_bezier, hwnd_check;
    static HWND hwnd_red_fill, hwnd_green_fill, hwnd_blue_fill, hwnd_clear;
    int width;
    int xMouse, yMouse;

    static POINT line, lineStart;

    static BOOL ellipse_started;
    static RECT ellipse;

    static BOOL rectangle_started;
    static RECT rectangle;

    static int bezierStage = 0;
    static POINT bezierPoints[4];
    static POINT bezierPoint;

    static RECT gradient = {470, 450, 630, 480};
    static RECT area     = {30, 30, 450, 490};
    static RECT temp_rect;

    static HDC hdcMem, hdcLine, hdcEllipse, hdcRect;
    static BITMAP bitmap, linebit, ellipsebit, rectbit;
    static HBITMAP hbmplogo = NULL ;
    static HBITMAP hLine = NULL;
    static HBITMAP hEllipse = NULL;
    static HBITMAP hRect    = NULL;
    static COLORREF colorr, fill_color;

    hbmplogo = (HBITMAP)LoadImage(hInstance, "pen.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmplogo, sizeof(bitmap), &bitmap);

    hLine = (HBITMAP)LoadImage(hInstance, "line.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hLine, sizeof(linebit), &linebit);

    hEllipse = (HBITMAP)LoadImage(hInstance, "ellipse.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hEllipse, sizeof(ellipsebit), &ellipsebit);

    hRect = (HBITMAP)LoadImage(hInstance, "rect.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hRect, sizeof(rectbit), &rectbit);

	HDC hDC;
    PAINTSTRUCT Ps;
	HBRUSH  NewBrush, NewBrush1;
	HPEN linePen;
	HPEN linePen2;
	HPEN linePen3;
	HPEN hPenOld, hPenOld2;
    HDC hdc = GetDC(hwnd);

    POINT Pt[4] = { {  20,  12 }, {  88, 246 }, { 364, 192 }, { 250,  48 } };
    PolyBezierTo(hdc,Pt,4);

    switch (message)
    {
     case WM_CREATE:
     {
        hwnd_pen = CreateWindow( TEXT("Button"), TEXT("Pen"),
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    470, 40,
                    45, 20,
                    hwnd,(HMENU)IDI_PEN,
                    NULL, NULL);

        hwnd_line = CreateWindow( TEXT("Button"), TEXT("Line"),
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    470, 65,
                    50, 20,
                    hwnd,(HMENU)IDI_LINE,
                    hInstance, NULL);

        hwnd_ellipse = CreateWindow( TEXT("Button"), TEXT("Ellispe"),
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    470, 90,
                    65, 20,
                    hwnd,(HMENU)IDI_ELIPSE,
                    NULL, NULL);

        hwnd_rect = CreateWindow( TEXT("Button"), TEXT("Rectangle"),
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    470, 115,
                    85, 20,
                    hwnd,(HMENU)IDI_LINE,
                    NULL, NULL);

        hwnd_bezier = CreateWindow( TEXT("Button"), TEXT("Beizier"),
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    470, 140,
                    90, 20,
                    hwnd,(HMENU)IDI_LINE,
                    NULL, NULL);

        hwnd_eraser = CreateWindow( TEXT("Button"), TEXT("Eraser"),
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    470, 165,
                    90, 20,
                    hwnd,(HMENU)IDI_LINE,
                    NULL, NULL);

         hwnd_eraser_width = CreateWindow(TEXT("Edit"), TEXT("10"),
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    560, 165,
                    30, 20,
                    hwnd,(HMENU)IDI_WIDTH,
                    NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Border style:"),
                     WS_VISIBLE | WS_CHILD | BS_GROUPBOX ,
                     470, 195,
                     160, 100,
                     hwnd, (HMENU)500,
                     NULL, NULL);

        CreateWindow(TEXT("Static"), TEXT("Width:"),
                     WS_VISIBLE | WS_CHILD,
                     475, 220,
                     45, 20,
                     hwnd,(HMENU)550,
                     NULL, NULL);

        hwnd_width = CreateWindow( TEXT("Edit"), TEXT("4"),
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    530, 215,
                    30, 20,
                    hwnd,(HMENU)IDI_WIDTH,
                    NULL, NULL);

        CreateWindow(TEXT("Static"), TEXT("Color:"),
                     WS_VISIBLE | WS_CHILD,
                     475, 270,
                     45, 20,
                     hwnd,(HMENU)550,
                     NULL, NULL);

        hwnd_red = CreateWindow(TEXT("Edit"), TEXT("0"),
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    530, 270,
                    30, 20,
                    hwnd,(HMENU)IDI_R,
                    NULL, NULL);

        hwnd_green = CreateWindow(TEXT("Edit"), TEXT("0"),
                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                     560, 270,
                     30, 20,
                     hwnd,(HMENU)IDI_G,
                     NULL, NULL);

        hwnd_blue = CreateWindow(TEXT("Edit"), TEXT("0"),
                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                     590, 270,
                     30, 20,
                     hwnd,(HMENU)IDI_B,
                     NULL, NULL);

        hwnd_rgb = CreateWindow (TEXT("STATIC"), TEXT("  R  |  G   |  B"),
                     WS_VISIBLE | WS_CHILD,
                     530, 250,
                     90, 20,
                     hwnd, (HMENU)IDI_RGB,
                     NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Filling style:"),
                     WS_VISIBLE | WS_CHILD | BS_GROUPBOX ,
                     470, 300,
                     160, 100,
                     hwnd, (HMENU)600,
                     NULL, NULL);

        CreateWindow(TEXT("Static"), TEXT("Fill it?:"),
                     WS_VISIBLE | WS_CHILD,
                     475, 325,
                     45, 20,
                     hwnd,(HMENU)550,
                     NULL, NULL);

        hwnd_check = CreateWindow(TEXT("BUTTON"), TEXT(" "),
                     WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                     530, 325,
                     50, 20,
                     hwnd,(HMENU)IDI_FILL,
                     NULL, NULL);

        CreateWindow(TEXT("Static"), TEXT("Color:"),
                     WS_VISIBLE | WS_CHILD,
                     475, 375,
                     45, 20,
                     hwnd,(HMENU)590,
                     NULL, NULL);

        CreateWindow (TEXT("STATIC"), TEXT("  R  |  G   |  B"),
                     WS_VISIBLE | WS_CHILD,
                     530, 355,
                     90, 20,
                     hwnd, (HMENU)700,
                     NULL, NULL);

        hwnd_red_fill = CreateWindow(TEXT("Edit"), TEXT("255"),
                      WS_VISIBLE | WS_CHILD | WS_BORDER,
                      530, 375,
                      30, 20,
                      hwnd,(HMENU)IDI_R1,
                      NULL, NULL);

        hwnd_green_fill = CreateWindow(TEXT("Edit"), TEXT("255"),
                      WS_VISIBLE | WS_CHILD | WS_BORDER,
                      560, 375,
                      30, 20,
                      hwnd,(HMENU)IDI_G1,
                      NULL, NULL);

        hwnd_blue_fill = CreateWindow(TEXT("Edit"), TEXT("255"),
                      WS_VISIBLE | WS_CHILD | WS_BORDER,
                      590, 375,
                      30, 20,
                      hwnd,(HMENU)IDI_B1,
                      NULL, NULL);

        hwnd_clear = CreateWindow(TEXT("Button"), TEXT("Clear all"),
                      WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                      470, 410,
                      160, 30,
                      hwnd, (HMENU)IDI_CLEAR,
                      NULL, NULL);
    break;
     }

     case WM_COMMAND:
     {
         switch(LOWORD(wParam))
         {
            case IDI_CLEAR:
                InvalidateRect(hwnd, &area, FALSE);
				InvalidateRect(hwnd, &area, TRUE);
            break;
         }

     }

    case WM_MOUSEMOVE:
    {
        xMouse = GET_X_LPARAM(lParam);
        yMouse = GET_Y_LPARAM(lParam);

         if (xMouse > 30 && xMouse < 450 && yMouse > 30 && yMouse < 490 )  // defines the workind area ( borders )
         {
            if(wParam & MK_LBUTTON)
            {
                if (Button_GetCheck(hwnd_pen) == BST_CHECKED)
                {
                    width = get_width(hwnd_width);                       // function call, determines the width of border
                    colorr = get_color(hwnd_red, hwnd_green, hwnd_blue); // function call, determines the color of border

                    linePen = CreatePen(PS_SOLID, width, colorr);        // create the brush
                    SelectObject(hdc, linePen);

                    MoveToEx(hdc, xMouse, yMouse, NULL);
                    LineTo(hdc, pointPen.x, pointPen.y);
                    DeleteObject(linePen);

                    pointPen.x = xMouse;
                    pointPen.y = yMouse;
                }

                if (Button_GetCheck(hwnd_line) == BST_CHECKED)
                {
                    width = get_width(hwnd_width);
                    colorr = get_color(hwnd_red, hwnd_green, hwnd_blue);

                    linePen = CreatePen(PS_SOLID, width, RGB(255, 255, 255));  // makes the background of the line - white
                    SelectObject(hdc, linePen);
                    MoveToEx(hdc, lineStart.x, lineStart.y, NULL);
                    LineTo(hdc, line.x, line.y);
                    DeleteObject(linePen);

                    linePen = CreatePen(PS_SOLID, width, colorr);            // makes the brush for line
                    SelectObject(hdc, linePen);
                    MoveToEx(hdc, lineStart.x, lineStart.y, NULL);
                    LineTo(hdc, xMouse, yMouse);
                    DeleteObject(linePen);

                    line.x = xMouse;
                    line.y = yMouse;
                }

                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwnd_eraser) == BST_CHECKED))
                {
                    int eraser_width = get_eraser_width(hwnd_eraser_width);  // function call, the width of eraser tool

                    rectangle.left = xMouse - (eraser_width / 2);
                    rectangle.right = xMouse + (eraser_width / 2);
                    rectangle.top = yMouse - (eraser_width / 2);
                    rectangle.bottom = yMouse + (eraser_width / 2);
                    InvalidateRect(hwnd, &rectangle, FALSE);
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                }

            }
        }
      break;
      }

      case WM_LBUTTONUP :
      {
          xMouse = GET_X_LPARAM(lParam);
          yMouse = GET_Y_LPARAM(lParam);

          if (xMouse > 30 && xMouse < 450 && yMouse > 30 && yMouse < 490 )
          {
            if (Button_GetCheck(hwnd_line) == BST_CHECKED)
            {
                width = get_width(hwnd_width);
                colorr = get_color(hwnd_red, hwnd_green, hwnd_blue);

                SelectObject(hdc, CreatePen(PS_SOLID, width, RGB(255, 255, 255)));
                MoveToEx(hdc, lineStart.x, lineStart.y, NULL);
                LineTo(hdc, line.x, line.y);

                linePen = CreatePen(PS_SOLID, width, colorr);
                SelectObject(hdc, linePen);
                MoveToEx(hdc, lineStart.x, lineStart.y, NULL);
                LineTo(hdc, xMouse, yMouse);
                DeleteObject(linePen);

                line.x = xMouse;
                line.y = yMouse;
            }

            if(ellipse_started)
            {
                width = get_width(hwnd_width);
                colorr = get_color(hwnd_red, hwnd_green, hwnd_blue);

                linePen2 = CreatePen(PS_DASHDOTDOT, width, colorr);

                if (Button_GetCheck(hwnd_check) == BST_CHECKED)          // check if the user want to fill the figure
                {
                    fill_color = get_color_fill(hwnd_red_fill, hwnd_green_fill, hwnd_blue_fill);
                    NewBrush   = CreateSolidBrush(fill_color);
                }
                else
                {
                   NewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);       // if not, the brush is NULL
                }

                SelectObject(hdc, linePen2);
                SelectObject(hdc, NewBrush);

                Ellipse(hdc, ellipse.left, ellipse.top, xMouse, yMouse);
                DeleteObject(linePen2);
                DeleteObject(NewBrush);

                ellipse_started = false;
            }

            if(rectangle_started)
            {
                width = get_width(hwnd_width);
                colorr = get_color(hwnd_red, hwnd_green, hwnd_blue);

                linePen2=CreatePen(PS_DASHDOTDOT, width, colorr);

                if (Button_GetCheck(hwnd_check) == BST_CHECKED)
                {
                    fill_color = get_color_fill(hwnd_red_fill, hwnd_green_fill, hwnd_blue_fill);
                    NewBrush   = CreateSolidBrush(fill_color);
                }
                else
                {
                   NewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
                }

                SelectObject(hdc, linePen2);
                SelectObject(hdc, NewBrush);
                Rectangle(hdc, rectangle.left, rectangle.top, xMouse, yMouse);

                DeleteObject(linePen2);
                DeleteObject(NewBrush);

                rectangle_started = false;
            }

            if(bezierStage == 1)             // bazier check point
            {
                bezierPoint.x = xMouse;
                bezierPoint.y = yMouse;
                bezierPoints[1] = bezierPoint;
                bezierStage = 2;
            }

            if(bezierStage == 3)
            {
                bezierPoint.x = xMouse;
                bezierPoint.y = yMouse;
                bezierPoints[3] = bezierPoint;
                bezierStage = 0;
                SelectObject(hdc, linePen3);
                PolyBezier(hdc, bezierPoints, 4);
                DeleteObject(linePen3);
            }
        }
    break;
    }

    case WM_LBUTTONDOWN:
    {
        xMouse = GET_X_LPARAM(lParam);
        yMouse = GET_Y_LPARAM(lParam);

        if (xMouse > 30 && xMouse < 450 && yMouse > 30 && yMouse < 490 )
        {
            if(wParam == MK_LBUTTON)
            {
                if (Button_GetCheck(hwnd_pen) == BST_CHECKED)
                {
                    pointPen.x = xMouse;
                    pointPen.y = yMouse;
                }

                if (Button_GetCheck(hwnd_line) == BST_CHECKED)
                {
                    lineStart.x = xMouse;
                    lineStart.y = yMouse;
                    line.x = xMouse;
                    line.y = yMouse;
                }

                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwnd_ellipse) == BST_CHECKED))
                {
                    ellipse.left = xMouse;
                    ellipse.top = yMouse;
                    ellipse_started = true;
                }

                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwnd_rect) == BST_CHECKED))
                {
                    rectangle.left = xMouse;
                    rectangle.top = yMouse;
                    rectangle_started = true;
                }

                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwnd_bezier) == BST_CHECKED))
                {
                    if(bezierStage == 0)
                    {
                        bezierPoint.x = xMouse;
                        bezierPoint.y = yMouse;
                        bezierPoints[0] = bezierPoint;
                        bezierStage = 1;
                    }
                    else
                    {
                        bezierPoint.x = xMouse;
                        bezierPoint.y = yMouse;
                        bezierPoints[2] = bezierPoint;
                        bezierStage = 3;
                    }
                }
            }
        }
   break;
    }

    case WM_PAINT:
    {
        hDC = BeginPaint(hwnd, &Ps);

        HPEN hLinePen;          // used to draw a line, without mouse
        COLORREF qLineColor;    // color of line

        qLineColor = RGB(255, 150, 0);                   // the color of line
        hLinePen = CreatePen(PS_SOLID, 7, qLineColor);   // the width of line is 7
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);

        MoveToEx(hdc, 450, 30, NULL);                   // defines the x, y coordonates of upper point
        LineTo(hdc, 450, 490);                          // defines the x, y coordonates of lower point

        MoveToEx(hdc, 30, 30, NULL);
        LineTo(hdc, 30, 490);

        MoveToEx(hdc, 30, 30, NULL);
        LineTo(hdc, 450, 30);

        MoveToEx(hdc, 30, 490, NULL);
        LineTo(hdc, 450, 490);

        SelectObject(hdc, hPenOld);
        DeleteObject(hLinePen);

        HPEN hLinePen2;
        COLORREF qLineColor2;
        qLineColor2 = RGB(215, 0, 0);

        hLinePen2 = CreatePen(PS_SOLID, 10, qLineColor2);
        hPenOld2 = (HPEN)SelectObject(hdc, hLinePen2);

        MoveToEx(hdc, 0, 0, NULL);
        LineTo(hdc, 0, 560);

        MoveToEx(hdc, 0, 560, NULL);
        LineTo(hdc, 680, 560);

        MoveToEx(hdc, 680, 0, NULL);
        LineTo(hdc, 680, 560);

        MoveToEx(hdc, 0, 0, NULL);
        LineTo(hdc, 680, 0);

        SelectObject(hdc, hPenOld2);
        DeleteObject(hLinePen2);

        NewBrush1 = CreateSolidBrush(RGB(255, 255, 255));    // color of working area

        FillRect(hdc, &area, NewBrush1);
        DeleteObject(NewBrush1);

        // Draw logo
        hdcMem = CreateCompatibleDC(hdc);
        SelectObject(hdcMem, hbmplogo);
        BitBlt(hdc, 515, 40, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
        DeleteDC(hdcMem);

        hdcLine = CreateCompatibleDC(hdc);
        SelectObject(hdcLine, hLine);
        BitBlt(hdc, 525, 65, linebit.bmWidth, linebit.bmHeight, hdcLine, 0, 0, SRCCOPY);
        DeleteDC(hdcLine);

        hdcEllipse = CreateCompatibleDC(hdc);
        SelectObject(hdcEllipse, hEllipse);
        BitBlt(hdc, 538, 90, ellipsebit.bmWidth, ellipsebit.bmHeight, hdcEllipse, 0, 0, SRCCOPY);
        DeleteDC(hdcEllipse);

        hdcRect = CreateCompatibleDC(hdc);
        SelectObject(hdcRect, hRect);
        BitBlt(hdc, 555, 115, rectbit.bmWidth, rectbit.bmHeight, hdcRect, 0, 0, SRCCOPY);
        DeleteDC(hdcRect);

        HBRUSH hBrush;

        temp_rect.top = gradient.top;
        temp_rect.bottom = gradient.bottom;

        for(int i = 0; i < (gradient.right - gradient.left); i++)
        {
            int blue;
            blue = i * 255 / (gradient.right - gradient.left);
            temp_rect.left  = gradient.left  + i;
            temp_rect.right = gradient.left + i + 1;
            hBrush = CreateSolidBrush(RGB(0, 0, blue));
            FillRect(hdc, &temp_rect, hBrush);
            DeleteObject(hBrush);
        }
        EndPaint(hwnd, &Ps);

    break;
    }
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

int get_width(HWND input)
{
    static int result;
    static int iLength = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input, WM_GETTEXT, iLength+1, (LPARAM)szText);
    result = atoi(szText);
    _itoa(result, szText, 10);
    SendMessage(input, WM_SETTEXT, 0, (LPARAM)szText);
    free(szText);
    return result;
}

int get_eraser_width(HWND input)
{
    static int result;
    static int iLength = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input, WM_GETTEXT, iLength+1, (LPARAM)szText);
    result = atoi(szText);
    free(szText);
    return result;
}

COLORREF get_color(HWND input1, HWND input2, HWND input3)
{
    static COLORREF color;
    static int red, green, blue;

    int iLength = SendMessage(input1, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input1, WM_GETTEXT, iLength+1, (LPARAM)szText);
    red = atoi(szText);

    iLength = SendMessage(input2, WM_GETTEXTLENGTH, 0, 0);
    szText = (char*)malloc(iLength+1);
    SendMessage(input2, WM_GETTEXT, iLength+1, (LPARAM)szText);
    green = atoi(szText);

    iLength = SendMessage(input3, WM_GETTEXTLENGTH, 0, 0);
    szText = (char*)malloc(iLength+1);
    SendMessage(input3, WM_GETTEXT, iLength+1, (LPARAM)szText);
    blue = atoi(szText);
    free(szText);

    color = RGB (red, green, blue);

    return color;
}

COLORREF get_color_fill(HWND input1, HWND input2, HWND input3)
{
    static COLORREF color;
    static int red, green, blue;

    int iLength = SendMessage(input1, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input1, WM_GETTEXT, iLength+1, (LPARAM)szText);
    red = atoi(szText);

    iLength = SendMessage(input2, WM_GETTEXTLENGTH, 0, 0);
    szText = (char*)malloc(iLength+1);
    SendMessage(input2, WM_GETTEXT, iLength+1, (LPARAM)szText);
    green = atoi(szText);

    iLength = SendMessage(input3, WM_GETTEXTLENGTH, 0, 0);
    szText = (char*)malloc(iLength+1);
    SendMessage(input3, WM_GETTEXT, iLength+1, (LPARAM)szText);
    blue = atoi(szText);
    free(szText);

    color = RGB (red, green, blue);

    return color;
}


