/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:25:16 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/01/31 22:41:48 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
char	*new_storage(char *storage, char *line)
{
	char	*temp;
	int		i;
	int j;
	j=0;
	
	if(!line)
		return(NULL);
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
	return(temp);
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
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i]=='\n')
		line[i] = '\n';
	return(line);
}

char	*read_line(char *storage, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		n_bytes;
	
	n_bytes = 1;
	buffer[0] = 0;
	if(!storage)
		storage = ft_calloc(1,1);
	while (n_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes < 0)
		{
			free (storage);
			storage = NULL;
			return(NULL);
		}
		buffer[n_bytes] = 0;
		temp = ft_strjoin(storage, buffer);
		free(storage);
		storage = temp;
	}
	return(storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char	*line;
	
	if(fd < 0 || BUFFER_SIZE <=0 || read(fd, 0, 0) < 0)
	{
		free(storage);
		storage = NULL;
		return(NULL);
	}
	storage = read_line(storage, fd);
	line = new_line(storage);
	if(!line)
	{
		free(storage);
		storage = NULL;
	}
	storage = new_storage(storage, line);
	return(line);
	}
/* int main ()
{
	int fd;
	fd = open("texto.txt", O_RDONLY);
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
} */