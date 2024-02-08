/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:35:26 by mbriand           #+#    #+#             */
/*   Updated: 2024/02/08 14:58:43 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_head(char *s)
{
	char	*str_output;
	int		len_output;

	if (s == NULL)
		return (NULL);
	if (ft_strchr(s, '\n') == 0)
		len_output = ft_strlen(s) + 1;
	else
		len_output = ft_strchr(s, '\n') - s + 2;
	if (len_output == 0)
		return (0);
	str_output = malloc(len_output);
	if (str_output == NULL)
		return (0);
	ft_strlcpy(str_output, s, len_output);
	return (str_output);
}

static char	*get_tail(char *s, int i)
{
	char	*str_output;
	int		len_output;

	if (ft_strchr(s, '\n') == 0 || s == NULL)
	{
		if (i == 1)
			free (s);
		return (NULL);
	}
	len_output = ft_strlen(ft_strchr(s, '\n') + 1) + 1;
	str_output = malloc(len_output);
	if (str_output == NULL)
		return (0);
	ft_strlcpy(str_output, ft_strchr(s, '\n') + 1, len_output + 1);
	if (i == 1)
		free (s);
	if (str_output[0] == 0)
	{
		free(str_output);
		str_output = NULL;
	}
	return (str_output);
}

static void	free_str(char *line, char *tail, char *buffer, int buffer_len)
{
	if (buffer_len == -1)
	{
		free (buffer);
		return ;
	}
	if (ft_strchr(line, '\n') == 0)
	{
		free (tail);
		free (buffer);
	}
}

static char	*fill_line(char *line, char *buffer, int buffer_len)
{
	buffer[buffer_len] = '\0';
	if (line == NULL)
		line = get_head(buffer);
	else
		line = ft_strjoin(line, get_head(buffer));
	return (line);
}

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
	tail = get_tail(tail, 1);
	while (tail == NULL && ft_strchr(line, '\n') == 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (0);
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		if (buffer_len == 0 || buffer_len == -1)
			break ;
		line = fill_line(line, buffer, buffer_len);
		tail = get_tail(buffer, 0);
		free (buffer);
	}
	free_str(line, tail, buffer, buffer_len);
	return (line);
}

// cc -Wall -Wextra -Werror -D BUFFER_SIZE=5 
//get_next_line.c get_next_line_utils.c -g
// if there are nothing to read return NULL

/*#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDWR);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);
 
	close(fd);
	return (0);
}*/
