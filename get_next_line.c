#include <unistd.h>
#include <stdio.h>

// tricky thing: use BUFFER_SIZE in the buffer
char	*get_next_line(int fd)
{
	static char end_line[1000];
	int i;
	
	i = 0;
	end_line[0] = 'a';
	while (end_line[i] != '\n')
	{
		read(fd, (int *) (end_line + i), 1);
		printf("%c", end_line[i]);
		i++;
	}
	return (end_line);
}

#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int	fd;
	char	*test;
	
	fd = open("test.txt", O_RDONLY);
	printf("%d", test);
	while ((test = get_next_line(test)))
		printf("%s", test);
	
	return (0);
}
