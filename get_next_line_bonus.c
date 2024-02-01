/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:25:16 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/02/01 18:52:18 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_stor(char **storage)
{
	free (*storage);
	*storage = NULL;
	return (NULL);
}

char	*new_storage(char *storage, char *line)
{
	char	*temp;
	int		i;
	int		j;

	j = 0;
	if (!line)
		return (NULL);
	temp = ft_calloc((ft_strlen(storage) - ft_strlen(line) + 2), sizeof(char));
	i = ft_strlen(line);
	while (storage[i])
	{
		temp[j] = storage[i];
		i++;
		j++;
	}
	free(storage);
	storage = NULL;
	temp[j] = 0;
	return (temp);
}

char	*new_line(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
		i--;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		free_stor(&storage);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*read_line(char *storage, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		n_bytes;

	n_bytes = 1;
	buffer[0] = 0;
	if (!storage)
	{
		storage = ft_calloc(1, 1);
		if (!storage)
			return (NULL);
	}
	while (n_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes < 0)
			free_stor(&storage);
		buffer[n_bytes] = 0;
		temp = ft_strjoin(storage, buffer);
		free(storage);
		if (!temp)
			return (NULL);
		storage = temp;
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[FD_SETSIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	storage[fd] = read_line(storage[fd], fd);
	if (!storage[fd])
		return (NULL);
	line = new_line(storage[fd]);
	if (!line)
	{
		free(storage[fd]);
		storage[fd] = NULL;
	}
	storage[fd] = new_storage(storage[fd], line);
	return (line);
}

/* int main ()
{
	int fd;
	fd = open("texto.txt", O_RDONLY);
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
} */