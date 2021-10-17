/* folds long input lines into two or more smaller lines */
#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define MAXCHAR 1000
#define FOLD 80

int getline(char line[], int maxline);
void fold_line(char line[], int len, int fold);

main(int argc, char *argv[])
{
    int len, fold;
    char line[MAXLINE];

    fold = 0;
    if(argc == 2)
        fold = atoi(argv[1]); /* assign the column count for folding */


    while((len = getline(line, MAXLINE)) > 0) {
        fold_line(line, len, fold);
    }

    return 0;
}

/* getline: read a line, return length */
int getline(char line[], int maxline)
{
    int c; /* character returned by getchar */
    int i; /* array index*/

    /* fill line until we reach maxline-1 length, EOF or newline */
    for (i = 0; i < maxline-1 && (c=getchar()) != EOF && c != '\n'; ++i) 
        line[i] = c;

    /* add newline character and null termination character */
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';

    return i;
}

void fold_line(char line[], int len, int fold)
{
    int i;

    if (!fold)
        fold = FOLD;

    for (i = 0; i < len; ++i) {
        if (i && i % fold == 0) {
            putchar('\n');
            putchar(line[i]);
        } else
            putchar(line[i]);
    }
}
