#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>

// return pointer on new_string / copy from the beginning to the first nl (include)
char	*get_head(char* s)
{
	char	*str_output;
	int		len_output;

	if (s == NULL)
		return (NULL);
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

// return pointer on new_string / copy after 1st new line
char	*get_tail(char *s)
{
	char	*str_output;
	int		len_output;
	
	if (ft_strchr(s, '\n') == 0 || s == NULL)
		return (NULL);
	len_output = ft_strlen(ft_strchr(s, '\n') + 1) + 1;
	str_output = malloc(len_output);
	if (str_output == NULL)
		return (0);
	ft_strlcpy(str_output, ft_strchr(s, '\n') + 1, len_output + 1); // handle the nl
	return (str_output);
}

// if there are nothing to read return NULL
char	*get_next_line(int fd)
{
	int			buffer_len;
	char		*buffer;
	char		*line;
	static char	*tail;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer_len = BUFFER_SIZE;
	line = get_head(tail);
	tail = get_tail(tail);
	while (buffer_len == BUFFER_SIZE && ft_strchr(line, '\n') == 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (0);
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		if (buffer_len == -1)
			return (NULL);
		if (buffer_len == 0 && line != NULL)
			break ;
		buffer[buffer_len] = '\0';

		tail = get_tail(buffer);
		if (line == NULL)
			line = get_head(buffer);
		else
			line = ft_strjoin(line, get_head(buffer));
		free (buffer);
	}
	// free tail for the last occurence
	return (line);
}

// cc -Wall -Wextra -Werror -D BUFFER_SIZE=100 get_next_line.c get_next_line_utils.c -g
int	main(void)
{
	int		fd;
	char	*str;

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

	str = get_next_line(fd);
	printf("6 %s", str);
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
