#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>

void	handle_nl(char *buffer, char *tail, char *head)
{
	int	head_len;
	int	tail_len;

	tail_len = ft_strlen(buffer) - (int)(ft_strchr(buffer, '\n') - buffer) - 1;
	head_len = ft_strlen(buffer) - tail_len;
	head = malloc(head_len + 1);
	if (head == NULL)
		return;
	tail = malloc(tail_len + 1);
	if (tail == NULL)
		return;
	ft_strlcpy(head, buffer, head_len);
	ft_strlcpy(tail, buffer + head_len, tail_len);
	head[head_len] = '\0';
	tail[tail_len] = '\0';
	//free(head); // do I free?
	free(tail); // do I free?
}

int	free_tail(char *tail, char *head, int *end_line)
{
	char	*store_tail;
	int		len_store_tail;

	store_tail = malloc(ft_strlen(tail) + 1);
	if (store_tail == NULL)
		return (0);
	ft_strlcpy(store_tail, tail, ft_strlen(tail));
	free(tail);
	len_store_tail = ft_strlen(store_tail);
	if (ft_strchr(store_tail, '\n') == 0)
	{
		head = malloc(BUFFER_SIZE + 1);
		if (head == NULL)
			return (0);
		ft_strlcpy(head, store_tail, len_store_tail);
		head[len_store_tail] = '\0';
	}
	else
	{
		handle_nl(store_tail, tail, head);
		return (*end_line = 1);
	}
	return (*end_line = 0);
}

int	catch_buffer(int fd, char *tail, char *head, int *end_line)
{
	int		buffer_len;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (0);
	buffer_len = read(fd, buffer, BUFFER_SIZE);
	buffer[buffer_len] = '\0';
	// handle full copy : basic no new_line in text AND same with end
	if (ft_strchr(buffer, '\n') == 0)
	{
		head = malloc(BUFFER_SIZE + 1);
		if (head == NULL)
			return (*end_line = 0);
		ft_strlcpy(head, buffer, buffer_len);
		head[buffer_len] = '\0';
	}
	// handle new_line case
	else
	{
		handle_nl(buffer, tail, head);
		free(buffer); // do I add that?
		return (*end_line = 1);
	}
	free(buffer); // do I add that?
	// return one if the function is end
	if (buffer_len < BUFFER_SIZE)
		return (*end_line = 1); //is it an int?
	return (*end_line = 0);
}

// It's possible that I need to empty the string line
char	*get_next_line(int fd)
{
	int			end_line;
	char		*line;
	char		*head;
	static char	*tail;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	// if tail is empty
	end_line = 0;
	head = NULL; // Pointer 
	line = NULL;
	if (tail != NULL)
	{
		free_tail(tail, head, &end_line);
		ft_strjoin(line, head);
		free(head);
	}
	// until end of buffer or new_line
	while (end_line != 1)
	{
		catch_buffer(fd, tail, head, &end_line);
		ft_strjoin(line, head);
		free(head);
	}
	return (line);
}

// launch the function using: cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
#include <stdio.h>
int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	return (0);
}
