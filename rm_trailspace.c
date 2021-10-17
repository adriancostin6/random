/* remove trailing whitespace */
#include <stdio.h>
#define MAXLINE 1000
#define IS_CHAR 0
#define IS_BLANK 1


int getline(char line[], int maxline);
int rm_whitespace(char line[], int len);
int is_whitespace(char c);

main()
{
    int len;
    char line[MAXLINE];

    /* get the line */
    while((len = getline(line, MAXLINE)) > 0){
        rm_whitespace(line, len);
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

/* rm_whitespace: remove trailing blanks, tabs and blank lines */
int rm_whitespace(char line[], int len)
{
    /* trim length until we get rid of all whitespace */
    while(len && is_whitespace(line[len-1]))
        --len;

    /* set newline and null*/
    if(len){ /* not blank line*/
        line[len] = '\n';
        line[len+1] = '\0';
    }
    else 
        line[len] = '\0'; /* blank line */

    line[len+1] = '\0';

    return len;
}

int is_whitespace(char c) { return c == ' ' || c == '\n' || c == '\t'; }
