# IDE Laboratory Work #2

### Title: GUI Development 

   - **Visual Studio**

> It is 4102. Aliens invaded us. Luckily the world has some great engineers and you are one of them! Your'e working on an unbeatable weapon: Simulatron. Simulatron is an exact copy of alien ship but it has a secret: when the alien gets into ship the alien is traped and brought into human prison. Your task is very simple: you have to clone Simulatron's control panel. World depends on you...

#### In this laboratory work I executed the following tasks:

   - Define 3 virtual tasks that you Simulatron is supposed to control
   - Create a GUI application with 5 standard controls (any child window control mentioned in book Windows Programming ed.5 is considered standard)

#### In this laboratory work I executed the following tasks with points:

   - Add 3 non-standard controls (2pt)
   - Make controls to interact. At least 3 interactions (1pt) 
   - Create a custom control (not existent in IDE) (2pt)
   - Create a _Reset_ button. On clicking this button all controls should go to their default state (1pt)
   - Set a breakpoint in your application and check variables values at that moment of time (1pt)
   - _Mention your own tasks that you did and claim points for them_
     - Sound effects and GIF usage (1pt)
     - Switch forms (1pt)

     **The result of my application:**

       - First form _LogIn_ request with progress bar : 

       ![screen](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/logIn.png)

       - Second form _MainScreen_ of _Simulatron_ :
      > the same screen is generated when button _Reset_ is clicked
     
       ![screen1](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/main_screen.png)

       - The result shown when button _Find / Get_ is clicked
          - in center - is loaded a gif, with found alien;
          - in the right corner - a gif that flashes, the colors depend on the danger level:
            - red - high
            - yellow - moderate
            - green - low
          - in the left corner  - the stopwatch
          - in the left part of the screen - the information about found alien
          - in the right part of the screen - the information about nr of detected and captured aliens

       ![screen2](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/alien_red.png)

       - The result shown when button _Capture_ is clicked:

       ![screen3](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/captured.png)

       - The result shown when the user do not click the _Capture_ button:

       ![screen4](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/alien_escaped.png)

#### Conclusion:
 
 This laboratory was very interesting, I had used all power of _WindowsFormsApplication_ . You can basically do everything using _C#_ and _WFA_ , like:
  - Import images / GIFs
  - Create DataBase and LogIn app
  - Import Sound Effects
  - Use Progress Bar