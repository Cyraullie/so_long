/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:44:32 by cgoldens          #+#    #+#             */
/*   Updated: 2024/10/28 14:44:35 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_map_size(char *buffer, int *rows, int *cols)
{
	int	x;
	int	y;
	int	i;
	int	n;

	x = 0;
	y = 1;
	i = 0;
	n = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			y++;
			n++;
		}
		if (n == 0)
			x++;
		i++;
	}
	*rows = y;
	*cols = x;
}

char	**convert_buffer_to_map(char *buffer, int rows, int cols)
{
	int		row;
	int		col;
	int		i;
	char	**map;
	int		j;

	j = 0;
	i = 0;
	col = 0;
	row = 0;
	map = malloc(sizeof(char *) * rows);
	while (j < rows)
		map[j++] = malloc(sizeof(char) * (cols + 1));
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			map[row++][col] = '\0';
			col = 0;
		}
		else
			map[row][col++] = buffer[i];
		i++;
	}
	return (map);
}

int	init(void *mlx, char *file)
{
	t_map	map;
	char	*buffer;
	int		i;

	i = 0;
	buffer = NULL;
	buffer = open_read_map(file);
	if (get_map_data(buffer))
		return (1);
	get_map_size(buffer, &map.rows, &map.cols);
	map.map = convert_buffer_to_map(buffer, map.rows, map.cols);
	add_floor(mlx, map.rows * IMG_S, map.cols * IMG_S, map);
	while (i < map.rows)
		free(map.map[i++]);
	free(map.map);
	return (0);
}

int	main(int argc, char **argv)
{
	void	*mlx;

	if (argc != 2)
		return (print_error("Error\nMissing map file\n", 1));
	mlx = mlx_init();
	if (mlx == NULL)
		return (0);
	init(mlx, argv[1]);
	mlx_loop(mlx);
	return (0);
}
