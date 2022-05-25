#include "uart.h"



void KMain(void){

    init_uart();
    write_string("Hello, world!");
    while (1);
    
}