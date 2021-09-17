#if defined(__SAMD21G18A__)
# include <samd21g18a.h>
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
#endif

	return 0;
}
