
/**
 *  Write a function dtob(s), which converts a string of decimal digits
 *  into it's equivalent binary value.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct String {
    char* data;
    int len;
} String;

String dtob(const char *s);
void insert_binary_char(char *s, int num, int pos);

int main(int argc, char **argv)
{
    int i;
    String s;

    if(argc != 2) {
        printf("Converts character string from decimal to binary notation\n"
                "Usage:  ./dec2bin STRING\n"
                "Example ./dec2bin 100\n"
              );
        return -1;
    }

    s = dtob(argv[1]);
    printf("Decimal: %s\nBinary: ", argv[1]);
    for (i = s.len; i >= 0; --i)
        putchar(s.data[i]);
    putchar('\n');

    free(s.data);

    return 0;
}


/* converts a string of octal digits to decimal; returns a String*/
String dtob(const char *s)
{
    int i;
    int decimal, copy;
    char *result;
    int remainder;
    String str;

    decimal = copy = atoi(s);

    /* count number of divisions */
    i = 0;
    while (copy / 2 != 0) {
        ++i;
        copy /= 2;
    }
    ++i; /* null termination character */

    /* allocate memory for result array */
    result = malloc(i * sizeof(char));
    result[i] = '\0'; /* add null termination character */

    /* convert decimal to hex by division */
    i = 0;
    while(decimal / 2 != 0) { 
        insert_binary_char(result, decimal, i);
        decimal /= 2;
        ++i;
    }
    insert_binary_char(result, decimal, i);

    str.data = result;
    str.len = i;

    return str;
}
/* inserts char in array based on value of hex num */
void insert_binary_char(char *s, int num, int pos)
{
    int remainder;

    remainder = num % 2;
    s[pos] = remainder + '0';
}
