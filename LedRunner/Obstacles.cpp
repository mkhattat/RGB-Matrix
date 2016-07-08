#include "Obstacles.hpp"
#include "pattern.h"


Obstacles::Obstacles(Screen &w, hwlib::target::pin_in &upsideDown_button, vector size):
	Coordinate(w, size, vector(w.getWidth(), 8)), upsideDown_button (upsideDown_button)
{
//	uint32_t points = 0;	
	color_up = 0x9A33FF;
	color_down = 0x8F1455;
	patternSize = 166;
	startWidth = w.getWidth();
	upsideDown_flag = false;
	button_pressed = false;
}

bool Obstacles::update(Coordinate &interact_obj){
		
	if (upsideDown_button.get() == false && button_pressed == false){
		button_pressed = true;
		upsideDown_flag = !upsideDown_flag;
	}
	else if (upsideDown_button.get() == true && button_pressed == true){
		button_pressed = false;
	}
	
	if (upsideDown_flag){
		return drawPattern_upsideDown(interact_obj);
	}
	else {
		return drawPattern(interact_obj);
	}
	
}


bool Obstacles::drawPattern(Coordinate &interact_obj){
		
	bool result = true;
	uint16_t tmp_x = startWidth;
	uint32_t color; // change the color later if necessary
	// walk through every pattern and draw them on the screen
	
	for (int p=0; p<patternSize; p++){
		
		// every bit contains twoo pattern (one for above the line and one for under the line)
		for(int b=0; b<6; b++){ // there are min 1 and max 3 blocks above each other)
			if (b==3)
				tmp_x += size.x+1; //create some space after first pattern
			
			(b >=3) ? color = color_down : color = color_up;
			
			uint8_t start_y = (location.y) + (b*(size.y+2)); // size of each block plus a gap between them
						
			if(pattern[p] & (0x1 << b)){ // draw block only if it's bit is true (Top to button)
			
					// check if the the obstacle overlaps with other object
					if (tmp_x > interact_obj.getLocation().x && 
						tmp_x < interact_obj.getLocation().x + interact_obj.getSize().x){
							if (start_y < (interact_obj.getLocation().y + interact_obj.getSize().y)-1)
								result = false;
					}

					drawBlock(vector(tmp_x, start_y), vector(tmp_x+size.x, start_y+size.y), color); 
			}
			
		}
		tmp_x += size.x; //create some space after second pattern
		
	}
	
	if (tmp_x == 0) startWidth = w.getWidth()+1;
	
	startWidth--;
	
	return result;
}

bool Obstacles::drawPattern_upsideDown(Coordinate &interact_obj){
	bool result = true;
	uint16_t tmp_x = startWidth;
	uint32_t color; // change the color later if necessary
	// walk through every pattern and draw them on the screen
	for (int p=0; p<patternSize; p++){
		
		// every bit contains twoo pattern (one for above the line and one for under the line)
		for(int b=5; b>=0; b--){ // there are min 1 and max 3 blocks above each other)
			if (b==2)
				tmp_x += size.x+1; //create some space after first pattern
			
			(b >=3) ? color = color_down : color = color_up;
			
			uint8_t start_y = (location.y) + ((5-b)*(size.y+2)); // size of each block plus a gap between them
			if(pattern[p] & (0x1 << b)){ // draw block only if it's bit is true (Top to button)

					// check if the the obstacle overlaps with other object
					if (tmp_x > interact_obj.getLocation().x && 
						tmp_x < interact_obj.getLocation().x + interact_obj.getSize().x){
							
							if (start_y < (interact_obj.getLocation().y + interact_obj.getSize().y)-1)
								result = false;
					}
			
					drawBlock(vector(tmp_x, start_y), vector(tmp_x+size.x, start_y+size.y), color); 
			}
			
		}
		tmp_x += size.x; //create some space after second pattern
		
	}
	
	if (tmp_x == 0) startWidth = w.getWidth()+1;
	
	startWidth--;
	
	return result;
}


void Obstacles::drawBlock(vector start, vector end, int color) {
	/// draw a filled rectangular 
	for (int i=start.y; i<=end.y; i++){
		for (int j=start.x; j<=end.x; j++){
			w.drawPixel(j,i, color);
		}
	}	

}
