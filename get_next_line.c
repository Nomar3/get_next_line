/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:38:29 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/01/22 20:41:18 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}


char	*line_cut(char *storage)
{
	int		i;
	char	*pre_n;
	
	i = 0;
	
	while(storage[i])
	{
		pre_n[i] = storage[i];
		if(storage[i] == '\n')
			return (pre_n);
		i++;
	}
	
}

char	*ft_read(char *storage, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		n_byte;

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
		return (ft_read(storage, fd));
	}
	//si tiene salto de linea, 
	else
		return (storage);
}


char	*get_next_line(int fd)
{
	static char* storage;
	int	n;

	if (!storage)
	{
		storage = malloc(sizeof(char));
		*storage = 0;
	}
	storage = ft_read(storage, fd);
}
