/* converts hex to octal */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BINARY_GROUP_LENGTH_OCT 3 /* groups of 3 bits, for octal conversion */
#define BINARY_GROUP_LENGTH_HEX 4 /* each hex char is represented by four binary chars*/

/* struct defining a simple string */
typedef struct String{
    char* data;
    int len;
} String;

String htob(const char *s);
String btoo(const char *s);
void make_binary(int c, char *res);
void put_binary(String destination, char *source, int *dest_index);
int bin2oct(char *in);


int main(int argc, char **argv)
{
    String s_bin, s_oct;
    int i;

    if(argc != 2) {
        printf("Converts character string from hex to octal notation\n"
                "Usage:  ./hex2oct STRING\n"
                "Example ./hex2oct 1001\n"
                "        ./hex2oct 0b1001\n"
                "        ./hex2oct 0B1001\n"
              );
        return -1;
    }

    s_bin = htob(argv[1]); /* first convert the hex to binary */
    s_oct = btoo(s_bin.data); /* second convert the binary to octal */
    printf("Hex: %s\nOctal: %s\n", argv[1], s_oct);
    free(s_bin.data);
    free(s_oct.data);
    return 0;
}


/* converts a string of hexadecimal digits to binary*/
String htob(const char *s)
{
    int i, k;
    int output_array_len, input_array_len;
    char bits[BINARY_GROUP_LENGTH_HEX];
    String result_str;

    input_array_len = strlen(s);

    /* accounts for prefix */
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')){
        input_array_len -= 2;
        i = 2;
    } else i = 0;

    
    output_array_len = BINARY_GROUP_LENGTH_HEX * input_array_len;
    result_str.data = malloc(output_array_len * sizeof(char));

    k = 0;
    while (i < input_array_len) {
        if(isdigit(s[i])) {
            make_binary(s[i] - '0', bits);
            put_binary(result_str, bits, &k);
        } else {
            switch(s[i]) {
                case 'A':
                case 'a': 
                    make_binary(10, bits);
                    put_binary(result_str, bits, &k);
                    break;
                case 'B':
                case 'b':
                    make_binary(11, bits);
                    put_binary(result_str, bits, &k);
                    break;
                case 'C':
                case 'c':
                    make_binary(12, bits);
                    put_binary(result_str, bits, &k);
                    break;
                case 'D':
                case 'd':
                    make_binary(13, bits);
                    put_binary(result_str, bits, &k);
                    break;
                case 'E':
                case 'e':
                    make_binary(14, bits);
                    put_binary(result_str, bits, &k);
                    break;
                case 'F':
                case 'f':
                    make_binary(15, bits);
                    put_binary(result_str, bits, &k);
                    break;
            }
        }
        ++i;
    }

    result_str.data[output_array_len] = '\0'; /* add null termination character */
    result_str.len = output_array_len;

    return result_str;
}

/* make binary output string from hex character */
void make_binary(int c, char* res)
{
    int i, j;

    i = 0;
    do {
        res[i] = c % 2 + '0';
        c /= 2;
        ++i;
    } while (c != 0);

    while(i < BINARY_GROUP_LENGTH_HEX){
        res[i] = '0';
        ++i;
    }
}

/* copy source bits into destination, updating destination index */
void put_binary(String destination, char  *source, int *dest_index)
{
    int i, j;

    for(j = BINARY_GROUP_LENGTH_HEX - 1; j >= 0; --j)
        destination.data[(*dest_index)++] = source[j];
}

/* converts a string of binary digits to octal */
String btoo(const char *s)
{
    int i, k, j;
    int prev_in_len ,in_len, out_len;

    char *temp; /* temp char array used for input string processing */
    String result_str; /* output string */

    in_len = strlen(s);

    /* accounts for prefix */
    if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B')){
        in_len -= 2;
        i = 2;
    } else i = 0;


    /* set up grouping conversion algorithm by making the number of bits a multiple of 3 */
    prev_in_len = in_len;
    while(in_len % BINARY_GROUP_LENGTH_OCT != 0) in_len++;

    /* allocate memory and copy input bit string */
    temp = malloc(in_len * sizeof(char));
    strcpy(temp + in_len - prev_in_len, s);
    for (j = 0; j < in_len - prev_in_len; ++j)
        temp[j] = '0';

    /* allocate memory for output string*/
    out_len = in_len / BINARY_GROUP_LENGTH_OCT;
    result_str.data = malloc(out_len * sizeof(char));

    /* iterate over input string and get octal representation for each group of 3 bits */
    k = 0;
    while (i < in_len) {
        result_str.data[k] = bin2oct(temp+i) + '0';
        i += 3;
        ++k;
    }

    result_str.data[out_len] = '\0'; /* add null termination character */
    result_str.len = out_len;

    free(temp);

    return result_str;
}

/* return octal value from groups of binary strings of length 3 */
int bin2oct(char *in)
{
    int i;
    int power;
    int result;

    power = BINARY_GROUP_LENGTH_OCT - 1;
    result = 0;
    for (i = 0; i < BINARY_GROUP_LENGTH_OCT; ++i){
        if(in[i] - '0')
            result += pow(2,power);
        --power;
    }
    return result;
}
