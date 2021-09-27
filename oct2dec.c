/* convert octal to decimal */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* length for octal prefix*/
#define OCTAL_PREFIX_NEW 2 /* refers to octal prefix of form "0o" like "0x" for hex */
#define OCTAL_PREFIX_OLD 1 /* refers to octal prefix of form "0" as in 0177 */

int otoi(const char *s);

int main(int argc, char **argv)
{
    if(argc != 2) {
        printf("Converts character string from octal notation to decimal\n"
                "Usage:  ./oct2dec STRING\n"
                "Example ./oct2dec 177\n"
                "        ./oct2dec 0o177\n"
                "        ./oct2dec 0O177\n"
              );
        return -1;
    }
    printf("Octal: %s\nDecimal: %d\n", argv[1], otoi(argv[1]));
    return 0;
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
