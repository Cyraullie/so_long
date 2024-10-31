/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:28:32 by cgoldens          #+#    #+#             */
/*   Updated: 2024/10/31 16:39:15 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_data(char *map)
{
	int	i;
	int	x;
	int	y;
	int n;

	i = 0;
	n = 0;
	x = 0;
	y = 0;
	printf("%s", map);
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			y++;
			n++;
		}
		if (n == 0)
			x++;
		i++;
	}
	printf("\nx:%d - y:%d\n", x, y);
	handle_error_map(map, y, x);
	return (1);
}

int	handle_error_map(char *map, int rows, int cols)
{
	//TODO 1 exit
	//TODO 1 collectible
	//TODO 1 starting position
	//TODO rectangular
	//TODO surrounded by walls = {row 0 and last full 1 && col 0 and last full 1}
	//int	i;

	if (!check_map(map, rows, cols))
		return (print_error("Error\nThe map aren't a rectangle\n", 0));
	if (!check_wall(map, rows, cols))
		return (print_error("Error\nThe integrity of the wall is not respected\n", 0));
	/*i = check_item(map, rows, cols);
	if (i == 1)
	{
		ft_printf("Error\nThere's too much exit available or too many appearance points for the player\n");
		return (0);
	}
	else if (i == 2)
	{
		ft_printf("Error\nThere must be at least 1 collectible\n");
		return (0);
	}*/

	return (1);
}

int	check_item(char **map, int rows, int cols)
{
	int	x;
	int	y;
	int	e;
	int	c;

	x = -1;
	y = 0;
	e = 0;
	c = 0;
	while (x++ != cols && y != rows)
	{
		if (map[y][x] == 'E' || map[y][x] == 'P')
			e++;
		if (map[y][x] == 'C')
			c++;
		if (x == cols - 1)
		{
			y++;
			x = -1;
		}
	}
	if (e > 1 || e < 1)
		return (1);
	if (c < 1)
		return (2);
	return (0);
}

int	check_wall(char *map, int rows, int cols)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = 0;
	y = 0;
	while (i != (int)ft_strlen(map))
	{
		if ((((y == 0 || y == rows) && x < cols) && map[i] != '1')
			|| ((x == 0 || x == cols - 1) && map[i] != '1'))
			return (0);
		if (map[i] == '\n')
		{
			x = 0;
			y++;
		}
		else
			x++;
		i++;
	}
	return (1);
}

int	check_map(char *map, int rows, int cols)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	x = 0;
	while (i != (int)ft_strlen(map))
	{	
		if (map[i] == '\n')
		{
			if (x != cols)
				return (0);
			x = 0;
			y++;
		}
		else
			x++;
		i++;
	}
	if (y != rows || x != cols)
		return (0);
	return (1);
}
