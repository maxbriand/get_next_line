#include <fcntl.h>
#include <unistd.h>
#include <get_next_line.h>

//I have to free the static store var using a specific function

int	free_tail(char *tail, char *head)
{


}

void	handle_nl(char *buffer, char *tail, char *head)
{
	int	head_len;
	int tail_len;

	tail_len = ft_strlen(head) - (int) (ft_strchr(head, '\n') - head);
	head_len = ft_strlen(head) - tail_len;
	head = malloc(head_len + 1);
	tail = malloc(tail_len + 1);
	ft_strlcpy(head, buffer, head_len);
	ft_strlcpy(tail, buffer, tail_len);
	head[head_len + 1] = '\0';
	tail[head_len + tail_len + 1] = '\0';
}

int	catch_buffer(int fd, char *tail, char *head)
{
	int		end_tester;
	int		buffer_len;
	char	*buffer;
	
	// LAUNCH THE CONDITION / THE FUNCTION USING THE TAIL


	buffer = malloc(BUFFER_SIZE + 1);
	end_tester = read(fd, buffer, BUFFER_SIZE);
	buffer_len = ft_strlen(buffer);

	// handle full copy : basic no new_line in text AND same with end
	if (ft_strchr(buffer, '\n') == 0)
	{
		head = malloc(BUFFER_SIZE + 1);
		ft_strlcpy(head, buffer, buffer_len);
		head[buffer_len + 1] = '\0';
	}
	// handle new_line case
	else
	{
		handle_nl(buffer, tail, head);
		return (1);
	}
	// return one if the function is end
	if (buffer_len < BUFFER_SIZE)
		return (1);
	return (0);
}

// It's possible that I need to empty the string line
char	*get_next_line(int fd)
{
	int			end;
	char		*line;
	char		*head;
	static char	*tail;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	// if tail is empty
	end = 0;
	if (tail != NULL)
	{
		end = free_tail(tail);
		ft_strjoin(line, head);
		free(head);
	}
	// until end of buffer or new_line
	while (end != 1)
	{
		end = catch_buffer(fd, tail, head);
		ft_strjoin(line, head);
		free(head);
	}
	//free the buffer everytime
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
