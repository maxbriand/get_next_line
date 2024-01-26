#include <stdio.h>
#include <stdlib.h>


void test(char **test)
{
    *test = malloc(3);
    (*test)[0] = 'k';
    (*test)[1] = 'o';
    (*test)[2] = '\0';
}

int main(void)
{
    char* variable;
    
    variable = NULL;
    test(&variable);
    printf("%s", variable);
    return 0;
}