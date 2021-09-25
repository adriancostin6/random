

/**
 *  Write a function dtoo(s), which converts a string of decimal digits
 *  into it's equivalent octal value.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int dtoo(const char *s);

int main(int argc, char **argv)
{
    if(argc != 2) {
        printf("Converts character string from decimal octal notation\n"
                "Usage:  ./dec2oct STRING\n"
                "Example ./dec2oct 100\n"
              );
        return -1;
    }
    printf("Decimal: %s\nOctal: %d\n", argv[1], dtoo(argv[1]));
    return 0;
}


/* converts a string of octal digits to decimal*/
int dtoo(const char *s)
{
    int decimal;
    int result;
    int power;

    decimal = atoi(s);

    /* convert decimal to octal by division */
    power = result = 0;
    while(decimal / 8 != 0) {
        result += decimal % 8 * pow(10, power);
        decimal /= 8;
        ++power;
    }
    result += decimal % 8 * pow(10,power);
    return result;
}
