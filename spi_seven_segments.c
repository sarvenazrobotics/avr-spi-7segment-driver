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
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void main(void)
{   uint8_t digits[4] = {1, 2, 3, 4};  // Number to display

    SPI_init();


    while(1)
    {send_16bit(0b1110, seg_code[9]);
    delay_ms(5);

    // 4
    send_16bit(0b1101, seg_code[4]);
    delay_ms(5);

    // 6
    send_16bit(0b1011, seg_code[6]);
    delay_ms(5);

    // 7
    send_16bit(0b0111, seg_code[7]);
    delay_ms(5);

    }
}