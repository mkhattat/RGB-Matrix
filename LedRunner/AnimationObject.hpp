#ifndef ANIMATIONOBJECT_HPP
#define ANIMATIONOBJECT_HPP

#include "Coordinate.hpp"

class AnimationObject
{
public:
	virtual void update(){};
	virtual bool update(Coordinate&){return true;};

};

#endif // ANIMATIONOBJECT_HPP
