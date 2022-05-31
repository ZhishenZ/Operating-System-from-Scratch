#ifndef _UART_H
#define _UART_H

// why do we write 0xfe200000? in data sheet 1.2.4. Legacy master addresses
//So a peripheral described in this document as being at legacy address 0x7Enn_nnnn is available in the 35-bit address
// space at 0x4_7Enn_nnnn, and visible to the ARM at 0x0_FEnn_nnnn if Low Peripheral mode is enabled.
#define IO_BASE_ADDR    0xfe200000
#define UART0_DR    IO_BASE_ADDR + 0x1000
#define UART0_FR    IO_BASE_ADDR + 0x1018
#define UART0_CR    IO_BASE_ADDR + 0x1030
#define UART0_LCRH  IO_BASE_ADDR + 0x102c
#define UART0_IBRD  IO_BASE_ADDR + 0x1024
#define UART0_FBRD  IO_BASE_ADDR + 0x1028
#define UART0_IMSC  IO_BASE_ADDR + 0x1038


unsigned char read_char(void);
void write_char(unsigned char c);
void write_string(const char *string);
void init_uart(void);


#endif