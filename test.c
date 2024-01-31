#include <stdio.h>
#include <stdlib.h>

void test(char **test)
{
    int i = 1;
    int j = 2;
    int k = 7;
    
    *test = malloc(3);
    (*test)[0] = 'k';
    (*test)[1] = 'o';
    (*test)[2] = '\0';

    while(i < 5)
    {
        i += j;
        printf("Hey man!");
    }
}

int main(void)
{
    char* variable;
    
    variable = NULL;
    test(&variable);
    printf("%s", variable);
    return 0;
}