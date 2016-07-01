#include "matrix.hpp"
#include <cstring>


static matrix* current_display;


matrix::matrix(int width, int height, bool double_buffer):
			Screen(width, height), double_buffer ( double_buffer ),
			t_delay( 1 ),
	_lat ( hwlib::target::pin_out( hwlib::target::pins::d43) ),
	_oe ( hwlib::target::pin_out( hwlib::target::pins::d42) ),
	_clk ( hwlib::target::pin_out( hwlib::target::pins::d39) ),
	_selA ( hwlib::target::pin_out( hwlib::target::pins::d25) ),
	_selB ( hwlib::target::pin_out( hwlib::target::pins::d26) ),
	_selC ( hwlib::target::pin_out( hwlib::target::pins::d27) ),
	_selD ( hwlib::target::pin_out( hwlib::target::pins::d28) ),
	_b1 ( hwlib::target::pin_out(hwlib::target::pins::d33) ),
	_g1 ( hwlib::target::pin_out(hwlib::target::pins::d34) ),
	_r1 ( hwlib::target::pin_out(hwlib::target::pins::d35) ),
	_b2 ( hwlib::target::pin_out(hwlib::target::pins::d36) ),
	_g2 ( hwlib::target::pin_out(hwlib::target::pins::d37) ),
	_r2 ( hwlib::target::pin_out(hwlib::target::pins::d38) )
{
	useDefault = true;
	
	PIOC->PIO_OWER = 0x7F << 1; //Enable R1G1B1R2G2B2 and clk
	PIOD->PIO_OWER = 0xF; //Enable ABCD
	PIOA->PIO_OWER = 0x03 << 19; // Enable OE and LAT
	
	PIOC->PIO_OER = 0x7F << 1;
	PIOD->PIO_OER = 0xF;
	PIOA->PIO_OER = 0x03 << 19;
	
	PIOC->PIO_CODR = PIO_PC1;
	PIOC->PIO_CODR = PIO_PC2;
	PIOC->PIO_CODR = PIO_PC3;
	PIOC->PIO_CODR = PIO_PC4;
	PIOC->PIO_CODR = PIO_PC5;
	PIOC->PIO_CODR = PIO_PC6;
	
	init();
}

matrix::matrix(int width, int height, bool double_buffer, target::pin_out  _lat,
			target::pin_out  _oe, target::pin_out  _clk,
			target::pin_out  _selA, target::pin_out  _selB,
			target::pin_out  _selC, target::pin_out  _selD,
			target::pin_out  _b1, target::pin_out  _g1,
			target::pin_out  _r1, target::pin_out  _b2,
			target::pin_out   _g2, target::pin_out _r2):
			Screen(width, height), double_buffer ( double_buffer ),
			t_delay( 1 ),
	_lat ( _lat ),
	_oe ( _oe ),
	_clk ( _clk ),
	_selA ( _selA ),
	_selB ( _selB ),
	_selC ( _selC ),
	_selD ( _selD ),
	_b1 ( _b1 ),
	_g1 ( _g1 ),
	_r1 ( _r1 ),
	_b2 ( _b2 ),
	_g2 ( _g2 ),
	_r2 ( _r2 )
{
	useDefault = false;
	init();
}

void matrix::init()
{
	current_buffer = front_buffer;
	next_buffer = back_buffer;
	
	
	current_bit = 0;
	current_row = 0;
	
	swap_flag = false;
	swap_copy = false;

	clear();
	
	
	_lat.set(false);
	_oe.set(false);
	_clk.set(false);
	_selA.set(false);
	_selB.set(false);
	_selC.set(false);
	_selD.set(false);
	_r1.set(false);
	_r2.set(false);
	_g1.set(false);
	_g2.set(false);
	_b1.set(false);
	_b2.set(false);
	
	
    // Disable the write protect of PMC register
    REG_PMC_WPMR = 0x504D43;
    // Enable peripheral clock
    REG_PMC_PCER0 = 0x01 << 30; // TC1 channel 0, ID:30
    REG_PMC_PCER0 = 0x3F << 11; // ALL GPIO ports
    REG_PMC_SCER = 0x01 << 9;

    // Disable the write protect of TC register
    REG_TC1_WPMR = 0x54494D;

    // Disable the clock
    REG_TC1_CCR0 = 0b010;
    //Set the channel mode register
    REG_TC1_CMR0 = 0x02; // Select clock MKC/32
    REG_TC1_CMR0 |= 0x01 << 14; // Enable compare RC trigger
    REG_TC1_CCR0 |= 0x00 << 15; // Enable compare mode (Wave = 0)
    //Counter periode
    REG_TC1_RC0 = t_delay; // Frequenty of 
    REG_TC1_IER0 = 0x01 << 4; // Enable Inerrupt on counter RC
    REG_TC1_IDR0 = 0xEF; // Disable other interrupts
    // Enable interrupt handlers
    NVIC_EnableIRQ(TC3_IRQn); // TC1 channel0	
	NVIC_SetPriority(TC3_IRQn, 1);

}

