#include "Runner.hpp"

Runner::Runner(AnimatedImage gif, hwlib::target::pin_in & jump_button):
	Coordinate(gif.getScreen(), gif.getSize(), gif.getLocation()), gif (gif), jump_button (jump_button)
{
	current_frame = 0;
	
	counter_frame = 0;
	counter_jump = 0;
	jump_flag = false;
}


void Runner::update() {
	/// the last frame of gif animation is for jump 
	
	if (counter_jump > 17){
		jump_flag = true;
	}


	if (jump_flag == false && jump_button.get() == false) { // is jump button pressed?
		current_frame = gif.getTotalFrames()-1; // yes? then load jump frame (the last frame of animation)
		gif.setLocation(vector(10, 3));
	}
	else if (counter_frame >= 3){ /// No? the load the next run frame
		(current_frame >= 3) ? current_frame = 0 : current_frame++;
		gif.setLocation(vector(10, 9));
		counter_frame = 0;
	}
	
	counter_frame++;
	counter_jump++;
	
	if (jump_button.get() == true){
		jump_flag = false;
		counter_jump = 0;
	}
	
	gif.drawFrame(current_frame);
}

vector Runner::getLocation() {
	return gif.getLocation();
}