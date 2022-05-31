#include "stdint.h"
#include "stdarg.h"
#include "uart.h"

static int read_string(char *buffer, int position, const char *string)
{

    int index = 0;

    for (index = 0; string[index] != '\0'; index++)
    {
        buffer[position++] = string[index];
    }

    return index;
};

static int read_hex(char *buffer, int position, uint64_t integer_to_print)
{

    char digits_buffer[16];
    char hex_digits[16] = "0123456789abcdef";
    int size = 0;

    do
    {

        digits_buffer[size++] = hex_digits[integer_to_print % 16];
        integer_to_print /= 16;

    } while (integer_to_print != 0);

    // the digits buffer now is in reverse order
    buffer[position++] = '0';
    buffer[position++] = 'x';

    for (int i = size - 1; i >= 0; i--)
    {
        buffer[position++] = digits_buffer[i];
    }

    // +2 because of the two more digits "0x"
    return size + 2;
};

static int read_uint(char *buffer, int position, uint64_t integer_to_print)
{
    char digits_buffer[24];
    char decimal_digits[10] = "0123456789";
    int size = 0;

    do
    {
        digits_buffer[size++] = decimal_digits[integer_to_print % 10];
        integer_to_print /= 10;

    } while (integer_to_print != 0);

    for (int i = size - 1; i >= 0; i--)
    {
        buffer[position++] = digits_buffer[i];
    }

    return size;
};

static int read_int(char *buffer, int position, int64_t integer_to_print)
{
    int size = 0;
    if (integer_to_print < 0)
    {
        integer_to_print = -integer_to_print;
        buffer[position++] = '-';
        size++;
    }
    size += read_uint(buffer, position, (uint64_t)integer_to_print);
    return size;
}

static void write_to_console(const char *buffer, int size)
{

    for (int i = 0; i < size; i++)
    {
        write_char(buffer[i]);
    }
}

// for simplicity we implement %s, %d, %x and %u specifiers
int printk(const char *format, ...)
{

    char buffer[1024];            //buffer for the characters tso be printed on the console
    int buffer_size = 0;          //buffer size, points to the current character
    int64_t integer_to_print = 0; // save value we want to print on the console.

    char *string_to_print = 0;

    // hold information about variable arguments
    va_list args;

    //Initialize a variable argument list
    va_start(args, format);

    for (int i = 0; format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buffer_size++] = format[i];
        }
        else // if it is '%'
        {
            switch (format[++i])
            {

            case 's':
                string_to_print = va_arg(args, char *); //retrieve next argument ,
                                                        //char* is the type of the variable we want to retrieve
                buffer_size += read_string(buffer, buffer_size, string_to_print);
                break;

            case 'x':
                integer_to_print = va_arg(args, int64_t); //convert it to integer

                buffer_size += read_hex(buffer, buffer_size, (uint64_t)integer_to_print);
                // When printing the hexadecimal number
                // The printf function will cast the negative value to uint64_t
                break;

            case 'u':
                integer_to_print = va_arg(args, int64_t); //convert it to integer
                buffer_size += read_uint(buffer, buffer_size, (uint64_t)integer_to_print);
                break;

            case 'd':
                integer_to_print = va_arg(args, int64_t); //convert it to integer
                buffer_size += read_int(buffer, buffer_size, integer_to_print);
                break;

            default:
                buffer[buffer_size++] = '%';
                break;
            }
        }
    }
    write_to_console(buffer, buffer_size);
    //Clean up: End using variable argument list
    va_end(args);

    return buffer_size;
}