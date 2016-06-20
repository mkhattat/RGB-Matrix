#include "straightLine.hpp"

void straightLine::print(){
	   
	if (start.x == end.x){
		for (int y=start.y; y<=end.y; y++){
			w.drawPixel(start.x, y, color);
		}
	}
	else if (start.y == end.y) {
		for (int x = start.x; x<=end.x; x++){
			w.drawPixel(x, start.y, color);
		}
	}

}