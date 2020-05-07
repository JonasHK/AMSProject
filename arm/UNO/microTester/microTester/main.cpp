#define F_CPU 16000000
#include <avr/io.h>
#include "uart.h"
#include "d_SysTime.h"
#include <util/delay.h>

#include <avr/interrupt.h>

#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (F_CPU / 1000L) )
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
// the fractional number of milliseconds per timer0 overflow. we shift right
// by three to fit these numbers into a byte. (for the clock speeds we care
// about - 8 and 16 MHz - this doesn't lose precision.)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)
volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;

volatile uint8_t count;

ISR (TIMER0_OVF_vect)
{
	unsigned long m = timer0_millis;
	unsigned char f = timer0_fract;

	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;
}

unsigned long millis()
{
	unsigned long m;
	//uint8_t oldSREG = SREG;

	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer0_millis)
	cli();
	m = timer0_millis;
	//SREG = oldSREG;
	sei();
	return m;
}



int main (void)
{
	InitUART(UART0,9600,8,0);
	initTimer();
	unsigned long start = Micro();
	_delay_ms(1001);
	unsigned long stop = Micro();
	start = ~1;
	SendInteger(UART0,start);
	SendString(UART0,"\n\r");
	SendInteger(UART0,stop);
	SendString(UART0,"\n\r");	
	/*
	DDRB |= (1<<0);
	TCNT0 = 0;
	count = 0;
	TCCR0B |= (0<<CS02) | (1<<CS01) | (1<<CS00); // PRESCALER 64
	TIMSK0 = (1<<TOIE0);
	sei();
	
	InitUART(UART0,9600,8,0);
	SendString(UART0,"Start:\n\r");
	while(1)
	{
		SendInteger(UART0,millis());
		SendString(UART0,"\n\r");
		_delay_us(50000);

	}
	*/
}