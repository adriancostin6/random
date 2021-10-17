/* Replaces tabs in input with appropriate number of spaces */
#include <stdio.h>
#include <stdlib.h>
#define TABSTOP 4
#define MAXLINE 1000

int getline(char line[], int maxline);
int detab(char s[], int len, int tabstop);

main(int argc, char *argv[])
{
    int len, tabstop;
    char line[MAXLINE];

    tabstop = 0;
    if(argc == 2)
        tabstop = atoi(argv[1]); /* assign the tabstop */

    while((len = getline(line, MAXLINE)) > 0){
        len = detab(line, len, tabstop);
        if(!len)
            printf("Detab failed: len exceeds MAXLINE\n");
        else 
            printf("%s", line);

    }

    return 0;
}

/* getline: read a line, return length */
int getline(char line[], int maxline)
{
    int c; /* character returned by getchar */
    int i; /* array index*/

    /* fill line until we reach maxline-1 length, EOF or newline */
    for(i = 0; i < maxline-1 && (c=getchar()) != EOF && c != '\n'; ++i) 
        line[i] = c;

    /* add newline character and null termination character */
    if(c == '\n'){
        line[i] = c;
        ++i;
    }
    line[i] = '\0';

    return i;
}

/* detab: turns tabs into spaces
 * returns len of new array on success, 0 on fail */
int detab(char s[], int len, int tabstop)
{
    int newlen;
    int i, j;

    if(!tabstop)
        tabstop = TABSTOP;

    for (i = 0; i < len; ++i) {
        if(s[i] == '\t') {
            len += tabstop - 1; /* update len to account for tabstop */

            /* return 0 on fail*/
            if(len > MAXLINE)
                return 0;

            /* shift char array to the right, by "tabstop" */
            for(j = len-1; j >= i+tabstop; --j)
                s[j] = s[j-tabstop+1];
            s[len] = '\0';

            /* replace tab with spaces */
            for(j = i; j < i+tabstop; ++j)
                s[j] = ' ';
        }
    }
    return len;
}
