// ==========================================================================
//
// File      : AnimatedImage.hpp
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

#ifndef ANIMATEDIMAGE_HPP
#define ANIMATEDIMAGE_HPP

#include "Graphics.hpp"
#include "Timer.hpp"


/// AnimateImage implementation for raw gif files.
//
/// A class used to draw raw gif animations on the screen.
class AnimatedImage : public Graphics
{
public:
	
	/// AnimatedImage constructor'
	//
	/// Screen is the screen to draw on e.g. matrix.
	/// image is the raw gif file converted by a commandline script. After you included the conveted
	/// gif animation you can pass it to this function. Location is the location of animated image on the screen.
	AnimatedImage(Screen &w, const uint8_t* image, vector location = vector(0,0)):
		Graphics(w, vector(image[3],image[4]), location), image (image)
	{}
	
	/// draw the animated image on the screen.
	//
	/// You do not need to swap buffers. Default loop is false and update interval is 10 milliseconds.
	void draw();
	/// draw the animated image on the screen.
	//
	/// You do not need to swap buffers. updateInterval is the delay between each frame.
	/// if loop is true the animation will be restarted when the last frame showed on the screen.
	void draw(int updateInterval, bool loop = false);
	/// draw a specefiek frame on the screen.
	//
	/// You need to swap buffer if double buffering is enabled.
	void drawFrame(int);
	///Return number of frames of the animatedImage.
	int getTotalFrames();

private:
	const uint8_t* image;
};

#endif // ANIMATEDIMAGE_HPP
