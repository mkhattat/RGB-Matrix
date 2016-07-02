# RGB-Matrix
A Bare metal C++ Library for RGB Matrix 64x32 and a simple game to show the work of the library.
This Library uses Bmptk (Bare Metal Programming Toolkit). for more information refre to "bmptk/README.txt".

You can find the source code of the library in the "core" folder.
For Documentation of RGB-Matrix library refer to "html/index.html" or https://mkhattat.github.io/RGB-Matrix/index.html

You can find the source code of the Game in the LedRunner folder. In order to compile the game cd to the LedRunner directory and type

'''sh
make
'''

and in order to upload the compiled binary use the following commands:

'''sh
stty -F /dev/ttyACM0 1200
bossac --port ttyACM0 -U false -e -w  -b main.bin -R
'''
