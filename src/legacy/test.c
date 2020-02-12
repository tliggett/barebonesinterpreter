#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char one[25];
    char two[25];
    char three[25];

    char line[] = "    testing tabs";
    char * lineptr = strtok(line, " ");
    strcpy(one, lineptr);
    lineptr = strtok(NULL, " ");
    strcpy(two, lineptr);
    printf("one: %s, two: %s", one, two);
}