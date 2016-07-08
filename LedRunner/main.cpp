#include "init.c"
#include "hwlib.hpp"

#include "matrix.hpp"

#include "photos/simpson.h"
#include "photos/hu.h"
#include "photos/gameover.h"
#include "fonts/tahoma8.h"
#include "fonts/tahoma10.h"
#include "animations/runner.h"
#include "animations/animation.h"

#include "straightLine.hpp"
#include "Runner.hpp"
#include "Obstacles.hpp"

namespace target = hwlib::target;

void presentation(){
	auto next_button = hwlib::target::pin_in(hwlib::target::pins::d2);
	Timer t;
	
//	matrix led(64, 32, true, target::pins::d43, target::pins::d42, target::pins::d39,
//				target::pins::d25, target::pins::d26, target::pins::d27, target::pins::d28,
//				target::pins::d33, target::pins::d34, target::pins::d35, target::pins::d36,
//				target::pins::d37, target::pins::d38);
	matrix led(64, 32, true);
	led.start();

	/* Colors with diffrent brightness
	for (int y=0; y<16; y++){
		for (int x=0; x<32; x++){
			led.drawPixel(x, y, 0, 35,0); 
		}
	}
	for (int y=0; y<16; y++){
		for (int x=32; x<64; x++){
			led.drawPixel(x, y, 0, 75,0); 
		}
	}
	for (int y=16; y<32; y++){
		for (int x=0; x<32; x++){
			led.drawPixel(x, y, 0, 255,0); 
		}
	}
	for (int y=16; y<32; y++){
		for (int x=32; x<64; x++){
			led.drawPixel(x, y, 0, 150,0); 
		}
	}
	led.swap_buffer(false);
	while (next_button.get()){
		
	}
	*/

	led.clear();
	Image im(led, simpson, vector(15, 0));
	im.draw();
	led.swap_buffer(false);
	while (next_button.get()){
		
	}
	t.delayMilliseconds(1000);	
	
	led.clear();
	AnimatedImage a_im(led, animation, vector(15,1));
	while (next_button.get()){
		a_im.draw(5, false);
	}


	t.delayMilliseconds(1000);	
	led.clear();
	Image im2(led, hu, vector(48, 0));
	im2.draw();
	String title(led, tahoma10, (char*)"hu.nl", 0xFA0000, vector(0, 10));
	title.draw();
	const char *text = "De Hogeschool van Utrecht ontstond in 1988 in de stad en provincie Utrecht.";
	String str(led, tahoma10, (char*)text, 0x878BFF, vector(0, 28));
	while (next_button.get()){
		str.scroll(15, false);
	}
	t.delayMilliseconds(1000);	
}

void runGame(){
//	matrix led(64, 32, true, target::pins::d43, target::pins::d42, target::pins::d39,
//				target::pins::d25, target::pins::d26, target::pins::d27, target::pins::d28,
//				target::pins::d33, target::pins::d34, target::pins::d35, target::pins::d36,
//				target::pins::d37, target::pins::d38);
	matrix led(64, 32, true);
	led.start();

	auto jump_button = hwlib::target::pin_in(hwlib::target::pins::d2);
	auto flip_button = hwlib::target::pin_in(hwlib::target::pins::d3);
	
	uint32_t line_color = 0xFA00;
	
	Timer t;

	while (1) {
		
		AnimatedImage aim(led, runner, vector(10,9));
		Runner doll(aim, jump_button);
		Obstacles obs(led, flip_button);
		
		straightLine l(led, vector(0, 19), vector(63, 19), line_color);	
		
		String points(led, tahoma8, (char*)"0", 255, 0,0, vector(0, 7));
		
		bool next = true;
		
		// menue
		while (jump_button.get() && flip_button.get()){
			led.clear();
			String s1(led, tahoma10, (char*)"Press a key", 0x73A81E, vector(5, 15));
			String s2(led, tahoma10, (char*)"to start", 0x73A81E, vector(15,25));
			s1.draw();
			s2.draw();
			led.swap_buffer(false);
		}
		
		// run the game
		while (next){
			led.clear();
			
			doll.update();
			if (obs.update(doll) == false)
				next = false;
				
			points.draw();
			l.setColor(line_color);
			l.print();
			
			led.swap_buffer(false);
			line_color += 500;
			
		}
		
		t.delayMilliseconds(800);
		
		// Losed the game
		do {
			
			led.clear();
			led.swap_buffer(false);
			t.delayMilliseconds(200);	
			
			led.clear();
			String s1(led, tahoma10, (char*)"Game", 0XBA005D, vector(5, 15));
			String s2(led, tahoma10, (char*)"Over", 0XBA005D, vector(5, 25));
			Image im(led, gameover, vector(32, 0));
			im.draw();
			s1.draw();
			s2.draw();
			led.swap_buffer(false);
			t.delayMilliseconds(300);
			
		} while (jump_button.get() && flip_button.get());
		
		
	} // end WHILE(1)
	
}


int main(void){


	// the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	// Set the clock up
	systemInit(); //84 MHZ
	
	presentation();
	
	runGame();
	
	while (1){	
		
		
	} // WHILE(1)
} //main
