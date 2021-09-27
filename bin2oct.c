/* Converts binary to hexadecimal */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BINARY_GROUP_LENGTH 3 /* groups of 3 bits, for octal conversion */

typedef struct String{
    char* data;
    int len;
} String;

String btoo(const char *s);
int bin2oct(char *in);

int main(int argc, char **argv)
{
    String s;
    int i;

    if(argc != 2) {
        printf("Converts character string from binary to octal notation\n"
                "Usage:  ./bin2oct STRING\n"
                "Example ./bin2oct 1001\n"
                "        ./bin2oct 0b1001\n"
                "        ./bin2oct 0B1001\n"
              );
        return -1;
    }

    s = btoo(argv[1]);
    printf("Binary: %s\nOctal: %s\n", argv[1], s);
    free(s.data);
    return 0;
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
    while(in_len % BINARY_GROUP_LENGTH != 0) in_len++;

    /* allocate memory and copy input bit string */
    temp = malloc(in_len * sizeof(char));
    strcpy(temp + in_len - prev_in_len, s);
    for (j = 0; j < in_len - prev_in_len; ++j)
        temp[j] = '0';

    /* allocate memory for output string*/
    out_len = in_len / BINARY_GROUP_LENGTH;
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

    power = BINARY_GROUP_LENGTH - 1;
    result = 0;
    for (i = 0; i < BINARY_GROUP_LENGTH; ++i){
        if(in[i] - '0')
            result += pow(2,power);
        --power;
    }
    return result;
}
