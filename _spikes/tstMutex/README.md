# boilerplate-cpp-vscode-win
The code depends on mingw, and requires the same to be installed on the machine. To use the code, open Makefile and look for the MINGW = C:\Qt\Qt5.9.7\5.9.7\mingw53_32. That's the path of mingw on my machine (using Qt's mingw toolchain, you can install mingw direct). 
Also change the path of "command" parameter in tasks.json, and the path of "miDebuggerPath" in launch.json.
