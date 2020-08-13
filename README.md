# ROS video game

# This future video game use V2E ( Virtual Ecosystem Engine )

# V2E is in the source folder named "V2E"

WINDOWS AND LINUX ONLY. Unfortunaly, no unigine sdk is compatible with macOS.

/!\ 2.11 unigine community version only ! See unigine-2.12 for early access to the upgrade !

/!\ data directory is missing to avoid heavy GIT project !

/!\ This is a very early project with no good graphics optimization and only a debug ( development ) version !   

Hardware in use to build and run the simulation :

* GPU : MSI Gaming X TRIO 2080 TI
* CPU : AMD Ryzen 9 3950X 3.5 Ghz, 8 cores, 16 threads
* RAM : Corsair LPX Vengeance 3200 MHz 32 Gio
* OS : Linux version 5.7.7-200.fc32.x86_64 (mockbuild@bkernel01.iad2.fedoraproject.org) (gcc version 10.1.1 20200507 (Red Hat 10.1.1-1) (GCC), GNU ld version 2.34-3.fc32) #1 SMP Wed Jul 1 19:53:01 UTC 2020  

Please report your configuration in case of issue.


# DEV BUILD INSTRUCTIONS

To build this project with unigine ( development version or release ) :

1. Create an account in Unigine ( follow instructions ) here : https://unigine.com/get-unigine/sign-up-free

2. Get UNIGINE Community SDK

3. Clone or download this repository

4. Download data directory here : https://mega.nz/file/G9dGlY4Y#RvMNsqiDXyhqvlIFPQ3lU6WVE6LoDLLYJtxxP0ti8uY

5. Put the directory in the project root directory

5. Run unigine browser and sign in

6. Choose "ADD EXISTING" choose the path of the cloned repository

7. Modify the project in editor, run build version,... from here

## IDE USER - Kdevelop example - LINUX ONLY 

I make a custom CmakeList.txt in the repository, is usualy the best option to build the project with all the custom components.

In Kdevelop open project by choosing `"source" directory in the repository` as project directory.

Choose CMakeLists.txt as project manager then choose `"build" directory in the root of the project` and set extra options with `-S ../source/`

In the `run menu` choose `configure launches`

Add a script application with bash as script interpreter and run always the same file `launch_debug.sh` ( for debug mode )


**Troubleshoot :**

*The IDE doesn't build the debug version but the release version* : force Cmake to use debug version in `Project --> Open Configuration --> Show Advanced --> Build Type : Debug`

## IDE USER - WINDOWS USERS

You can use visual studio code, usualy integration is good with Windows - see the docs here : 

https://developer.unigine.com/en/docs/2.11/code/environment/windows?rlang=cpp

# TO DO LIST

1. Texturing.

2. User interface.

3. System Integration.

4. Special animation than land/take off.

5. Add other animals.

6. Plants and Cells better integration.

7. User Interface.

8. Optimization ( graphical and code )