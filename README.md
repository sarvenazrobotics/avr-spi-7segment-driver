## Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Usage](#-usage)


- ##  Overview

Welcome to the **SPI 7-Segment Display Driver**! This project shows how to interface a **4-digit 7-segment display** with an **ATmega328P** using **SPI** and **74HC595 shift registers**.

Instead of wasting multiple GPIO pins, this design uses just **3 pins** to control all segments and digits. It includes proper **multiplexing logic** for smooth display rendering and supports both **common anode** and **common cathode** configurations.

## Features

###  Key Advantages

| Feature | Direct Drive | This Project |
|---------|-------------|--------------|
| **GPIO Pins Used** | 12+ pins | **3 pins** |
| **MCU Load** | High | **Low (Hardware SPI)** |
| **Display Type** | Fixed | **CA & CC Supported** |
| **Scalability** | Limited | **High (Daisy-chain)** |
| **Brightness** | Constant | **Multiplexed (High Peak)** |

### 🔧 Technical Specifications
- **Protocol:** SPI (Mode 0, MSB First)
- **Shift Registers:** 2x 74HC595 (16-bit output)
- **Refresh Rate:** ~500Hz (2ms per digit)
- **Microcontroller:** ATmega328P @ 16MHz
- **Display:** 4-Digit 7-Segment (Multiplexed)



---




##  Usage




```c
void main(void)
{
    spi_init();
    
    while(1)
    {
        send_16bit(0x01, 0xF9);  // Digit 1 = 1
        delay_ms(2);
        send_16bit(0x02, 0xA4);  // Digit 2 = 2
        delay_ms(2);
        send_16bit(0x04, 0xB0);  // Digit 3 = 3
        delay_ms(2);
        send_16bit(0x08, 0x99);  // Digit 4 = 4
        delay_ms(2);
    }
}

send_16bit(digit, segment)
     │          │
     │          └─→ Segment pattern (0xC0-0x90 for 0-9)
     └─→ Digit select (0x01, 0x02, 0x04, 0x08)
