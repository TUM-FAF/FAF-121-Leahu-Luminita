# Windows Programming Laboratory Work #1

# Title: Window. Window handling. Basic window’s form elements


  - **Contents:**
    - Win32 API
    - GIT
    - Programming Style Guidelines
    - Window
    - Button
    - Text Input
    - Text

##The Application Creation Steps

###During this laboratory work I executed the following Mandatory Tasks:

    - **Create a Windows application**
      In order to do this I used function ```CreateWindowEx ``` with size : 400 x 348 and name : Lab#1::Editor.
    - **Add 2 buttons to window: one with default styles, one with custom styles (font family)**
      To change font family of button I used 
      ```CreateFont(0 , 0, 0, 0, FW_DONTCARE, false, false, false,
                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                    DEFAULT_QUALITY, FF_DONTCARE, "Courier");```
      function with default parameters, which creates ```Courier``` font. In order to send it to specific button function
      ```SendMessage(hwnd_courier, WM_SETFONT, WPARAM(font_courier), TRUE); ``` is used.
    - **Add 2 text inputs to window: one with default styles, one with custom styles (background)**
      I used ```WM_CTLCOLOREDIT``` case and ```CreateSolidBrush`` to change background color of text input. 
    - **Add 2 text elements to window: one with default styles, one with custom styles (text color, font family)***
      In order to do this I used 4 functions:
      ```CreateFont();```                                                              - to create font
      ```(HFONT)SelectObject(hdc, font_forte);```                                      - set the font to text element
      ```SetTextColor (hdc, BLACK);```                                                 - set text color
      ```DrawText(hdc, "WP, 2014", -1, &rect, DT_SINGLELINE | DT_BOTTOM | DT_LEFT);``` - create the text which will be written

###And Tasks With Points:
    - **Make elements to fit window on resize **
     This is done using ```WM_GETMINMAXINFO:``` , which set the minimum window size.
    - **Make elements to interact or change other elements (1 pt for 2 different interactions) **
     The interactions are:
     1. By clicking the ```INPUT``` button, text from firs input window is send to second one.
     2. By clicking the ```CLEAR``` button, all text from second input window is erased.
     3. By clicking the ```FONT`` buttons (```FORTE```, ```ARIAL```, ```COURIER```), the text font is changed.

     All are done using ```SendMessage();``` function in ```WM_COMMAND```

     4. By clicking the ```QUIT``` button, the user exit from program.

     Is implementing using ```DestroyWindow(hwnd);``` function.
    - **Change behavior of different window actions (at least 3). **
     The different window actions are defined in ```WM_SYSCOMMAND```:
     1. By clicking ```MINIMIZE``` button the window change its position
      ```SetWindowPos(hwnd, HWND_TOP, 20, 20, 700, 700, SWP_SHOWWINDOW);```

    2. By clicking ```MAXIMIZE``` button a MessageBox appears and if the ```YES`` button clicked the window also change its position
     ```if (MessageBox(hwnd, "Do you want to resize the window?", "Attention!", MB_YESNO) == IDYES)
         {
            SetWindowPos(hwnd, HWND_TOP, 500, 200, 550, 400, SWP_SHOWWINDOW); 
         }
      ```
    3. By clicking ```CLOSE``` button a MessageBox appears
     ```MessageBox(hwnd, "Press QUIT button", " Attention!", MB_OK);```

    - **Write your own PSG  and argue why it is better (for you) **

##Programming Style Guide

**Naming**
 Name of variables should have a reference to its purpose, like ```hwnd_input``` , ```font_arial```,  in order to make code more understandable. Simple letters are used only as indexes (```i```, ```j```), widely used names like ```rect```, ```cxChar```, ```cyChar``` are unchanged.

 ```#define```s  are written in snake_case, with all caps and on the first position word ```BUTTON``, like ```BUTTON_CLEAR```
 ```global``` variables are written in snake_case if are from two words, like ```text_font```, handles to the child window control have on the first position word ```hwnd``, as ```hwnd_quit```

 ***Indentation***
  ```Allman style```. This style puts the brace associated with a control statement on the next line, indented to the same level as the control statement. Statements within the braces are indented to the next level. 
  ``` if (a == b)
      {
        ...
      }

  Braces are used even if is just one instruction.

***Spaces***
 Usualy are used some white spaces, like:
 ``` DefWindowProc (hwnd, message, wParam, lParam);``` or ```cxChar = LOWORD(lParam);```

 ***Comments***
  Comments are written before the code line, like
  ```     // comment1
         // comment2
        // comment3
  ```
  When the same comment have to be written to more than two lines, is written before first one, like:
  ``` //sending informaton about fonts to buttons
      SendMessage(hwnd_courier, WM_SETFONT, WPARAM(font_courier), TRUE);
      SendMessage(hwnd_forte, WM_SETFONT, WPARAM(font_forte), TRUE);
      SendMessage(hwnd_arial, WM_SETFONT, WPARAM(font_arial), TRUE);


##Conclusion
   
During this laboratory work I was developed skills in working with win32 API. It was shown that performing certain functions allows us to manage the relations between buttons.   
After the verification of the results outputted by the computer, the efficiency of the program is proved. 

