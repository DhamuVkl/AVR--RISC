#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


volatile int delay_ms = 1000; // Initial delay time in milliseconds
volatile int increment = 10; // Delay increment value

// Timer/Counter1 initialization
void timer1_init() {
    // Set Timer/Counter1 Control Register A (TCCR1A)
    TCCR1A = 0; // Normal mode, OC1A and OC1B disconnected

    // Set Timer/Counter1 Control Register B (TCCR1B)
    TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // CTC mode, Prescaler = 64

    // Set Timer/Counter1 Output Compare Register A (OCR1A) for 1 ms delay at 16 MHz clock
    OCR1A = 250 - 1; // (16e6 / (64 * 1000)) - 1

    // Enable Timer/Counter1 Output Compare A Match Interrupt
    TIMSK1 |= (1 << OCIE1A);
}

// Timer/Counter1 Output Compare A Match Interrupt Service Routine
ISR(TIMER1_COMPA_vect) {
    // Toggle the LED pin (pin 13, PB5)
    PORTB ^= (1 << PORTB5);
}

int main(void) {
    // Set pin 13 (PORTB5) as output
    DDRB |= (1 << DDB5);

    // Initialize Timer/Counter1
    timer1_init();

    // Enable global interrupts
    sei();

    while (1) {
        // Adjust the delay time
        delay_ms += increment;

        // Check if delay has reached maximum value, then start decreasing
        if (delay_ms >= 200) {
            increment = -10; // Decrease the delay
        }

        // Check if delay has reached minimum value, then start increasing again
        if (delay_ms <= 10) {
            increment = 10; // Increase the delay
        }

        // Delay for a short time to allow the interrupt to occur
        _delay_ms(100);
    }

    return 0;
}
