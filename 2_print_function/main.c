#include "uart.h"
#include "print.h"


void KMain(void){

    init_uart();
    write_string("Hello, world!\r\n");
    uint64_t value = 0x123456789abcdef;
    printk("print Hello, world! using printk fuction\r\n");
    printk("Test number value in decimal: %u\r\n",value);
    printk("Test number value in hexadecimal: %x\r\n",value);
    printk("12345 in decimal: %d\r\n",12345);
    printk("12345 in hexadecimal: %x\r\n",12345);
    uint64_t negative_value= -12345;
    printk("-12345 in decimal: %d\r\n",negative_value);
    char* hello_in_german = "Guten Tag.";
    printk("Hello in Germany is %s", hello_in_german);
    while (1);
    
}