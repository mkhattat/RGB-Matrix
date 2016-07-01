#include "AnimatedImage.hpp"

void AnimatedImage::draw(int updateIntervall, bool loop){
	int frames = image[0];
	Timer t;
	
	while (true){
		for (int i=0; i<frames; i++){
			w.clear();
			drawFrame(i);
			w.swap_buffer(false);
			t.delayMilliseconds(updateIntervall);
		}
		if (loop == false)
			break;
	}
}


void AnimatedImage::draw(){
	draw(10, false);
}

void AnimatedImage::drawFrame(int frame){
	if (frame < getTotalFrames()){
		int ww = (size.x*3);
		int hh = 0;	
		
		hh = (size.y)*frame;
		for (int y = 0; y<size.y; y++){
			for (int x=0; x<size.x; x++){
				w.drawPixel( (x+location.x), y+location.y,
								image[(hh*ww)+(x*3)+6], image[(hh*ww)+(x*3+1)+6], image[(hh*ww)+(x*3+2)+6]);			
			}
			hh += 1;
		}				
	}
}

int AnimatedImage::getTotalFrames(){
	return image[0];
}