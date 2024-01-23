#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

void	handle_nl(char *buffer, char *tail, char *head)
{
	int	head_len;
	int	tail_len;

	tail_len = ft_strlen(buffer) - (int)(ft_strchr(buffer, '\n') - buffer);
	head_len = ft_strlen(buffer) - tail_len;
	head = malloc(head_len + 1);
	if (head == NULL)
		return;
	tail = malloc(tail_len + 1);
	if (tail == NULL)
		return;
	ft_strlcpy(head, buffer, head_len);
	ft_strlcpy(tail, buffer, tail_len);
	head[head_len + 1] = '\0';
	tail[head_len + tail_len + 1] = '\0';
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
	int		end_tester;
	int		buffer_len;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (0);
	end_tester = read(fd, buffer, BUFFER_SIZE);
	buffer_len = ft_strlen(buffer);
	// handle full copy : basic no new_line in text AND same with end
	if (ft_strchr(buffer, '\n') == 0)
	{
		head = malloc(BUFFER_SIZE + 1);
		if (head == NULL)
			return (*end_line = 0);
		ft_strlcpy(head, buffer, buffer_len);
		head[buffer_len + 1] = '\0';
	}
	// handle new_line case
	else
	{
		handle_nl(buffer, tail, head);
		return (*end_line = 1);
	}
	// return one if the function is end
	if (end_tester < BUFFER_SIZE)
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
	if (tail != NULL)
	{
		head = NULL; // is it possible to handle this error using another method?
		line = NULL; // is it possible to handle this error using another method?
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

// launch the function using: cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}
