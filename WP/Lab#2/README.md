# Windows Programming Laboratory Work #2

### Title: Advanced Form Elements. Child Windowses. Basics of Working With Keyboard.


   - **Contents:**
    - The Keyboard
    - Child Window Controls
      - Scroll Bar
      - Listbox
    - Menus and Other Resources
    - Dialog Boxes

## The Application Creation Steps


### During this laboratory work I executed the following Mandatory Tasks:

   - **Display a dialog box on some event (ex. on clicking some button)**
    
      In order to display a dialog box I have declared a specific declaration in ``resource.rc`` file :
      ```
      BEGIN
        DEFPUSHBUTTON   "OK",IDOK,60,80,50,14
        ICON            IDI_ICON,IDC_STATIC,60,20,30,50
        CTEXT           "About",IDC_STATIC,40,10,100,8
      END
      ```
      
      The Dialog Box appears when F1 button is clicked or is selected item ```HELP``` -> ```About``` from menu.
    
   - **Add a system menu to your application with at least 3 items (add actions to that items)**
   
      The menu also has been declared in `resource.rc` file
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
      
     Actions to the items are added in `WM_COMMAND`, where I have declared to Menu `ID`s specific actions. 
      
   - **Add a scroll bar that will change any visible parameter of any other element (color of a text)**
    
     In order to do this I have executed the following steps:
     - have created the scroll bar
     ```hwnd_scroll_color = CreateWindow(TEXT("Scrollbar"), .... );```
    - ```SetScrollRange(hwnd_scroll_color, SB_CTL, 0, 255, FALSE); ``` - sets the minimum and maximum scroll box positions
      ``` SetScrollPos(hwnd_scroll_color, SB_CTL, 0, FALSE); ```       - sets the position of the scroll box (thumb)

    - have added actions in `WM_VSCROLL`
      - ```InvalidateRect(hwnd_text, NULL, TRUE);``` - window's client area that must be redrawn
    
   - **Hook keyboard input. Add 2 custom events for 2 different keyboard combinations**

      - `F1`           - display a DialogBox     
      - `LSHIFT` + `E` - exit from application
      - `SPACE`  + `C` - the color of listbox is changed

### And Tasks With Points:

  - **Add a listbox and attach some events when any element is accessed (clicked)**
    
      - `DOUBLE CLICK` or `ENTER` - a MessageBox with information about accessed element is displayed
      - `DELETE`                  - the accessed alement is deleted
      
      In order to manage the listbox using keyboard input I have created a procedure `ListProc` which allowed me to           `SetFocus` on listbox, otherwise the commands were executed even if no element was accessed.
  - **Add 2 scroll bars that will manage main window  position**
  
     Commands for this task are written in ```WM_VSCROLL``` and ```WM_HSCROLL```, where a static variable `posY` and         respectively `posX` is incremented or decremented.
  - **Customize your application by adding an icon and using different cursor in application**
 
     ``LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));``     - custom icon
     ``LoadCursor (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CURSOR));`` - custom cursor
      
     In project were added for custom icon a file with extension `.ico` and for cursor - `.cur`.
  - **Use a scroll bar to scroll through application working space. Scroll should appear only when necessary**
     
## Conclusion
   
