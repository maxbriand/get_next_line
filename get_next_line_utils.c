#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// add the null char
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l_dst;
	int		save_ltotal;
	int		i;

	if (dst == NULL && size == 0)
		return (size + ft_strlen(src));
	l_dst = ft_strlen(dst);
	if (size <= l_dst)
		return (size + ft_strlen(src));
	save_ltotal = ft_strlen(dst) + ft_strlen(src);
	i = 0;
	while (l_dst < size - 1 && src[i])
	{
		dst[l_dst] = src[i];
		l_dst++;
		i++;
	}
	dst[l_dst] = '\0';
	return (save_ltotal);
}

// join two string
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	int		lnew_string;

	if (!s1 || !s2)
		return (NULL);
	lnew_string = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_string = malloc(lnew_string);
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_string, s2, lnew_string);
	return (new_string);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (s == NULL) // add
		return (0); // add
	i = 0;
	printf("IN STRCHR: %s", s);
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (0);
}
