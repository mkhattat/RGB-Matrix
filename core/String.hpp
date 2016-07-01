// ==========================================================================
//
// File      : String.hpp
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

#ifndef STRING_HPP
#define STRING_HPP

#include "Graphics.hpp"


/// String class implements text manipulation to be used by a Screen object e.g. matrix object.
//
/// String class can print a text on the screen and/or scroll it from right to left.
class String : public Graphics
{
public:
	/// String constructor
	//
	/// Screen is the display you want to draw text on to it e.g. matrix.
	/// font is a font file. you need to convert the normal .ttf font with a commandline script and 
	/// then include the .h file into your project. font is the name of array in that file (usually the same as the
	/// file name e.g. tahoma10).
	/// text is the string you want to write on the screen. You have to typecast your string first to char*.
	/// for example if you want to print "Hallo World" you have to pass it like this: (char*)"Hallo World".
	/// r g b are colors of the text. they are between 0 and 255.
	/// location is the location of line you want to write text on it. The height or Y should be greater than font size
	/// to be able to see the text on screen. The characters will be printed from bottom to top.
	String(Screen &w, const uint8_t *font, char *text, uint8_t r,uint8_t g,uint8_t b, vector location = vector(31,63));
	/// String constructor
	//
	/// Screen is the display you want to draw text on to it e.g. matrix.
	/// font is a font file. you need to convert the normal .ttf font with a commandline script and 
	/// then include the .h file into your project. font is the name of array in that file (usually the same as the
	/// file name e.g. tahoma10).
	/// text is the string you want to write on the screen. You have to typecast your string first to char*.
	/// for example if you want to print "Hallo World" you have to pass it like this: (char*)"Hallo World".
	/// color is the colors of the text. It can be max 24 bits (2^24-1).
	/// location is the location of line you want to write text on it. The height or Y should be greater than font size
	/// to be able to see the text on screen. The characters will be printed from bottom to top.
	String(Screen &w, const uint8_t *font, char *text, uint32_t color, vector location = vector(31,63));
		
	/// Print the text on the screen.
	//
	/// The characters will be printed on the screen at the specified position.
	/// Note that if double buffering is enabled you have to swap the buffers for the text to be showed on the screen.
	void draw() override;
	/// Scroll text from left to right at startX.
	//
	/// This function scrolls the text from right to left at the speed of "updateInterval".
	/// "updateInterval" is in milliseconds. if loop is true the scrolling of the text
	/// would be continuously. startX is width's postion where the text start to scroll from.
	/// You do not need to swap the buffer. It's done internally.
	void scroll(int updateInterval = 10, bool loop = false, int startX = 64);
	/// Set the text of string.
	//
	/// This function changes the text of the string. It has to be typecasted to char*.
	/// For example if you want to pass "Hallo World" to the function, you have to write it as:
	/// (char*)"Hallo World".
	void setText(char *t){
		text = t;
	}
	/// Set the color of the string.
	//
	/// This function changes the color of the text. the color can be a (hexa)decimal between 0 and 2^24-1.
	void setColor(uint32_t c);
	/// Set the color of the string.
	//
	/// This function changes the color of the text. r g and b can be between 0 and 255.
	void setColor(uint8_t rc, uint8_t gc, uint8_t bc);
	
	/// Set the font of the string.
	//
	/// This function changes the font of the string.
	/// font is a font file. you need to convert the normal .ttf font with a commandline script and 
	/// then include the .h file into your project. font is the name of array in that file (usually the same as the
	/// file name e.g. tahoma10).	
	void setFont(const uint8_t *f){
		font = f;
	}
	

private:
	/// clear the printed text.
	//
	/// This function is used by scroll text to clear the text and preven clearing all
	/// pixels on the screen.
	void clear(int);
	
	/// stores the font variable
	const uint8_t *font;
	/// store the text variable
	char *text;
	/// stores the max height of a char in the string.
	uint8_t maxHeight=0;
	
	uint8_t color_red;
	uint8_t color_green;
	uint8_t color_blue;

};

#endif // STRING_HPP
