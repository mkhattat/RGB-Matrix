#include "String.hpp"
#include "Timer.hpp"

String::String(Screen &w, const uint8_t *font, char *text, uint8_t r, uint8_t g, uint8_t b, vector location):
		Graphics(w, vector(0,0), location), font (font), text (text),
		color_red (r), color_green (g), color_blue(b)
{}


String::String(Screen &w, const uint8_t *font, char *text, uint32_t color, vector location):
		Graphics(w, vector(0,0), location), font (font), text (text)
{
	color_blue = (color & 0xFF);
	color_green = ((color >> 8) & 0xFF);
	color_red = ((color >> 16) & 0xFF);

}


void String::draw() {
	uint8_t width, height, c;
	uint8_t tmp_y;
	uint16_t offset;
	
	int tmp_x = location.x;
	
	for (int i=0; text[i] != '\0'; i++){
		c = text[i];
		if (c > 32){
			c = c - 33;
			width = font[c*4];
			height = font[c*4+1];
			if (this->maxHeight < height) this->maxHeight = height;
			offset = font[c*4+3] << 8;
			offset |= font[c*4+2];
			offset += 376;
			tmp_y = (height - location.y)*-1;
			for (int y = 0; y<height; y++){
				for (int x=0; x<width; x++){
					uint8_t color = font[(y*width)+(x)+offset];
					uint8_t per = (color*100)/255;
					w.drawPixel(x + tmp_x, y + tmp_y, (per*color_red)/100, (per*color_green)/100, (per*color_blue)/100);			
				}
			}	
		}
		tmp_x += width + 1;
	}			
}



void String::scroll(int updateInterval, bool loop, int startX) {

	if (startX > w.getWidth()) startX = w.getWidth();

	uint8_t width, height, c;
	uint8_t tmp_y;
	uint16_t offset;
	
	int start = startX;
	int tmp_x = start;
	
	Timer t;
	
	while (true){
		for (int i=0; text[i] != '\0';i++){
			c = text[i];
			if (c > 32){
				c = c - 33;
				width = font[c*4];
				height = font[c*4+1];
				if (this->maxHeight < height) this->maxHeight = height;
				offset = font[c*4+3] << 8;
				offset |= font[c*4+2];
				offset += 376;
				tmp_y = (height - location.y)*-1;
				if (tmp_x >= width*-1){ // to prevent vanishing letter
					for (int y = 0; y<height; y++){
						for (int x=0; x<width; x++){
							uint8_t color = font[(y*width)+(x)+offset];
							uint8_t per = (color*100)/255;
							w.drawPixel(x + tmp_x, y + tmp_y, (per*color_red)/100, (per*color_green)/100, (per*color_blue)/100);			
						}								
					}
				}
			}
			tmp_x += width + 1;
			if (tmp_x > startX) break;
		}
		if (tmp_x == 0) {
			if (loop)
				start = startX+1;
			else
				break;
		}
		start--;
		tmp_x = start;
		w.swap_buffer(true);
		t.delayMilliseconds(updateInterval);
		clear(startX);
	}
}

void String::clear(int startX){		
	for(int y=(location.y - this->maxHeight); y<=location.y; y++)
		for (int x = 0; x < startX; x++ ){
			w.drawPixel(x, y, 0);
		}
}

void String::setColor(uint32_t c){
	color_blue = (c & 0xFF);
	color_green = ((c >> 8) & 0xFF);
	color_red = ((c >> 16) & 0xFF);
}

void String::setColor(uint8_t rc, uint8_t gc, uint8_t bc){
	color_blue = bc;
	color_green = gc;
	color_red = rc;

}