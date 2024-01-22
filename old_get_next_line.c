#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>

// WARNING: LIBFT, LSEEK AND GLOBAL VARIABLE FORBIDDEN

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_cp;

	s_cp = s;
	i = 0;
	while (i < n)
	{
		*(s_cp + i) = (unsigned char) c;
		i++;
	}
	return (s);
}

void	collect_line(int fd, char* save_buff, char *line)
{
	char 	*buff;
	int	i;
	int 	checker;
	int	lenght;

	buff = malloc(BUFFER_SIZE + 1);
	checker = 0;
	while (checker == 0)
	{
		lenght = read(fd, buff, BUFFER_SIZE);
		buff[lenght] = '\0';
		if (lenght == 0)
			break;
		i = 0;
		while (buff[i] != '\n' && buff[i])
			i++;
		if (buff[i] == '\n')
		{
			ft_memset(buff + i, 0, ft_strlen(buff + i));
			checker = 1;
		}
		ft_strjoin(line, buff);
	}
	// add a return
}

char *get_next_line(int fd)
{
	static char* 	save_buff =  NULL;
	char* 		line;

	free(line);
	collect_line(fd, save_buff, line);
	return (line);
}

#include <fcntl.h>
#include <unistd.h>
int	main(void)
{
	int fd1 = open("test.txt", O_RDONLY);
	char	*test1 = get_next_line(fd1);
	char	*test2 = get_next_line(fd1);
	return (0);
}
