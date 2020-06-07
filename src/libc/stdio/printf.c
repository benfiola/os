//
// Created by benfiola on 5/25/20.
//

#include <stdio.h>
#include <stdarg.h>

struct printf_flags {
    unsigned char leftJustify;
    unsigned char sign;
    unsigned char misc;
    unsigned char leftPad;
};


struct printf_flags parse_flags(char** format) {
    struct printf_flags flags;
    flags.leftJustify = 0;
    flags.leftPad = 0;
    flags.misc = 0;
    flags.sign = 0;

    char* current = *format;

    while(*current != '\0') {
        if (*current == '-') {
            flags.leftJustify = 1;
        } else if (*current == '+') {
            flags.sign = 1;
        } else if (*current == ' ') {
            flags.sign = -1;
        } else if (*current == '#') {
            flags.misc = 1;
        } else if (*current == '0') {
            flags.leftPad = 1;
        } else {
            break;
        }
        current = current + 1;
    }
    *format = current;
    return flags;
}

int parse_precision(char** format, va_list args) {
    /*
     * Return 1 if no .
     * Return 0 if . but no numeric characters afterwards
     * Otherwise returns unsigned precision integer.
     */
    char* current = *format;

    //Check for missing decimal
    if(*current != '.') {
        return 1;
    }

    //Check for .*
    current = current + 1;
    if(*current == '*') {
        return va_arg(args, int);
    }

    int width = 0;
    while(*current != '\0') {
        if('0' > *current || '9' < *current) {
            break;
        }
        int integer = *current - (int) '0';
        width = (width * 10) + integer;
        current = current + 1;
    }

    *format = current;
    return width;
}

int parse_width(char** format, va_list args) {
    /*
     * Returns -1 if unspecified.
     * Otherwise returns a unsigned width integer.
     */
    char* current = *format;

    if(*current == '*') {
        return va_arg(args, int);
    }

    int width = -1;

    while(*current != '\0') {
        if('0' > *current || '9' < *current) {
            break;
        }
        if(width == -1) {
            width = 0;
        }
        int integer = *current - (int) '0';
        width = (width * 10) + integer;
        current = current + 1;
    }

    *format = current;
    return width;
}

int parse_size(char** format) {
    /*
     * Returns -2 if hh
     * Returns -1 if h
     * Returns 0 if none
     * Returns 1 if l/L
     * Returns 2 if ll
     * Returns 0 if none.
     */
    char* current = *format;
    int toReturn = 0;

    if(*current == 'h') {
        current = current + 1;
        toReturn = toReturn - 1;
        if(*current == 'h') {
            current = current + 1;
            toReturn = toReturn - 1;
        }
    }
    else if(*current == 'l') {
        current = current + 1;
        toReturn = toReturn + 1;
        if(*current == 'l') {
            current = current + 1;
            toReturn = toReturn + 1;
        }
    }
    else if(*current == 'L') {
        current = current + 1;
        toReturn = toReturn + 1;
    }
    *format = current;
    return toReturn;
}


