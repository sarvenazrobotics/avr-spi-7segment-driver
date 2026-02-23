#define F_CPU 16000000UL

#include <io.h>
#include <delay.h>
#include <stdint.h>

/* -------- SPI INIT -------- */
void SPI_init(void)
{
    DDRB |= (1<<3) | (1<<5) | (1<<2);  // MOSI, SCK, LATCH as output
    SPCR = (1<<SPE) | (1<<MSTR);             // Enable SPI, Master mode
}

/* -------- SPI SEND BYTE -------- */
void SPI_send(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1<<SPIF)));  // Wait until transmission complete
}

/* -------- SEND 16 BITS TO BOTH 595 -------- */
void send_16bit(uint8_t digit_byte, uint8_t segment_byte)
{
    PORTB &= ~(1<<2);  // LATCH LOW

    SPI_send(digit_byte);     // goes to second chip
    SPI_send(segment_byte);   // stays in first chip

    PORTB |= (1<<2);   // LATCH HIGH
}

/* -------- SEGMENT TABLE (COMMON ANODE) -------- */
uint8_t seg_code[10] =
{
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

void main(void)
{   uint8_t digits[4] = {1, 2, 3, 4};  // Number to display

    SPI_init();


    while(1)
    {    send_16bit(0b0010,0x99);
         send_16bit(0b0100,0x82);
          send_16bit(0b1000,0xF8);
          send_16bit(0b0001, 0x90);
    }
}