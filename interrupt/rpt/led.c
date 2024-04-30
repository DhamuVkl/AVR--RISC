#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> // Added for _delay_ms()

// goal is to flip LED every second
#define F_CPU 16000000

ISR (TIMER1_OVF_vect)
{
    static uint8_t ledState = 0; // Added a state variable for debouncing

    PORTB ^= _BV(PORTB5);
    TCNT1 = 65535 - (F_CPU / 1024 / 256); // Recalculated with CS12 only
    ledState = ~ledState; // Debounce the LED
}

int main(void)
{

    DDRB |= _BV(DDB5);

    // Calibrate clock using CLKPR
#if defined(__AVR_ATmega328P__) // Replace this with your board's name if different
    CLKPR = _BV(CLKPCE); // Set the Clock Control Register for calibration
    CLKPR = _BV(CLKSRC) | _BV(CLKSWSR); // Select the oscillator and set its start-up time
    while ((CLKPR & _BV(CLKPCE)) != 0) { }; // Wait until calibration is done
#endif

    TCNT1 = 65535 - (F_CPU / 1024 / 256); // Sets the timer value for 1s interval
    TCCR1B = _BV(CS12); // Set the prescaler to 256
    TCCR1A = 0X00;
    TIMSK1 = (1 << TOIE1); // Enable timer overflow interrupt

    sei(); // Enable global interrupts

    while (1)
    {
        _delay_ms(50); // Debouncing delay
    }
}