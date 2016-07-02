// ==========================================================================
//
// File      : doxygen.hpp
// Part of   : led matrix library
// Copyright : mostafa@khattat.nl 2016
//
// led matrix implementation for an Arduino Due (ATSAM3X8E chip)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

// This file contains doxygen stuff that doesn't belong in any specific
// header file. This file is not included by the library.

/// \mainpage Quick Start Guid
/// \image html main.JPG
/// \author Mostafa Khattat (mostafa@khattat.nl)
/// \version 1.0 (last modified 2016-06-20)
/// \copyright boost license (some files public domain)
///
/// Smart Matrix is a library to control 64x32 led pannels. A dot-matrix display is a display
/// device used to display information, photos or short video clip animations. The display consists of 
/// a dot matrix of RGB lights arranged in a rectangular configuration such that by switching on or off selected
/// lights, text or graphics can be displayed. Smart Matrix is a library to control such matrix.
/// The library is written in c++ Object Oriented. The main class, matrix.hpp, is used to declare and initialize the
/// led matrix and also there are other classes to help you control the led matrix.
/// Here you will find a quick start guide with some example to show you how the library works.
///
/// \b Wiring:
///
/// This section describes default wiring and pins numbers.
/// The RGB panels are normally designed for chaining (linking end-to-end into larger displays)…the output of one panel
/// connects to the input of the next, down the line. Flip the matrix over so you’re looking at the back, holding it with
/// the two sockets situated at the left and right edges. One of them is INPUT. That's the socket we are intersting.
/// \image html led_matrix_orient.png
/// You need to wire you gpio pins as bellow:
/// \image html wiring.jpg
///
/// <table>
/// <caption id="multi_row">Wiring Table</caption>
/// <tr><th>Pin Names                      <th>Arduino Digital Pin Names      
/// <tr><td>R1<td>digital pin 35
/// <tr><td>B1<td>digital pin 33
/// <tr><td>R2<td>digital pin 38
/// <tr><td>B2<td>digital pin 36
/// <tr><td>R1<td>digital pin 35
/// <tr><td>A<td>digital pin 25
/// <tr><td>C<td>digital pin 27
/// <tr><td>CLK<td>digital pin 39
/// <tr><td>OE<td>digital pin 42
/// <tr><td>G1<td>digital pin 34
/// <tr><td>G2<td>digital pin 37
/// <tr><td>B<td>digital pin 26
/// <tr><td>D<td>digital pin 28
/// <tr><td>Latch<td>digital pin 43
/// </table>
///
/// \b Matrix:
/// 
/// To start using the led pannel you have to initialize it. You can do it in two ways:
/// - You can use the default wiring (Highly recommended)
///
/// - You can use your own wiring and pinnen (Not recommended! because of performance issues)
///
/// Here is such an example of using matrix library with default wiring:
/// \code{.cpp}
/// #include "matrix.hpp"
/// 
/// matrix led(64, 32, true);
/// led.start();
/// \endcode
///
/// But as already said you can use your own wiring setup. In that case you have to pass the pin number of every wire
/// to the constructor:
/// \code{.cpp}
/// #include "matrix.hpp"
///
///     matrix led(64, 32, true, target::pins::d43, target::pins::d42, target::pins::d39,
///				target::pins::d25, target::pins::d26, target::pins::d27, target::pins::d28,
///				target::pins::d33, target::pins::d34, target::pins::d35, target::pins::d36,
///				target::pins::d37, target::pins::d38);
///     led.start();
/// \endcode
/// The problem with above code is that you can not get the maximum performance out of you microcontroller
/// and thus you will notice flickers and lag in animation. It's recommended to use de default wiring. To setup
/// your led matrix with default wiring use the documentation above. for more information about both constructor refer to
/// matrix.hpp class.
///
/// In both cases (default wiring or custom wiring) of above examples 64 is the width of led matrix and 32 is the height.
/// Library supports a double buffering. To enable it you should pass true as 3e arrgument.
/// The hardware of led matrix can display only two rows at once. In order to light all pixels we have
/// to turn on and off every row quickly so that in our eyes it seems that the alle pixels are on.
/// To that the library uses a timer interrupt functionality of Arduino Due. led.start() enables auto update,
/// so you don't have to worry about turning on or off panel rows.
/// 
/// <b> Note: </b> The library uses timer interrupt 1 channel 1 to update the led pannel. So if you plan to use 
/// timer interrupts in your program you should not use this interrupt channel.
/// 
/// If you enable double buffering, drawing any pixel will occur in the back buffer. The result is not
/// visible until you swap the buffers:
/// \code{.cpp}
/// led.drawPixel(0,0, 0xFFFFFF);
/// led.swap_buffer(false);
/// \endcode
/// In the above example we light up the pixel (0,0) and specify it's color as "White". 
/// Colors can be in (hexa)decimal values between 0 and 2^24-1 or seprate RGB colors:
/// \code {.cpp}
/// led.drawPixel(0,0, 255, 255, 255);
/// \endcode
/// Because we already enabled double buffering we have to swap buffers to turn on pixel (0,0). 
/// This function requires an bool argument.
/// If you need to copy the values of the updated buffer into the new back buffer 
/// you need to pass true to the copy varianle.
/// But if you only need to swap the front buffer with the back buffer and you don't care about the old buffer (maybe
/// because you clear the screen afterwards) the pass false to the copy variable.
/// To avoid "tearing" swapping of buffers takes place at the end of a complete screen refresh cycle.
///
/// <b>Note: </b> This function doesn't have any effect if you didn't enable the double buffer in the constructor.
/// 
/// In order to fill the screen with a specific color you can use fillscreen function.
/// \code{.cpp}
/// led.fillScreen(0x87ADFF);
/// \endcode
/// Here you can also use RGB colors:
/// \code{.cpp}
/// led.fillScreen(135, 173, 255);
/// \endcode
/// There is also a clear function to clear the screen:
/// \code{.cpp}
/// led.clear();
/// \endcode
/// 
/// 
/// <b> Show Images: </b>
/// 
/// 
/// With your led pannel you can also show pictures. The max size of pictures should be at the max size of pannel.
/// So if you have a 64 width x 32 height pannel, the size of you pictures should be maximum 64x32. The library does
/// not scale the images for you.
/// The library uses a special raw format for the photos. There is a python command line script helps you convert
/// your images at any format to the required raw format. This python script is readbmp.py.
/// In order to use this script you need to install pillow library.
/// \code{.sh}
/// python -m pip install Pillow
/// \endcode
/// The readbmp script needs two arguments, path to the photo and the name of the new raw file:
/// \code{.sh}
/// python readbmp.py photo.jpg myphoto
/// \endcode
/// The result is a .h file you can include in your projects and use it to show the photo on the screen:
/// \code{.cpp}
/// #include "myphoto.h"
/// 
/// Image im(led, myphoto, vector(35,0));
/// im.draw();
/// led.swap_buffer(false);
/// \endcode
/// in the above example vector(35,0) is the location of the library. in this library you should pass location and
/// size of something as a vector(x,y). See also vector.hpp
/// 
/// <b> Show Animated Images: </b>
/// 
/// Not only Images can be shown but Animated Images can also be shown on the led matrix. To use this feature you
/// have to convert a gif animation file to a raw animated image. To do this you can use a python
/// script make_animation.py. This script depends on a pillow library:
/// \code{.sh}
/// /// python -m pip install Pillow
/// \endcode
/// The make_animation.py script needs two arguments, path to the gif file and the name of the new raw animated file:
/// \code{.sh}
/// python make_animation.py animation.gif myanimation
/// \endcode
/// The result is a .h file you can include in your projects and use it to show the animated image on the screen:
/// \code{.cpp}
/// #include "myanimation.h"
/// 
/// AnimatedImage aIm(led, animation, vector(15, 0));
/// aIm.draw();
/// \endcode
/// The above code prints animation at location (15, 0). De default is one time from start to end with a update interval
/// 10 milliseconds between each frame. In order to change de update interval and loop option you can declare the function
/// as:
/// \code{.cpp}
/// aIm.draw(5, true);
/// \endcode
/// The above code prints animation with 5 milliseconds update interval between each frame and loop option set to true.
/// 
/// <b> Note: </b> The draw() function of AnimatedImage class doesn't need the buffer_swap operation.
/// 
/// You can also print a specific frame of an animated image file:
/// \code{.cpp}
/// aIm.drawFrame(0);
/// led.swap_buffer();
/// \endcode
/// The value of frame number must be smaller than total frames, otherwise nothing will be printed on the screen.
/// You can get total number of frames of an animated image by:
/// \code{.cpp}
/// int frames;
/// frames = aIm.getTotalFrames();
/// \endcode
/// The result is an intger value. 
///
/// <b> Show Text: </b>
/// 
/// Texts can be shown on the screen by using String class. This class needs a font. You can convert any .ttf font to font
/// supported by the library. In order to convert a font you can use a python script make_font.py. This script depends
/// on a pillow python library. You have to first install it:
/// \code{.sh}
/// python -m pip install Pillow
/// \endcode
/// The make_font.py script accepts 3 arguments: font path, size of the font you want to use and the name of new font:
/// \code{.sh}
/// python make_font.py tahoma.ttf 10 tahoma10
/// \endcode
/// The result is a .h file. A tahoma.ttf font converted with size of 10 to a supported font with name tahoma10.
/// You can use this font by string class to show text or scroll text on the screen:
/// \code{.cpp}
/// #include "tahoma10.h"
/// 
/// String str(led, tahoma10, (char*)"Hallo World!", 0xFA0000, vector(0, 10));
/// str.draw();
/// led.swap_buffer(false);
/// \endcode
/// "Hallo World!" is the string to be written on the screen. You have to typecast your string first to char*.
/// for example if you want to print "Hallo World" you have to pass it like this: (char*)"Hallo World".
/// You can also use RGB colors:
/// \code{.cpp}
/// String str(led, tahoma10, (char*)"Hallo World!", 255, 255, 255, vector(0, 10));
/// \endcode
/// 
/// In order to scroll text from right to left on the screen you can use scroll function:
/// \code{.cpp}
/// str.scroll();
/// \endcode
/// This function scrolls the text from right to left at the speed of 10 milliseconds.
/// By default the loop is set to false and the start point of scroll is at width = 64;
/// In order to change the default behavior you can declare the above function like this:
/// \code{.cpp}
/// str.scroll(15, true, 32);
/// \endcode
/// The above code scrolls the text at the speed of 15 milliseconds per pixel and the loop is set to true.
/// Also notice that the start point of scrolling is width = 32. It means the text will be scrolled from pixel(32, y) to
/// pixel(0,y).
///
/// \b Note: By using scroll function you do not need to use swap_buffer();