void matrix::clear(){
	fillScreen(0);
}


void matrix::drawPixel(int x, int y, uint8_t rc, uint8_t gc, uint8_t bc){
//	x -= 1;
//	y -= 1;
	
	if (x >=width || y >=height || x < 0 || y < 0) return;
	
	uint8_t r, g, b;
	
	rc = gamma[rc];
	gc = gamma[gc];
	bc = gamma[bc];

		   
  for (int i=0; i<CBIT; i++){	
	
	r = ((rc >> i) & 0x01) ;
	g = ((gc >> i) & 0x01) ;
	b = ((bc >> i) & 0x01) ;
	
	uint8_t *tmp_buffer;
	if (double_buffer)
		tmp_buffer = next_buffer;
	else
		tmp_buffer = current_buffer;

//	if (double_buffer){
//		if (y<(height/2))  // Top half of screen
//		  next_buffer[y*COL+(i*width+x)] = (((next_buffer[y*COL+(i*width+x)]) & 0b01110000) | 
//									((r << 3) | (g << 2) | (b << 1)));   // Change only LSB bits
//		else // second half of screen
//		  next_buffer[((y-(height/2))*COL)+(i*width+x)] = (((next_buffer[((y-(height/2))*COL)+(i*width+x)]) & 0b00001110) | 
//									((r << 6) | (g << 5) | (b << 4)));   //Change MSB bits
//	}
//	else {
		if (y<(height/2))  // Top half of screen
		  tmp_buffer[y*COL+(i*width+x)] = (((tmp_buffer[y*COL+(i*width+x)]) & 0b01110000) |
								((r << 3) | (g << 2) | (b << 1)));   // Change only LSB bits
		else // second half of screen
		  tmp_buffer[((y-(height/2))*COL)+(i*width+x)] = (((tmp_buffer[((y-(height/2))*COL)+(i*width+x)]) & 0b00001110) | 
								((r << 6) | (g << 5) | (b << 4)));   //Change MSB bits		
//	}

  }
}


void matrix::drawPixel(int x, int y, uint32_t color){
	if (x >=width || y >=height || x < 0 || y < 0) return;
	uint8_t rc, gc, bc;
	bc = (color & 0xFF);
	gc = ((color >> 8) & 0xFF);
	rc = ((color >> 16) & 0xFF);
	
	drawPixel(x, y, rc, gc, bc);
}

void matrix::fillScreen(uint8_t r, uint8_t g, uint8_t b){
	for (int y=0; y<height; y++){
		for(int x=0; x<width; x++){
			drawPixel(x, y, r, g, b);
		}
	}
}

void matrix::fillScreen(uint32_t color){
	for (int y=0; y<height; y++){
		for(int x=0; x<width; x++){
			drawPixel(x, y, color);
		}
	}	
}

void matrix::start(){
	current_display = this; // Interrupt handler uses this to find the current led matrix object
	// start the timer counter
	REG_TC1_CCR0 = 0b101; //enable and restart the counter
}

void matrix::stop(){
	// Disable the counter
	REG_TC1_CCR0 = 0b010;
}

void matrix::swap_buffer(bool copy){
	if (double_buffer == true){
		swap_flag = true;
		swap_copy = copy;
		while (swap_flag == true) {
			
		}
	}
}


