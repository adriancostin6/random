/* inverts input string */
#include <stdio.h>
#include <string.h>

void invert_string(char s[], int len);

int main(int argc, char *argv[]) 
{
    int len;
    if(argc != 2){
        printf("Inverts the input string."
               "Usage: ./invert_string STRING"
               );
        return -1;
    }


    printf("original string: %s\n", argv[1]);

    len = strlen(argv[1]);
    invert_string(argv[1], len);

    printf("inverse string: %s\n", argv[1]);
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
