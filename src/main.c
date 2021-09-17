#if defined(__SAMD21G18A__)
# include <samd21g18a.h>
#elif defined(__SAM3X8E__)
# include <sam3x8e.h>
#endif

int main() {
	SystemInit();
	SystemCoreClockUpdate();

#if defined(__SAMD21G18A__)
	// LEDs: PA17 == L (red), PA27 == TX (yellow)
	// They are in one group, so we can set them both at the same time.
	#define LEDS (PORT_PA17 | PORT_PA27)
	PORT->Group[0].DIR.reg = LEDS;

	// Set Data Output Value Toggle to let them blink alternately:
	// L is on when state is set, TX is on when state is cleared
	for (;;) {
		PORT->Group[0].OUTTGL.reg = LEDS;
		for (volatile int i = 0; i < 100000; i++) {}
	}
#elif defined(__SAM3X8E__)
	//
	// Acronyms: OER = Output Enabled Register
	//					 SODR = Set Output Data Register
	//					 CODR = Clear Output Data Register
	//
	// LEDs: PB27 == L (yellow) and PA21 == TX (yellow)
	// They are in different groups, so we must set them individually.
	PIOA->PIO_OER = PIO_PA21;
	PIOB->PIO_OER = PIO_PB27;

	// Set and clear them explicitly:
	// L is on when state is set, TX is on when state is cleared
  for (;;) {
		PIOA->PIO_SODR = PIO_PA21; // Turn off TX
		PIOB->PIO_SODR = PIO_PB27; // Turn on L
		for (volatile int i = 0; i < 1000000; i++) {}

		PIOB->PIO_CODR = PIO_PB27; // Turn off L
		PIOA->PIO_CODR = PIO_PA21; // Turn on TX
		for (volatile int i = 0; i < 1000000; i++) {}
	}
#endif

	return 0;
}
