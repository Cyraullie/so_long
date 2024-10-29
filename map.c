/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:28:32 by cgoldens          #+#    #+#             */
/*   Updated: 2024/10/29 16:42:02 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	check_map(char **map,int rows, int cols)
{
	//TODO 1 exit
	//TODO 1 collectible
	//TODO 1 starting position
	//TODO rectangular
	//TODO surrounded by walls = {row 0 and last full 1 && col 0 and last full 1}
	int	x;
	int	y;
	int e;
	int	c;
	int p;

	e = 0;
	c = 0;
	p = 0;
	x = 0;
	y = 0;
printf("%c", map[y][x]);
	printf("%d-", rows);
	printf("%d\n", cols);
	while (x <= cols && y <= rows)
	{
		printf("%d ", x);
		if (map[y][x] == 'E')
			e++;
		if (map[y][x] == 'C')
			c++;
		if (map[y][x] == 'P')
			p++;
		if (x == cols)
		{
			if (x == cols && y == rows)
				break;
			y++;
			x = -1;
		}
		x++;
	}



	ft_putstr_fd("Error\n", 1);
	return (1);
}