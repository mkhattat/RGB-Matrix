#include "Image.hpp"

void Image::draw(){
	int ww = (size.x)*3;
	for (int y = 0; y<size.y; y++){
		for (int x=0; x<size.x; x++){
			w.drawPixel( (x+location.x), y+location.y,
							image[(y*ww)+(x*3)+3], image[(y*ww)+(x*3+1)+3], image[(y*ww)+(x*3+2)+3]);			
		}
	}				
}
