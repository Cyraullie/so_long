/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:28:32 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/01 12:39:55 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_data(char *map)
{
	int	i;
	int	x;
	int	y;
	int	n;

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
	int	e;
	int	p;
	int	c;

	e = 0;
	p = 0;
	c = 0;
	if (!check_map(map, rows, cols))
		return (print_error("Error\nThe map aren't a rectangle\n", 0));
	if (!check_wall(map, rows, cols))
		return (print_error("Error\nThe integrity of wall isn't respected\n", 0));
	check_item(map, &e, &c, &p);
	if (p != 1)
		return (print_error("Error\nToo many spawn points for the player\n", 0));
	if (e != 1)
		return (print_error("Error\nThere's too much exit available\n", 0));
	if (c < 1)
		return (print_error("Error\nThere must be at least 1 collectible\n", 0));
	return (1);
}

int	check_item(char *map, int *e, int *c, int *p)
{
	int	i;
	int	e_t;
	int	p_t;
	int	c_t;

	e_t = 0;
	p_t = 0;
	c_t = 0;
	i = 0;
	while (i != (int)ft_strlen(map))
	{
		if (map[i] == 'E')
			e_t++;
		if (map[i] == 'C')
			c_t++;
		if (map[i] == 'P')
			p_t++;
		i++;
	}
	*e = e_t;
	*c = c_t;
	*p = p_t;
	if (*e != 1 || *p != 1 || *c < 1)
		return (0);
	return (1);
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
