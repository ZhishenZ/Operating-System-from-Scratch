#include "uart.h"
#include "lib.h"

void write_char(unsigned char c)
{
    // if the bit 5 of the value is 1, it means that the transmit FIFO is full.
    // only when the bit 5 is 0 we then can write data to the uart.
    while (in_word(UART0_FR) & (1 << 5)) { }
    // write the word to the buffer register
    out_word(UART0_DR, c);
}


unsigned char read_char(void)
{
    // first check the bit 4 of the flag register
    // if it is set, we will wait until there is data in the receive buffer.
    while (in_word(UART0_FR) & (1 << 4))
    {
    };

    return in_word(UART0_DR);
}

void write_string(const char *string)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        write_char(string[i]);
    }
}

// initialization function
void init_uart(void)
{
    // 1: we disable the uart0 and then do the initialization---------------------------------
    // write 0 to the control register.
    out_word(UART0_CR, 0);

    // 2: set the baud rate ------------------------------------------------------------------
    // 2.1: set IBRD Integer Baud rate divisor
    // 2.2: set Fractional Baud rate divisor
    // the default value of the UART clock is 48 MHz and the baud rate is 115200

    // 48*1000000/(16*115200) = 26.04166
    // integer part 26
    // fractional part 0.4166 * (2^6) ~= 2.6 here we just simply write 0
    out_word(UART0_IBRD, 26);
    out_word(UART0_FBRD, 0);

    // 3--------------------------------------------------------------------------------------
    // we write 1 to bit 4 line control register to enable fifo buffer
    // write 1 to bit 5 and 6 to enable 8-bit data mode.
    out_word(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    // 4--------------------------------------------------------------------------------------
    // mask all the interrupts since we do not use interrupt in this example.
    // we write 0 to the Interrupt Mask Set/Clear Register
    out_word(UART0_IMSC, 0);

    // 5---------------------------------------------------------------------------------------
    // set bit 0 of the control register to enable UART
    // set bit 8 and bit 9 to enable receiver and transmitter
    out_word(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}