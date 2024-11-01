/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:31:34 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/01 16:13:03 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	if (!buf)
		buf = ft_calloc(1, sizeof(char));
	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*read_map(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			if (res)
				free(res);
			return (NULL);
		}
		buffer[byte_read] = 0;
		res = ft_free(res, buffer);
		if (ft_strchr(buffer, '\0'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*open_read_map(char *file)
{
	char	*buffer;
	int		fd;

	fd = open(file, O_RDONLY);
	printf("%d", fd);
	if (fd < 0)
		return (NULL);
	buffer = NULL;
	buffer = read_map(fd, buffer);
	close(fd);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
