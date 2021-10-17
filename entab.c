/* Replaces string of spaces with minimum number of tabs and spaces to achieve indentation */
#include <stdio.h>
#include <stdlib.h>
#define TABSTOP 4
#define MAXLINE 1000

int getline(char line[], int maxline);
int entab(char line[], int len, int tabstop);

main(int argc, char *argv[])
{
    int len, tabstop;
    char line[MAXLINE];

    tabstop = 0;
    if(argc == 2)
        tabstop = atoi(argv[1]); /* assign the tabstop */

    while((len = getline(line, MAXLINE)) > 0){
        len = entab(line, len, tabstop);
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

int entab(char line[], int len, int tabstop)
{
    int state, nspace;
    int i, j;

    if (!tabstop)
        tabstop = TABSTOP;

    nspace = 0;
    for (i = 0; i < len; ++i) {
        if (line[i] == ' ') {
            ++nspace;
            if (nspace == tabstop) {
                line[i-tabstop+1] = '\t'; /* replace space with tab */
                for (j = i-tabstop+2; j < len; ++j) /* shift left by tabstop-1 */
                    line[j] = line[j+tabstop-1];
                len -= tabstop - 1;
                i -= tabstop - 1;
                nspace = 0;
            }
        } else
            nspace = 0;
    }
}
