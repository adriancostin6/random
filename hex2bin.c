/* converts hex to binary */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BINARY_GROUP_LENGTH 4 /* each hex char is represented by four binary chars*/

/* struct defining a simple string */
typedef struct String{
    char* data;
    int len;
} String;

String htob(const char *s);
void make_binary(int c, char *res);
void put_binary(String destination, char *source, int *dest_index);


int main(int argc, char **argv)
{
    String s;
    int i;

    if(argc != 2) {
        printf("Converts character string from hexadecimal to binary notation\n"
                "Usage:  ./hex2bin STRING\n"
                "Example ./hex2bin 16AB\n"
                "        ./hex2bin 0x16AB\n"
                "        ./hex2bin 0X16AB\n"
              );
        return -1;
    }

    s = htob(argv[1]);
    printf("Hex: %s\nBinary: %s\n", argv[1], s);
    free(s.data);
    return 0;
}


/* converts a string of hexadecimal digits to binary*/
String htob(const char *s)
{
    int i, k;
    int output_array_len, input_array_len;
    char bits[BINARY_GROUP_LENGTH];
    String result_str;

    input_array_len = strlen(s);

    /* accounts for prefix */
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')){
        input_array_len -= 2;
        i = 2;
    } else i = 0;

    
    output_array_len = BINARY_GROUP_LENGTH * input_array_len;
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

    while(i < BINARY_GROUP_LENGTH){
        res[i] = '0';
        ++i;
    }
}

/* copy source bits into destination, updating destination index */
void put_binary(String destination, char  *source, int *dest_index)
{
    int i, j;

    for(j = BINARY_GROUP_LENGTH - 1; j >= 0; --j)
        destination.data[(*dest_index)++] = source[j];
}