void matrix::update2() {
    // calculate the next interrupt time
    if (current_bit == CBIT){
		if (current_row == 15) {
			current_row=-2;
			t_delay = 1;
		}
		else if (current_row == -2) {
			current_row = -1;
			t_delay = 13125; // refresh the screen with 200 HZ rate
			_oe.set(true); //OE HIGH
			if (swap_flag == true){
				uint8_t *tmp = current_buffer;
				current_buffer = next_buffer;
				next_buffer = tmp;
				if (swap_copy){
					memcpy(next_buffer, current_buffer, ROW*COL);
					swap_copy = false;
				}
				swap_flag = false;
			}	
		}
		else if (current_row == -1){
			current_bit = 0;
			t_delay = 1;
			current_row = 0;      
		}
		else {
			current_row++;
			t_delay = 1;
			current_bit = 0;
		}
    }
    else {
        t_delay <<= 1;
        int finish=(current_bit*width)+width;
		_oe.set(true); //OE HIGH 
	
		uint8_t data;
        for (int i=current_bit*width; i<finish; i++){
            _clk.set(false); //clock down

			data = current_buffer[current_row*COL+i];
			_b1.set((data >> 1) & 0x01);
			_g1.set((data >> 2) & 0x01);
			_r1.set((data >> 3) & 0x01);
			_b2.set((data >> 4) & 0x01);
			_g2.set((data >> 5) & 0x01);
			_r2.set((data >> 6) & 0x01);
            
			_clk.set(true); //clock high
        }
		
        
        //Set Row adrees
		_selA.set((current_row) & 0x01);
		_selB.set((current_row >> 1) & 0x01);
		_selC.set((current_row >> 2) & 0x01);
		_selD.set((current_row >> 3) & 0x01);
        
        
       _lat.set(true); //LAT HIGH
       _lat.set(false); //LAT LOW
	   
	   
        
		current_bit++;      
       _oe.set(false); //OE LOW
    }
		
    REG_TC1_RC0 = t_delay; //apply new interrupt time
	
}

void matrix::update(void){
    // calculate the next interrupt time
    if (current_bit == CBIT){
		if (current_row == 15) {
			current_row=-2;
			t_delay = 1;
		}
		else if (current_row == -2) {
			current_row = -1;
			t_delay = 13125; // refresh the screen with 200 HZ rate
			PIOA->PIO_SODR = PIO_PA19; //OE HIGH						
			if (swap_flag == true){
				uint8_t *tmp = current_buffer;
				current_buffer = next_buffer;
				next_buffer = tmp;
				if (swap_copy){
					memcpy(next_buffer, current_buffer, ROW*COL);
					swap_copy = false;
				}
				swap_flag = false;
			}	
		}
		else if (current_row == -1){
			current_bit = 0;
			t_delay = 1;
			current_row = 0;      
		}
		else {
			current_row++;
			t_delay = 1;
			current_bit = 0;
		}
    }
    else {
        t_delay <<= 1;
        int finish=(current_bit*width)+width;
        
		PIOA->PIO_SODR = PIO_PA19; //OE HIGH 

        for (int i=current_bit*width; i<finish; i++){
//           PIOC->PIO_CODR = PIO_PC7; //clock down (It's not needed the 8e bits of buffer is always 0)
            // Set RGB top and RGB second half 
			// PIOC->PIO_ODSR = ((PIOC->PIO_ODSR) & (0xFFFFFF)) | current_buffer[current_row*COL+i];
			PIOC->PIO_ODSR = current_buffer[current_row*COL+i];
            //clock high
			PIOC->PIO_SODR = PIO_PC7;
        }
		
        

        //Set Row adrees ((PIOD->PIO_ODSR) & (0xF)) |
		PIOD->PIO_ODSR =  current_row;
		
        
        
       PIOA->PIO_SODR = PIO_PA20; //LAT HIGH
       PIOA->PIO_CODR = PIO_PA20; //LAT LOW
	   
        
		current_bit++;      
       PIOA->PIO_CODR = PIO_PA19; //OE LOW
    }
		
    REG_TC1_RC0 = t_delay; //apply new interrupt time
	
}


void TC3_Handler(void){
	volatile uint32_t status = REG_TC1_SR0; // Accept the interrupt!
	REG_PIOB_OER = 0x00 << status; // consume the status or embrace an eerror from the compiler!!!
	REG_TC1_CCR0 = 0b010;
	if (current_display->is_using_default_pins())
		current_display->update();
	else
		current_display->update2();
	REG_TC1_CCR0 = 0b101; // Enable and restart the timer 
}
