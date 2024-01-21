/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:38:29 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/01/21 22:58:36 by rmarin-j         ###   ########.fr       */
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*paco(char **storage)
{
	
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
	//si el storage no tiene salto de linea
	if (new_line(storage) == -1)
		return (ft_read(storage, fd));
	//si tiene salto de linea
	else
		return (paco ());
	//si ha llegado y el storage no esta vacio
	if (n_byte == 0 && storage[0] != 0)
		return (storage);
	//cuando lee porque no hay salto de linea, le añade bytes al storage
	temp = ft_strjoin(storage, buffer);
	free(storage);
	return (temp);
}


char	*get_next_line(int fd)
{
	static char* storage;
	int	n;

	if (!storage)
	{
		storage = malloc(sizeof(char));
		storage = 0;
	}
	storage = ft_read(storage, fd);
}
