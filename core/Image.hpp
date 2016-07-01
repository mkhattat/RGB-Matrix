// ==========================================================================
//
// File      : Image.hpp
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

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Graphics.hpp"

/// Implementation for raw image files.
//
/// This class is used to draw photos on the screen.
class Image : public Graphics
{
public:
	
	/// Image constructors
	// 
	/// Screen to draw image on it, e.g. matrix.
	/// image is a raw photo converted by a command line script. You have to include
	/// a raw file and then pass it to this function. Location is the location to draw 
	/// image on the screen.
	Image(Screen &w, const uint8_t *im, vector location = vector(0,0)):
		Graphics(w, vector(im[0], im[1]), location), image (im)
	{}
	
	/// print the image on the screen.
	//
	/// If you enabled a double buffering you have to swap buffers to draw the image
	/// on the screen.
	void draw() override;

private:
	const uint8_t *image;
};

#endif // IMAGE_HPP
