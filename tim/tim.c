#include <avr/io.h>

// Initialize Timer/Counter1
void timer1_init() {
    // Set Timer/Counter1 Control Register A (TCCR1A)
    TCCR1A = 0; // Normal mode, OC1A and OC1B disconnected

    // Set Timer/Counter1 Control Register B (TCCR1B)
    TCCR1B = (1 << CS11) | (1 << CS10); // Prescaler = 64

    // Set Timer/Counter1 Control Register C (TCCR1C) to 0 (not used in normal mode)

    // Set Timer/Counter1 Register (TCNT1) to 0
    TCNT1 = 0;
}

// Generate variable delay using Timer/Counter1
void custom_delay_ms(int milliseconds) {
    // Calculate the number of timer ticks required for the delay
    uint16_t ticks = (F_CPU / 64) / 1000 * milliseconds;

    // Set Timer/Counter1 Register (TCNT1) to 0
    TCNT1 = 0;

    // Wait until TCNT1 reaches the desired value
    while (TCNT1 < ticks) {
        // Do nothing, just wait
    }
}

int main(void) {
    DDRB |= (1 << DDB5); // Set pin 13 (PORTB5) as output

    int i;

    // Initialize Timer/Counter1
    timer1_init();

    while (1) {
        for (i = 0; i <= 2000; i += 10) {
            PORTB |= (1 << PORTB5); // Turn on LED
            custom_delay_ms(i);
            PORTB &= ~(1 << PORTB5); // Turn off LED
            custom_delay_ms(i);
        }

        // for (i = 200; i >= 0; i -= 10) {
        //     PORTB |= (1 << PORTB5); // Turn on LED
        //     custom_delay_ms(i);
        //     PORTB &= ~(1 << PORTB5); // Turn off LED
        //     custom_delay_ms(i);
        // }
    }
}
