/* Converts binary to hexadecimal */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BINARY_GROUP_LENGTH 4 /* each hex char is represented by four binary chars*/

typedef struct String{
    char* data;
    int len;
} String;

String btoh(const char *s);
char get_hex(int in, char *c);
int bin2int(char *in);

int main(int argc, char **argv)
{
    String s;
    int i;

    if(argc != 2) {
        printf("Converts character string from hexadecimal to binary notation\n"
                "Usage:  ./bin2hex STRING\n"
                "Example ./bin2hex 1001\n"
                "        ./bin2hex 0b1001\n"
                "        ./bin2hex 0B1001\n"
              );
        return -1;
    }

    s = btoh(argv[1]);
    printf("Hex: %s\nBinary: %s\n", argv[1], s);
    free(s.data);
    return 0;
}


/* converts a string of binary digits to hexadecimal */
String btoh(const char *s)
{
    char hex_lut[] = "0123456789ABCDEF";
    int i, k, j;
    int in_len, out_len;
    int remainder;

    char *temp; /* temp char array used for input string processing */
    String result_str; /* output string */

    in_len = strlen(s);

    /* accounts for prefix */
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')){
        in_len -= 2;
        i = 2;
    } else i = 0;

    /* account for unequeal groups of bits; example 11 1111 -> 0011 1111*/
    remainder = in_len % 4; /* remainder determines the number of leading zeros we need to add*/
    if(remainder != 0){
        /* if we need ot add leading zeros, allocate temp string and add them*/
        in_len += remainder;
        temp = malloc(in_len * sizeof(char));
        strcpy(temp + remainder, s);
        for (j = 0; j < remainder; ++j)
            temp[j] = '0';
    } else {
        /* if no leading zeros, create temp string and simply copy */
        temp = malloc(in_len * sizeof(char));
        strcpy(temp, s);
    }

    /* allocate memory for output string*/
    out_len = in_len / 4;
    result_str.data = malloc(out_len * sizeof(char));

    /* iterate over input string and get hex representation for each group of 4 bits */
    k = 0;
    while (i < in_len) {
        result_str.data[k] = get_hex(bin2int(temp+i), hex_lut);
        i += 4;
        ++k;
    }

    result_str.data[out_len] = '\0'; /* add null termination character */
    result_str.len = out_len;

    free(temp);

    return result_str;
}

/* return integer value of binary string */
int bin2int(char *in)
{
    int i;
    int power;
    int result;

    power = BINARY_GROUP_LENGTH - 1;
    result = 0;
    for (i = 0; i < BINARY_GROUP_LENGTH; ++i){
        if(in[i] - '0')
            result += pow(2,power);
        --power;
    }

    return result;
}

/* return hex value for input integer */
char get_hex(int in, char *c) { return c[in]; }
