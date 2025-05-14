#include "i2c.h"
#include "ssd1306.h"
#include <string.h>
#include <xc.h>
#include "font6x8.h"  // Usa una fuente de 6x8
#define _XTAL_FREQ 4000000

void SSD1306_Command(unsigned char cmd) {
    I2C_Start();
    I2C_Write(SSD1306_I2C_ADDRESS);
    I2C_Write(0x00);  // Co = 0, D/C# = 0
    I2C_Write(cmd);
    I2C_Stop();
}

void SSD1306_Data(unsigned char data) {
    I2C_Start();
    I2C_Write(SSD1306_I2C_ADDRESS);
    I2C_Write(0x40);  // Co = 0, D/C# = 1
    I2C_Write(data);
    I2C_Stop();
}

void SSD1306_Init(void) {
    __delay_ms(100);
    SSD1306_Command(0xAE); // Display OFF

    SSD1306_Command(0x20); // Set Memory Addressing Mode
    SSD1306_Command(0x00); // Horizontal Addressing Mode

    SSD1306_Command(0xB0); // Page Start
    SSD1306_Command(0xC8); // COM Output Scan Direction

    SSD1306_Command(0x00); // Low column
    SSD1306_Command(0x10); // High column

    SSD1306_Command(0x40); // Start line

    SSD1306_Command(0x81); // Contrast
    SSD1306_Command(0xFF);

    SSD1306_Command(0xA1); // Segment Re-map
    SSD1306_Command(0xA6); // Normal Display
    SSD1306_Command(0xA8); SSD1306_Command(0x3F); // Multiplex Ratio

    SSD1306_Command(0xA4); // Display follows RAM
    SSD1306_Command(0xD3); SSD1306_Command(0x00); // Display Offset

    SSD1306_Command(0xD5); SSD1306_Command(0xF0); // Clock divide
    SSD1306_Command(0xD9); SSD1306_Command(0x22); // Pre-charge
    SSD1306_Command(0xDA); SSD1306_Command(0x12); // COM Pins
    SSD1306_Command(0xDB); SSD1306_Command(0x20); // VCOMH Deselect

    SSD1306_Command(0x8D); SSD1306_Command(0x14); // Charge Pump

    SSD1306_Command(0xAF); // Display ON
}

void SSD1306_SetCursor(unsigned char x, unsigned char y) {
    SSD1306_Command(0xB0 + y);
    SSD1306_Command(((x & 0xF0) >> 4) | 0x10);
    SSD1306_Command((x & 0x0F) | 0x00);
}

void SSD1306_Clear(void) {
    for (unsigned char page = 0; page < 8; page++) {
        SSD1306_SetCursor(0, page);
        for (unsigned char col = 0; col < 128; col++) {
            SSD1306_Data(0x00);
        }
    }
}

void SSD1306_PrintChar(char c) {
    for (uint8_t i = 0; i < 6; i++) {
        SSD1306_Data(font6x8[c - 32][i]);
    }
}

void SSD1306_PrintString(const char* str) {
    while (*str) {
        SSD1306_PrintChar(*str++);
    }
}


