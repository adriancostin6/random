/* Converts binary to hexadecimal */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BINARY_GROUP_LENGTH 4 /* each hex char is represented by four binary chars*/

/* length for octal prefix*/
#define OCTAL_PREFIX_NEW 2 /* refers to octal prefix of form "0o" like "0x" for hex */
#define OCTAL_PREFIX_OLD 1 /* refers to octal prefix of form "0" as in 0177 */

typedef struct String{
    char* data;
    int len;
} String;

String btoh(const char *s);
char get_hex(int in, char *c);
int bin2int(char *in);
int otoi(const char *s);
String dtob(int decimal);
void insert_binary_char(char *s, int num, int pos);
void invert_string(char s[], int len);

int main(int argc, char **argv)
{
    String s_binary, s_hexadecimal;
    int i;
    int decimal;

    if(argc != 2) {
        printf("Converts character string from octal to hexadecimal notation\n"
                "Usage:  ./oct2hex STRING\n"
                "Example ./oct2hex 1001\n"
                "        ./oct2hex 0b1001\n"
                "        ./oct2hex 0B1001\n"
              );
        return -1;
    }

    decimal = otoi(argv[1]);
    s_binary = dtob(decimal);
    invert_string(s_binary.data, s_binary.len);
    s_hexadecimal = btoh(s_binary.data);
    printf("Octal: %s\nHex: %s\n", argv[1], s_hexadecimal);
    free(s_binary.data);
    free(s_hexadecimal.data);
    return 0;
}


/* converts a string of binary digits to hexadecimal */
String btoh(const char *s)
{
    char hex_lut[] = "0123456789ABCDEF";
    int i, k, j;
    int in_len_old, in_len, out_len;
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
        in_len_old = in_len;
        while(in_len % 4 != 0) in_len++;

        /* if we need ot add leading zeros, allocate temp string and add them*/
        temp = malloc(in_len * sizeof(char));
        strcpy(temp + in_len - in_len_old, s);
        for (j = 0; j < in_len - in_len_old; ++j)
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
    str.len = i+1;

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

void invert_string(char s[], int len)
{
    int i;
    char temp;

    for(i = 0; i < len / 2; ++i) {
        temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}
