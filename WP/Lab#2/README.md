# Windows Programming Laboratory Work #2

### Title: Advanced Form Elements. Child Windows. Basics of Working With Keyboard.


   - **Contents:**
    - The Keyboard
    - Child Window Controls
      - Scroll Bar
      - Listbox
    - Menus and Other Resources
    - Dialog Boxes

## The Application Creation Steps


### In this laboratory work I executed the following mandatory tasks:

   - **Display a dialog box on some event (ex. on clicking some button)**
    
      In order to display a dialog box I declared a specific declaration in ``resource.rc`` file :
      ```
      BEGIN
        DEFPUSHBUTTON   "OK",IDOK,60,80,50,14
        ICON            IDI_ICON,IDC_STATIC,60,20,30,50
        CTEXT           "About",IDC_STATIC,40,10,100,8
      END
      ```
      
      The Dialog Box appears when the F1 button is clicked or is selected the following item ```HELP``` -> ```About``` from menu.
    
   - **Add a system menu to your application with at least 3 items (add actions to that items)**
   
      The menu has also been declared in `resource.rc` file
      ```
      BEGIN
        POPUP "&File"
          BEGIN
            MENUITEM "&Exit",           IDI_EXIT
          END
      END
      ```
      where : 
       - `POPUP`    - top element of the menu
       - `MENUITEM` - menu item
      
     Actions to the items are added in `WM_COMMAND`, where I have attached to Menu `ID`s specific actions.
     - `EXIT`          - exit from the application
     - `DEFAULT COLOR` - change the listox color to initial one ( if is changed by pressing SPACE+C)
     - `ABOUT`         - display a DialogBox
      
   - **Add a scroll bar that will change any visible parameter of any other element (color of a text)**
    
     In order to do this I executed the following steps:
     - created the scroll bar
     ```hwnd_scroll_color = CreateWindow(TEXT("Scrollbar"), .... );```
    - ```SetScrollRange(hwnd_scroll_color, SB_CTL, 0, 255, FALSE); ``` - sets the minimum and maximum scroll box positions
      ``` SetScrollPos(hwnd_scroll_color, SB_CTL, 0, FALSE); ```       - sets the position of the scroll box (thumb)

    - added actions in `WM_VSCROLL`
      - ```InvalidateRect(hwnd_text, NULL, TRUE);``` - window's client area that must be redrawn
    
   - **Hook keyboard input. Add 2 custom events for 2 different keyboard combinations**

      - `F1`           - display a DialogBox     
      - `LSHIFT` + `E` - exit from the application
      - `SPACE`  + `C` - the color of the listbox is changed

### Tasks With Points:

  - **Add a listbox and attach some events when any element is accessed (clicked)**
    
      - `DOUBLE CLICK` or `ENTER` - a MessageBox with information about the accessed element is displayed
      - `DELETE`                  - the accessed alement is deleted
      
      In order to manage the listbox using keyboard input I created a procedure `ListProc` which allowed me to           `SetFocus` on listbox, otherwise the commands were executed even if no element was accessed.
  - **Add 2 scroll bars that will manage main window  position**
  
     Commands for this task are written in ```WM_VSCROLL``` and ```WM_HSCROLL```, where a static variable `posY` and         respectively `posX` is incremented or decremented.
  - **Customize your application by adding an icon and using different cursor in application**
 
     ``LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));``     - custom icon
     ``LoadCursor (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CURSOR));`` - custom cursor
      
     In the project I added files with extensions:
      - `.ico` -  for custom icon  
      - `.cur` -  for custom cursor
  - **Use a scroll bar to scroll through application working space. Scroll should appear only when necessary**
     
     For this task I got all information about vertical and horizontal scroll in `WM_SIZE` :
     ```
     si.cbSize = sizeof(si);                     // specifies the size, in bytes
     si.fMask = SIF_RANGE | SIF_PAGE;            // specifies the scroll bar parameters to set or retrieve
     si.nMin = 0;                                // the minimum scrolling position
     si.nMax = ((340 - 100) / cyChar);           // the maximum scrolling position
     si.nPage = cyClient / cyChar;               // the page size, in device units
     SetScrollInfo(hwnd, SB_VERT, &si, TRUE);    // sets the parameters of a scroll bar
     ```
     
     The result of my application:
     
     ![screen1] (https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/WP/Lab%232/screens/screen1.png)
     ![screen3] (https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/WP/Lab%232/screens/screen3.png)
## Conclusion

   This laboratory work was harder and more complex than first one. I developed skills in working not only with child windows, but also with scrollbars. It was shown that scrollbars can execute custom actions ( change text color, change window's position or size). Also I noticed that default scrollbars can appears only if necessry, at specific window size.
   ### Issues
   - Working with custom scrollbars:

     This task was quite difficult for me, because it took me some time to understand all scroll cases, like `SB_LINEDOWN`, `SB_PAGEUP` and others. In order to get this part done, I studied the image [Figure 1] (https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/WP/Lab%232/screens/scrollinfo.png). Another problems was with variables, which manage the scrolls work, like `color_id` or `posX`. My mistake was to declare them `local int` instead of `global` or `local static int`.
    - Hook keyboard input, add 2 custom events for 2 different keyboard combinations:
    
     Here I did not find a solution, but I think that I have to work with `SetFocus()` function. When the focus is set to the listbox or to the scrollbar, keyboard combinations `LSHIFT+E`, `SPACE+C` and `F1` do not work.
     
