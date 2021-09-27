/* converts dec to hex */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct String {
    char* data;
    int len;
} String;

typedef enum {
    HEX_A=65,
    HEX_B,
    HEX_C,
    HEX_D,
    HEX_E,
    HEX_F
} ascii_hex_notation;

String dtoh(const char *s);
ascii_hex_notation get_ascii_hex(int n);
void insert_hex_char(char *s, int num, int pos);

int main(int argc, char **argv)
{
    int i;
    String s;

    if(argc != 2) {
        printf("Converts character string from decimal to hex notation\n"
                "Usage:  ./dec2hex STRING\n"
                "Example ./dec2hex 100\n"
              );
        return -1;
    }

    s = dtoh(argv[1]);
    printf("Decimal: %s\nHex: ", argv[1]);
    for (i = s.len; i >= 0; --i)
        putchar(s.data[i]);
    putchar('\n');

    free(s.data);

    return 0;
}


/* converts a string of decimal digits to hex */
String dtoh(const char *s)
{
    int i;
    int decimal, copy;
    char *result;
    int remainder;
    String str;

    decimal = copy = atoi(s);

    /* count number of divisions */
    i = 0;
    while (copy / 16 != 0) {
        ++i;
        copy /= 16;
    }
    ++i; /* null termination character */

    /* allocate memory for result array */
    result = malloc(i * sizeof(char));
    result[i] = '\0'; /* add null termination character */

    /* convert decimal to hex by division */
    i = 0;
    while(decimal / 16 != 0) { 
        insert_hex_char(result, decimal, i);
        decimal /= 16;
        ++i;
    }
    insert_hex_char(result, decimal, i);

    str.data = result;
    str.len = i;

    return str;
}

/* gets ascii value for the hex number */
ascii_hex_notation get_ascii_hex(int n)
{
    switch(n){
        case 10:
            return HEX_A;
        case 11:
            return HEX_B;
        case 12:
            return HEX_C;
        case 13:
            return HEX_D;
        case 14:
            return HEX_E;
        case 15:
            return HEX_F;
    }
}

/* inserts char in array based on value of hex num */
void insert_hex_char(char *s, int num, int pos)
{
    int remainder;

    remainder = num % 16;
    if (remainder < 10)
        s[pos] = remainder + '0';
    else
        s[pos] = get_ascii_hex(remainder);
}
