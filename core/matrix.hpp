// ==========================================================================
//
// File      : matrix.hpp
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

#ifndef MATRIX_H
#define MATRIX_H

#include "hwlib.hpp"
#include "Screen.hpp"
#include "gamma.h"
#include "Image.hpp"
#include "String.hpp"
#include "Timer.hpp"
#include "AnimatedImage.hpp"
#include "Image.hpp"
#include "vector.hpp"


#define CBIT 8
#define ROW 16
#define COL 512

namespace target = hwlib::target;

/// Led matrix implementation for the abstract class Screen.
//
/// This class contains an implementation for the led matrix 32x64 but also
/// for other led matrixes like 32x32 and 16x32.
class matrix : public Screen {
 
public:

	/// Matrix constructor with default wiring
	//
	/// matrix constructor with given width, height and the posibility to choose
	/// a double buffer. if you chose to use a double buffer you always write into
	/// the back buffer. So you can't see the result unless you swap the buffers with swap_buffer methode.
	matrix(int width, int height, bool double_buffer);
	/// Matrix constructor with custom wiring
	//
	/// matrix constructor with given width, height and the posibility to choose
	/// a double buffer. if you chose to use a double buffer you always write into
	/// the back buffer. So you can't see the result unless you swap the buffers with swap_buffer methode.
	matrix(int width, int height, bool double_buffer, target::pin_out  _lat,
			target::pin_out  _oe, target::pin_out  _clk,
			target::pin_out  _selA, target::pin_out  _selB,
			target::pin_out  _selC, target::pin_out  _selD,
			target::pin_out  _b1, target::pin_out  _g1,
			target::pin_out  _r1, target::pin_out  _b2,
			target::pin_out   _g2, target::pin_out  _r2);
	/// Draw a given pixel with a color R G B.
	//
	/// the first int argument is the width position and the second int argument
	/// is the height position of a pixel. rgb colors are between 0 and 255.
	//
	/// This function writes always into the back buffer if double buffer is enabled, otherwise writes into
	/// the front buffer.
	void drawPixel(int x, int y, uint8_t rc, uint8_t gc, uint8_t bc) override;
	/// Draw a pixel with a hexadecimale color.
	//
	/// the first int argument is the width position and the second
	/// is the height position of a pixel. color is rgb is hexa or decimale.
	//
	/// This function writes always into the back buffer if double buffer is enabled, otherwise writes into
	/// the front buffer.
	void drawPixel(int x, int y, uint32_t color);
	/// Fill the entire screen with r g b colors.
	//
	/// This function fills the back buffer if double buffer is enabled otherwise clears the front buffer.
	void fillScreen(uint8_t r, uint8_t g, uint8_t b) override;
	/// Fill the entire screen with a hexa or decimal color.
	//
	/// This function fills the back buffer if double buffer is enabled otherwise clears the front buffer.
	void fillScreen(uint32_t color);
	/// Clear the entire screen.
	//
	/// This function clears the back buffer if double buffer is enabled otherwise clears the front buffer.
 	void clear() override;
	/// Start the auto update of the screen.
	//
	/// The led matrix needs to be updated constantly. This function does the job of updating the screen with
	/// a frequenty of 200 HZ.
	void start() override;
	/// Stop the auto update of the screen.
	//
	/// If you stop the auto update of the screen the current picture on the screen will be removed and maybe only
	/// one row or twoo rows of the led matrix remains light.
	void stop() override;
	/// Swap the front buffer with the back buffer.
	//
	/// If double buffer is enabled, you can swap the front buffer and the back buffer with this function.
	/// If you need to copy the values of the updated buffer into the new back buffer 
	/// you need to pass true to the copy varianle.
	/// But if you only need to swap the front buffer with the back buffer and you don't care about the old buffer (maybe
	/// because you clear the screen afterwards) the pass false to the copy variable.
	/// To avoid "tearing" swapping of buffers takes place at the end of a complete screen refresh cycle.
	//
	/// NOTE: This function doesn't have any effect if you didn't enable the double buffer in the constructor.
	void swap_buffer(bool copy) override;
	/// Update the screen.
	//
	/// You do not probably need to use this function. This function is used by the
	/// interrupt handler to update the screen at specefiec time intervals.
	void update() override;
	void update2();
	
	bool is_using_default_pins(){
		return useDefault;
	}
    
private:
	
	void init();
	
	bool useDefault;
	
	/// Front buffer used by drawPixel and swap_buffer functions
	uint8_t front_buffer[ROW*COL] = {};
	/// Back buffer used by drawPixel and swap_buffer when double buffering is enabled
	uint8_t back_buffer[ROW*COL] = {};
	/// always points to the current buffer.
	uint8_t * current_buffer;
	/// always points to the back buffer.
	uint8_t * next_buffer;
		
	/// current_row and current_bit is used by timer interrupt handler in BCM algorithm.
	volatile int current_row, current_bit;
	/// if double buffer is enabled, double buffer is true.
	/// swap buffer takse place in the interrupt handler function.
	/// swap_flag lets interrupt handler know that buffers need to be swapped.
	/// swap_copy lets interrupt handler know that the values of new buffer should
	/// be coppied to the old buffer.
	volatile bool double_buffer, swap_flag, swap_copy;
	
	/// time delay for next interrrupt. used by BCM algorithm.
	volatile int t_delay; 
	
	/// latch pin of led matrix
	hwlib::target::pin_out  _lat;
	/// output enable pin of led matrix
	hwlib::target::pin_out  _oe;
	/// clock pin of led matrix
	hwlib::target::pin_out  _clk;
	
	/// Select A pin of led matrix
	hwlib::target::pin_out  _selA;
	/// Select B pin of led matrix
	hwlib::target::pin_out  _selB;
	/// Select C pin of led matrix
	hwlib::target::pin_out  _selC;
	/// Select D pin of led matrix
	hwlib::target::pin_out  _selD;
	
	/// data pin Blue for top half screen
	hwlib::target::pin_out  _b1;
	/// data pin green for top half screen
	hwlib::target::pin_out  _g1;
	/// data pin red for top half screen
	hwlib::target::pin_out  _r1;
	/// data pin blue for bottom half screen
	hwlib::target::pin_out  _b2;
	/// data pin green for bottom half screen
	hwlib::target::pin_out  _g2;
	/// data pin red for bottom half screen
	hwlib::target::pin_out  _r2;

//  
};


#endif
