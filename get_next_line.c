#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>

static char	*get_head(char* s)
{
	char	*str_output;
	int		len_output;

	if (ft_strchr(s, '\n') == 0)
		len_output = ft_strlen(s) + 1;
	else
		len_output = ft_strchr(s, '\n') - s + 2; //handle null char 6 + 1

	if (len_output == 0)
		return (0);

	str_output = malloc(len_output);
	if (str_output == NULL)
		return (0);
	ft_strlcpy(str_output, s, len_output); // handle the new line
	return (str_output);
}

char	*get_tail(char *s)
{
	char	*str_output;
	int		len_output;
	
	if (ft_strchr(s, '\n') == 0)
		return (NULL);
	len_output = ft_strlen(ft_strchr(s, '\n') + 1) + 1;
	str_output = malloc(len_output);
	if (str_output == NULL)
		return (0);
	ft_strlcpy(str_output, ft_strchr(s, '\n') + 1, len_output + 1); // handle the nl
	return (str_output);
}

// if there are a tail, is it handle?
char	*free_tail(char **tail)
{
	char	*line;
	char	*save;

	printf("Tail value: %sokok \n", *tail);
	if (ft_strchr(*tail, '\n') == 0)
	{
		line = malloc(ft_strlen(*tail) + 1);
		if (line == NULL)
			return (0);
		ft_strlcpy(line, *tail, ft_strlen(*tail) + 1);
		free (*tail);
	}
	else
	{
		line = get_head(*tail);
		save = malloc(ft_strlen(*tail) + 1);
		if (save == NULL)
			return (0);
		ft_strlcpy(save, *tail, ft_strlen(*tail) + 1);
		free (*tail);
		*tail = get_tail(save);
		free (save);
	}
	return (line);
}

// if there are nothing to read return NULL
char	*get_next_line(int fd)
{
	int			buffer_len;
	char		*buffer;
	char		*line;
	static char	*tail = NULL;

	printf("Tail value: %sokok\n", tail);
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	buffer_len = BUFFER_SIZE;
	if (tail != NULL)
		line = free_tail(&tail);
	while (buffer_len == BUFFER_SIZE && ft_strchr(line, '\n') == 0)
	{
		buffer = malloc(BUFFER_SIZE + 1); // perhaps I can remove that of the loop
		if (buffer == NULL)
			return (0);
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		if (buffer_len == 0 && line != NULL)
			return (line);
		else if (buffer_len == 0)
			return (NULL);
		buffer[buffer_len] = '\0';
		tail = get_tail(buffer);
		// create a function to handle line
		if (line == NULL)
			line = get_head(buffer);
		else
			line = ft_strjoin(line, get_head(buffer));
		free (buffer);
	}
	printf("tail value: %s\n", tail);
	return (line);
}

// cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -g
// prb: cc -Wall -Wextra -Werror -D BUFFER_SIZE=100 get_next_line.c get_next_line_utils.c -g
int	main(void)
{
	int	fd;
	char *str;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("1 %s", str);
	free(str);

	str = get_next_line(fd);
	printf("2 %s", str);
	free(str);

	str = get_next_line(fd);
	printf("3 %s", str);
	free(str);

	str = get_next_line(fd);
	printf("4 %s", str);
	free(str);

	str = get_next_line(fd);
	printf("5 %s", str);
	free(str);

	/*while (1)
	{
		str = get_next_line(fd);
		if (str)
			printf("%s", str);
		else 
			break;
		free(str);
	}*/
	return (0);
}
