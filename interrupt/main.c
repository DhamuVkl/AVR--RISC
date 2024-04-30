#include <avr/io.h>
#include <avr/interrupt.h>

// goal is to flip LED every second;
#define F_CPU 16000000
ISR(TIMER1_OVF_vect)
{
  PORTB ^= _BV(PORTB5);
  TCNT1 = 65535 - (F_CPU / 1024);
}
int main(void)
{

  DDRB |= _BV(DDB5);

  // this has a max value of 65535
  TCNT1 = 65535 - (F_CPU / 1024);
  // sets the prescaler to 1024
  // 16M/1024 = 15625Hz
  TCCR1B = (1 << CS10) | (1 << CS12);
  TCCR1A = 0X00;
  TIMSK1 = (1 << TOIE1);

  sei();

  while (1)
  {
    ;
    ;
  }
}