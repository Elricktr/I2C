#include <xc.h>
#define _XTAL_FREQ 4000000

void I2C_Init(const unsigned long c) {
    SSPCON = 0b00101000;  // Master mode, SSPEN = 1
    SSPCON2 = 0;
    SSPADD = (unsigned char)((_XTAL_FREQ / (4 * c)) - 1);
    SSPSTAT = 0;
    TRISC3 = 1; // SCL como entrada
    TRISC4 = 1; // SDA como entrada
}

void I2C_Start(void) {
    SEN = 1;
    while (SEN);
}

void I2C_Stop(void) {
    PEN = 1;
    while (PEN);
}

void I2C_Write(unsigned char d) {
    SSPBUF = d;
    while (BF);
    while (SSPSTATbits.R_nW);
    while (SSPCON2bits.ACKSTAT);
}

unsigned char I2C_Read(unsigned char ack) {
    RCEN = 1;
    while (!BF);
    unsigned char data = SSPBUF;
    ACKDT = !ack;
    ACKEN = 1;
    while (ACKEN);
    return data;
}

