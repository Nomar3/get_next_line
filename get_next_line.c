/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:38:29 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/01/25 22:26:41 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0'){
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}


char	*line_cut(char *storage)
{
	int		i;
	char	*pre_n;
	
	i = 0;
	while(storage[i] && storage[i]!='\n')
		i++;
	pre_n = malloc(i+1);
	i = 0;
	while(storage[i])
	{
		pre_n[i] = storage[i];
		if(storage[i] == '\n')
			return (pre_n);
		i++;
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char* storage;
		char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		n_byte;

	if (!storage)
	{
		storage = malloc(1);
		*storage = 0;
	} 
	n_byte = read(fd, buffer, BUFFER_SIZE);
	buffer[n_byte] = 0;
	//si falla read o (ha llegado al final y el storage esta vacio)
	if ((n_byte < 0) || (n_byte == 0 && storage[0] == 0))
	{
		free(storage);
		storage = 0;
		return (NULL);
	}
	//si ha llegado al final y el storage no esta vacio
	if (n_byte == 0 && storage[0] != 0)
		return (storage);
	//si el storage no tiene salto de linea, 
	if (new_line(storage) == -1)
	{
		temp = ft_strjoin(storage, buffer);
		free(storage);
		storage = temp;
		return (get_next_line(fd));
	}
	//si tiene salto de linea, 
	else
	{
		storage = line_cut(buffer);
		return (storage);
	}
}
int main()
{
	int fd;
	
	fd = open("texto.txt", O_RDONLY);
	printf("%s\n\n", get_next_line(fd));
/* 	printf("%s\n\n", get_next_line(fd));
	printf("%s\n\n", get_next_line(fd));
	printf("%s\n\n", get_next_line(fd)); */
}