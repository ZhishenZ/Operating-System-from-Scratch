#ifndef _PRINT_H
#define _PRINT_H

#include "stdint.h"

// printk 'k' stands for kernel. 
int printk(const char *format, ...);

// '...' in int printk(const char *format, ...); allows a variable number of arguments of unspecified type

#endif