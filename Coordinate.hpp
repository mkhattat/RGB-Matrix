#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include "vector.hpp"
#include "Screen.hpp"

class Coordinate
{
public:
	Coordinate(Screen &w, vector size, vector location):
		w (w), size (size), location (location)
	{}
	
	vector getSize(){
		return size;
	}
	
	virtual vector getLocation(){
		return location;
	}
	
protected:
	Screen &w;
	vector size;
	vector location;
};

#endif // COORDINATE_HPP
