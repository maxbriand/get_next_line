#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size <= 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*sdup;

	sdup = malloc(ft_strlen(s) + 1);
	if (sdup == NULL)
		return (NULL);
	ft_strlcpy(sdup, s, ft_strlen(s) + 1);
	return (sdup);
}

void    test(char* s)
{
    // s = ft_strdup("cc teddy\n");

    free (s);
    // printf("%p\n", s);
    // s = ft_strdup("cc teddy");
    s = malloc(5);
    printf("%p\n", s);
    // printf("%s\n", s);
    ft_strlcpy(s, "Hey!", 5);
}
int main(void)
{
    char* variable = malloc(1);

    printf("%p\n", variable);
    void *garbage = NULL;
    // ft_strlcpy(variable, "Hey!", 5);
    // printf("%p\n", variable);
    // printf("value: %s\n", variable);
    test(variable);
    printf("value: %s\n", variable);
    free(variable);
    return (0);
}
