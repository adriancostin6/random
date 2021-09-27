
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* length for octal prefix*/
#define OCTAL_PREFIX_NEW 2 /* refers to octal prefix of form "0o" like "0x" for hex */
#define OCTAL_PREFIX_OLD 1 /* refers to octal prefix of form "0" as in 0177 */

typedef struct String {
    char* data;
    int len;
} String;

int otoi(const char *s);
String dtob(int decimal);
void insert_binary_char(char *s, int num, int pos);


int main(int argc, char **argv)
{
    int i;
    int decimal;
    String s_bin;

    if(argc != 2) {
        printf("Converts character string from octal to binary notation\n"
                "Usage:  ./oct2bin STRING\n"
                "Example ./oct2bin 0100\n"
                "Example ./oct2bin 0o100\n"
                "Example ./oct2bin 0O100\n"
              );
        return -1;
    }

    decimal = otoi(argv[1]);
    s_bin = dtob(decimal);
    printf("Octal: %s\nBinary: ", argv[1]);
    for (i = s_bin.len; i >= 0; --i)
        putchar(s_bin.data[i]);
    putchar('\n');

    free(s_bin.data);

    return 0;
}


/* converts a string of decimal digits to binary */
String dtob(int decimal)
{
    int i;
    int copy;
    char *result;
    int remainder;
    String str;

    copy = decimal;

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

    /* convert decimal to binary by division */
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

/* inserts char in array based on value of num */
void insert_binary_char(char *s, int num, int pos)
{
    int remainder;

    remainder = num % 2;
    s[pos] = remainder + '0';
}

/* converts a string of octal digits to decimal*/
int otoi(const char *s)
{
    int i;
    int len, result, power;

    len = strlen(s);

    /* if 0o or 0O is present, or 0, update the start index */
    if (s[0] == '0' && (s[1] == 'o' || s[1] == 'O')) {
        i = 2;
        power = len - OCTAL_PREFIX_NEW - 1;
    } else if (s[0] == '0') {
        i = 1;
        power = len - OCTAL_PREFIX_OLD - 1;
    }
    else {
        i = 0;
        power = len - 1;
    }

    result = 0;
    while (i < len) {
        if(isdigit(s[i])) {
            result += (s[i] - '0') * pow(8, power);
            --power;
        }
        ++i;
    }
    return result;
}
