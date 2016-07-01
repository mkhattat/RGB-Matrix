// ==========================================================================
//
// File      : Graphics.hpp
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

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "vector.hpp"
#include "Screen.hpp"

/// The interface for other graphics objects.
//
/// Graphics class is an abstract class used as an interface for
/// other graphic objects like Image, String and Animated Image.
/// This is an abstract class. It can be used only as a base for other objects.
class Graphics
{
public:
	/// Graphics constructor
	//
	/// Screen to draw graphics on it e.g. matrix.
	/// Size is the size of object and location is the pixels position on the screen.
	Graphics(Screen &w, vector size, vector location):
		 w (w), size (size), location (location)
	{}
	
	/// draw graphics object on the screen.
	virtual void draw() = 0;
	
	/// return the size of a graphics object.
	vector getSize() const{
		return size;
	}
	/// return the location of a graphics object.
	vector getLocation() const{
		return location;
	}
	
	/// return the screen used by graphics object
	Screen& getScreen() const{
		return w;
	}
	
	/// change the location of a graphics object.
	void setLocation(vector l){
		location = l;
	}
	
	
	/// change the size of a graphics object
	void setSize(vector s){
		size = s;
	}
		
protected:
	Screen &w;
	vector size;
	vector location;
	
};

#endif // GRAPHICS_HPP
