#include <avr/io.h>
#include <util/delay.h>



#define LED_PIN 5 // Arduino Uno's built-in LED is connected to pin 13, which is mapped to pin 5 of PORTB

// void delay_ms(uint16_t milliseconds)
// {
//     for (uint16_t j = 0; j < milliseconds; j++)
//     {
//         _delay_ms(1);
//     }
// }

int main(void)
{
    // Set pin 5 of PORTB as output
    DDRB |= (1 << LED_PIN);

    // while (1)
    // {
    //     // static int i;

        for (int i = 10; i <= 200; i += 100)
        {
            // Turn on the LED by setting pin 5 of PORTB
            
           // _delay_ms(1000);
            while (i--)
            {
                PORTB |= (1 << LED_PIN);
                /* code */
            }

            // Turn off the LED by clearing pin 5 of PORTB
            
            //_delay_ms(100);
            while (i--)
            {
                PORTB &= ~(1 << LED_PIN);
                /* code */
            }
        }

        // for (i = 200; i >= 0; i -= 10) {
        //     // Turn on the LED by setting pin 5 of PORTB
        //     PORTB |= (1 << LED_PIN);
        //     delay_ms(i);

        //     // Turn off the LED by clearing pin 5 of PORTB
        //     PORTB &= ~(1 << LED_PIN);
        //     delay_ms(i);
        // }
    // }
}