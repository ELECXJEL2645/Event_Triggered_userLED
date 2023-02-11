/*	Event_Triggered_userLED
*	====================
*
*	Function:               Preform an ISR upon the detection of an event (a button press - joystick button)
*	Circuit Schematic No.:
*	Required Libraries:     
*
*	Authored by:            Dr Craig Evans
*	Date:                   
*	Collaberators:          Andrew Knowles
*				Dr Tim Amsdon
*	Version:                1.0
*	Revision Date:          02/2023 
*	MBED Studio Version:    1.4.1
*	MBED OS Version:        6.12.0
*	Board:	                NUCLEO L476RG	*/
 
#include "mbed.h"
 
// Create objects for button A and LED1
InterruptIn joystick_button(PC_10);
DigitalOut user_led(LED1);
 
// flag - must be volatile as changes within ISR
// g_ prefix makes it easier to distinguish it as global
volatile int g_buttonA_flag = 0;
 
// function prototypes
void joystick_button_isr();
int state = 0;
 
int main(){
    // The joystick contains a switch which connects to ground when pressed, therefore the interrupt pin defaults to 3.3 V
    // which is set using internal pull-up resistor mode. When the button is pressed the pin goes from 3.3 V to 0 V, 
    // therefore we need to look for a falling-edge on the pin to trigger the interrupt
    joystick_button.fall(&joystick_button_isr);
	
    // since the joystick button connects to ground when pressed
    // we should set the internal resistor to pull-up
    joystick_button.mode(PullUp);
	
	user_led = state;
 
    while (1) {
 
        // check if flag i.e. interrupt has occured
        if (g_buttonA_flag) {
            g_buttonA_flag = 0;  // if it has, clear the flag
			
			state = !state;
			user_led = state;
        }
 
        // put the MCU to sleep until an interrupt wakes it up
        sleep();
    }
}
 
// Button A event-triggered interrupt
void joystick_button_isr(){
    g_buttonA_flag = 1;   // set flag in ISR
}
