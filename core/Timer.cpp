#include "Timer.hpp"

volatile static uint32_t timer1_flag;

Timer::Timer()
{
	timer1_flag = 0;
	
	// Disable the write protect of PMC register
    REG_PMC_WPMR = 0x504D43;
    // Enable peripheral clock
    REG_PMC_PCER0 = 0x01 << 27; // TC0 channel 0, ID:27
    REG_PMC_PCER0 = 0x3F << 11; // ALL GPIO ports
    REG_PMC_SCER = 0x01 << 8;

    // Disable the write protect of TC register
    REG_TC1_WPMR = 0x54494D;

    // Disable the clock
    REG_TC0_CCR0 = 0b010;
    //Set the channel mode register
    REG_TC0_CMR0 = 0x00; // Select clock MKC/2
    REG_TC0_CMR0 |= 0x01 << 14; // Enable compare RC trigger
    REG_TC0_CCR0 |= 0x00 << 15; // Enable compare mode (Wave = 0)
    //Counter periode
    REG_TC0_RC0 = 42; // Frequenty of 1 MHZ
    REG_TC0_IER0 = 0x01 << 4; // Enable Inerrupt on counter RC
    REG_TC0_IDR0 = 0xEF; // Disable other interrupts
    // Enable interrupt handlers
    NVIC_EnableIRQ(TC0_IRQn); // TC0 channel0	
	NVIC_SetPriority(TC0_IRQn, 0);

}

void Timer::start(){
	timer1_flag = 0;
	// start the timer counter
	REG_TC0_CCR0 = 0b101; //enable and restart the counter
}

void Timer::stop(){
	// Disable the counter
	REG_TC0_CCR0 = 0b010;
}

void Timer::delayMicroseconds(uint32_t micro){
	start();
	while (timer1_flag < micro){
			
	}
	stop();
}

void Timer::delayMilliseconds(uint32_t millis){
	start();
	uint32_t counter = millis*1000;
	while (timer1_flag < counter){
			
	}
	stop();
}

void TC0_Handler(void){
	volatile uint32_t status = REG_TC0_SR0; // Accept the interrupt!
	REG_PIOB_OER = 0x00 << status; // consume the status or embrace an error from the compiler!!!
	timer1_flag++;
}
