#define F_CPU 1000000UL
#define SCK   0
#define MOSI  1
#define LATCH 4
#include <avr/io.h>
#include <util/delay.h>

/* Very simple bitbanged SPI
 * For using shift registers with ATTiny13 or similar MCU
 * SCK, MOSI and Latch in PB0, PB1, PB4 respectively
 * Need some improvements!
 * by Daniel Couto (@couto0)
 * 11/09/2018
 */

void spi(unsigned char data);

int main(void)
{
    DDRB |= (1<<SCK) | (1<<MOSI) | (1<<LATCH);
    PORTB = 0x00;

    while(1){
        // Simple counter to demonstrate the SPI working
        for(char i=0; i<0xFF; i++){
            spi(i);
            _delay_ms(100);
        }
    }
}

void spi(unsigned char data){
  for(int i = 0; i < 8; i++){
    PORTB = ((data >> 7) << MOSI); //MSB first
    PORTB ^= (1<<SCK); //Clock Pulse
    PORTB ^= (1<<SCK);
    data <<= 1; //Shift 1 bit
  }
  PORTB ^= (1<<LATCH); //Latch Pulse for the 595
  PORTB ^= (1<<LATCH);
}
