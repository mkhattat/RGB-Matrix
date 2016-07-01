// ==========================================================================
//
// File      : Screen.hpp
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

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <stdint.h>


/// The interface for led matrix and eventual other led screens
//
/// This class abstracts the interface to a led screens.
/// You cannot define this class as an object. This class should be 
/// derieved by any class that implements a led screen.

class Screen
{
public:
	
	/// Specify the width and height of the screen.
	//
	/// Width and height are in pixel.
	Screen(int w, int h):
		width(w), height(h)
	{}
	/// Draw a given pixel with a color R G B.
	//
	/// the first int argument is the width position and the second
	/// is the height position of a pixel. rgb color is between 0 and 255.
	virtual void drawPixel(int, int, uint8_t, uint8_t, uint8_t) = 0;
	/// Draw a pixel with a hexadecimale color.
	//
	/// the first int argument is the width position and the second
	/// is the height position of a pixel. color is rgb is hexa or decimale.
	virtual void drawPixel(int, int, uint32_t) = 0;
	/// Fill the entire screen with r g b colors.
	virtual void fillScreen(uint8_t, uint8_t, uint8_t){}
	/// Fill the entire screen with a hexa or decimal color.
	virtual void fillScreen(uint32_t){}
	/// Clear the entire screen.
	virtual void clear() = 0;
	/// Start the auto update of the screen.
	virtual void start(){}
	/// Stop the auto update of the screen.
	virtual void stop(){}
	/// Swap the back buffer with front buffer.
	//
	/// You can also copy the values of new buffer to the old buffer
	/// by passing a true bool to the function.
	virtual void swap_buffer(bool copy){}
	virtual void update(){}
	
	//// Return the width of the screen in pixel.
	int getWidth(){
		return width;
	}
	
	/// Return the height of the screen in pixel.
	int getHeight(){
		return height;
	}
	
protected:
	/// width and height of the screen.
	int width, height;
	
};

#endif // SCREEN_HPP
