#ifndef RUNNER_HPP
#define RUNNER_HPP

#include "AnimationObject.hpp"
#include "Coordinate.hpp"
#include "AnimatedImage.hpp"
#include "Timer.hpp"
#include "hwlib.hpp"

class Runner : public Coordinate, public AnimationObject
{
public:
	Runner(AnimatedImage gif, hwlib::target::pin_in & jump_button);
	
	void update() override;
	vector getLocation() override;
//	void draw() override;
	
private:
	AnimatedImage gif;
	int counter_frame, counter_jump, current_frame;
	hwlib::target::pin_in & jump_button;
	bool jump_flag;

};

#endif // RUNNER_HPP
