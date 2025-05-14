#ifndef SSD1306_H
#define SSD1306_H

#define SSD1306_I2C_ADDRESS 0x3C  // 0x3C << 1

void SSD1306_Init(void);
void SSD1306_Command(unsigned char cmd);
void SSD1306_Clear(void);
void SSD1306_SetCursor(unsigned char x, unsigned char y);
void SSD1306_PrintChar(char c);
void SSD1306_PrintString(const char* str);

#endif
