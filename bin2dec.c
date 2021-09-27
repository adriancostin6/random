/* Converts binary to decimal */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* length for hexa prefix*/
#define BIN_PREFIX 2 

int btoi(const char *s);

int main(int argc, char **argv)
{
    if(argc != 2) {
        printf("Converts character string from binary notation to decimal\n"
                "Usage:  ./bin2dec STRING\n"
                "Example ./bin2dec 0011\n"
                "        ./bin2dec 0b0011\n"
                "        ./bin2dec 0B0011\n"
              );
        return -1;
    }
    printf("Binary: %s\nDecimal: %d\n", argv[1], btoi(argv[1]));
    return 0;
}


/* converts a string of hexadecimal digits to */
int btoi(const char *s)
{
    int i;
    int len, result, power;

    len = strlen(s);

    /* if 0X or 0x is present, update the start index */
    if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B')) {
        i = 2;
        power = len - BIN_PREFIX - 1;
    }
    else {
        i = 0;
        power = len - 1;
    }

    /* calculate decimal value for binary string */
    result = 0;
    while (i < len) {
        if(isdigit(s[i])) {
            result += (s[i] - '0') * pow(2, power);
            --power;
        }
        ++i;
    }
    return result;
}