int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    unsigned int written = 0;

    /* get argument va_arg(args, <type>) */
    while(*format != '\0') {
        if(*format == '%') {
            char* current = (char *) format;
            current = current + 1;

            struct printf_flags flags = parse_flags(&current);
            int width = parse_width(&current, args);
            int precision = parse_precision(&current, args);
            int size = parse_size(&current);

            if(*current == 'c') {
                putchar(va_arg(args, int));
                written = written + 1;
            } else if(*current == 'd' || *current == 'i') {
                // signed integer
                //print decimal unsigned int
                long long value;
                value = va_arg(args, long long);
                char negative = (value < 0);

                unsigned int index = sizeof(long long) * 8;
                char buffer[index];

                if(value == 0) {
                    buffer[--index] = '0';
                }
                while(value != 0) {
                    int mod = (value % 10);
                    if(mod < 0) {
                        mod = -mod;
                    }
                    buffer[--index] = '0' + mod;
                    value = value/10;
                }

                if(negative) {
                    putchar('-');
                    written = written + 1;
                }
                for(; index < sizeof(buffer); index++) {
                    putchar(buffer[index]);
                    written = written + 1;
                }
            } else if(*current == 'e' || *current == 'E') {
                //scientific notation
                char uppercase = (*current == 'F');
                double value = va_arg(args, double);
                struct double_struct* value_struct = (struct double_struct*) &value;
                int test = 0;
            } else if(*current == 'f' || *current == 'F') {
                char uppercase = (*current == 'F');
                double value = va_arg(args, double);
                long whole = (long) value;
                double fraction = value - whole;

                // print whole number
                unsigned long index = sizeof(unsigned long) * 8;
                char buffer[index];

                if(whole == 0) {
                    buffer[--index] = '0';
                }
                while(whole != 0) {
                    buffer[--index] = '0' + (whole % 10);
                    whole = whole/10;
                }

                for(; index < sizeof(buffer); index++) {
                    putchar(buffer[index]);
                    written = written + 1;
                }

                putchar('.');
                written = written + 1;

                //print fraction
                int decimalPlace = 0;
                while(decimalPlace < precision) {
                    fraction = fraction * 10;
                    int leadingDecimal = (int) fraction % 10;
                    fraction = fraction - leadingDecimal;
                    putchar('0' + leadingDecimal);
                    written = written + 1;
                    decimalPlace = decimalPlace + 1;
                }
            }else if(*current == 'g') {
                //uses the shorter of %e or %f
            } else if(*current == 'G') {
                //uses the shorter of %E or %F
            } else if(*current == 'o') {
                //print octal unsigned int
                unsigned int value = va_arg(args, unsigned int);

                unsigned int index = sizeof(unsigned int) * 8;
                char buffer[index];

                if(value == 0) {
                    buffer[--index] = '0';
                }
                while(value != 0) {
                    int digit = (value & 0x7);
                    char c = '0' + digit;
                    buffer[--index] = c;
                    value = value/8;
                }
                if(flags.misc) {
                    buffer[--index] = '0';
                }

                for(; index < sizeof(buffer); index++) {
                    putchar(buffer[index]);
                    written = written + 1;
                }
            } else if(*current == 's') {
                //print null-terminated string
                char *str = va_arg(args, char *);
                while(*str != '\0') {
                    putchar(*str);
                    str = str + 1;
                    written = written + 1;
                }
            } else if(*current == 'u') {
                //print decimal unsigned int
                unsigned int value = va_arg(args, unsigned int);

                unsigned int index = sizeof(unsigned int) * 8;
                char buffer[index];

                if(value == 0) {
                    buffer[--index] = '0';
                }
                while(value != 0) {
                    buffer[--index] = '0' + (value % 10);
                    value = value/10;
                }

                for(; index < sizeof(buffer); index++) {
                    putchar(buffer[index]);
                    written = written + 1;
                }
            } else if(*current == 'x' || *current == 'X') {
                //print hex
                char uppercase = *current == 'X';
                unsigned int value = va_arg(args, unsigned int);

                unsigned int index = sizeof(unsigned int) * 8;
                char buffer[index];

                if(value == 0) {
                    buffer[--index] = '0';
                }
                while(value != 0) {
                    int digit = (value & 0xF);
                    char c = '0' + digit;
                    if(digit > 9) {
                        c = 'a' + (digit - 10);
                        if(uppercase) {
                            c = c - ('a' - 'A');
                        }
                    }
                    buffer[--index] = c;
                    value = value/16;
                }
                if(flags.misc) {
                    buffer[--index] = (uppercase) ? 'X' : 'x';
                    buffer[--index] = '0';
                }

                for(; index < sizeof(buffer); index++) {
                    putchar(buffer[index]);
                    written = written + 1;
                }
            } else if(*current == 'p') {
                //print pointer - implementation defined
                unsigned int value = va_arg(args, unsigned int);

                unsigned int index = sizeof(unsigned int) * 8;
                char buffer[index];

                if(value == 0) {
                    buffer[--index] = '0';
                }
                while(value != 0) {
                    int digit = (value & 0xF);
                    char c = '0' + digit;
                    if(digit > 9) {
                        c = 'a' + (digit - 10);
                    }
                    buffer[--index] = c;
                    value = value/16;
                }
                buffer[--index] = 'x';
                buffer[--index] = '0';

                for(; index < sizeof(buffer); index++) {
                    putchar(buffer[index]);
                    written = written + 1;
                }
            } else if(*current == 'n') {
                //print nothing, store characters printed into
                //provided pointer
                int* pointer = va_arg(args, int *);
                *pointer = written;
            } else if(*current == '%') {
                //print a '%' character
                putchar('%');
                written = written + 1;
            } else {
                //invalid character
                putchar('%');
                written = written + 1;
                current = (char *) format;
            }
            format = current + 1;
            continue;
        }
        putchar(*format);
        written = written + 1;
        format = format + 1;
    }

    va_end(args);

    return 0;
}

