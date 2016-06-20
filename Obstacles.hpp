#ifndef OBSTACLES_HPP
#define OBSTACLES_HPP

#include "AnimationObject.hpp"
#include "Coordinate.hpp"
#include "Screen.hpp"
#include "vector.hpp"
#include "straightLine.hpp"
#include "hwlib.hpp"

class Obstacles : public Coordinate, public AnimationObject 
{
public:
	Obstacles(Screen &w, hwlib::target::pin_in &upsideDown_button, vector size = vector(2,2));
	bool update(Coordinate &interact_obj) override;
//	void draw() override;

private:
	hwlib::target::pin_in &upsideDown_button;
	bool upsideDown_flag, button_pressed;
//	uint32_t points;
	uint32_t color_up;
	uint32_t color_down;

	uint8_t patternSize;
	uint16_t startWidth;

	void drawBlock(vector start, vector end, int color);
	bool drawPattern(Coordinate &interact_obj);
	bool drawPattern_upsideDown(Coordinate &interact_obj);
	
};

#endif // OBSTACLES_HPP
