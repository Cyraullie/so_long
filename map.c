/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:28:32 by cgoldens          #+#    #+#             */
/*   Updated: 2024/10/30 13:28:58 by cgoldens         ###   ########.fr       */
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

int	check_map(char **map, int rows, int cols)
{
	//TODO 1 exit
	//TODO 1 collectible
	//TODO 1 starting position
	//TODO rectangular
	//TODO surrounded by walls = {row 0 and last full 1 && col 0 and last full 1}


	if (!check_wall(map, rows, cols))
	{
		ft_printf("Error\nThe integrity of the wall is not respected\n");
		return (0);
	}
	else if (!check_item(map, rows, cols))
		return (0);

	//printf("%d-", rows);
	//printf("%d\n", cols);

	/*printf("\ne=%d", check[0]);
	printf("c=%d", check[1]);
	printf("p=%d", check[2]);



	ft_putstr_fd("Error\n", 1);*/
	return (1);
}

int	check_item(char **map, int rows, int cols)
{
	int	x;
	int	y;
	int	check[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		check[i] = 0;
		i++;
	}
	x = 0;
	y = 0;
	while (x != cols && y != rows)
	{
		if (map[y][x] == 'E')
			check[0]++;
		if (map[y][x] == 'C')
			check[1]++;
		if (map[y][x] == 'P')
			check[2]++;
		if (x == cols - 1)
		{
			y++;
			x = -1;
		}
		x++;
	}
	if (check[0] > 1 || check[0] < 1)
	{
		ft_printf("Error\nThere's too much exit available\n");
		return (0);
	}
	if (check[1] < 1)
	{
		ft_printf("Error\nThere must be at least 1 collectible\n");
		return (0);
	}
	if (check[2] > 1 || check[2] < 1)
	{
		ft_printf("Error\nToo many appearance points for the player\n");
		return (0);
	}
	return (1);
}

int	check_wall(char **map, int rows, int cols)
{
	int	x;
	int	y;
	int	er;

	x = 0;
	y = 0;
	er = 0;
	while (x != cols)
	{
		if (map[0][x] != '1' || map[rows - 1][x] != '1')
			er++;
		x++;
	}
	while (y != rows)
	{
		if (map[y][0] != '1' || map[y][cols - 1] != '1')
			er++;
		y++;
	}
	if (er > 0)
		return (0);
	return (1);
}
