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

int	init(t_var *var, char *file)
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
	count_items(buffer, &map.nb_item);
	map.map = convert_buffer_to_map(buffer, map.rows, map.cols);
	var->map = map;
	var->map.map = convert_buffer_to_map(buffer, map.rows, map.cols);
	add_floor(var, map.rows * IMG_S, map.cols * IMG_S);
	while (i < map.rows)
		free(map.map[i++]);
	free(map.map);
	return (0);
}

int	handle_key(int keycode, t_var *var)
{
	int	new_x;
	int	new_y;

	new_x = var->player_x;
	new_y = var->player_y;
	if (keycode == ESC)
		exit(0);
	else if (keycode == W || keycode == AA)
		new_y -= IMG_S;
	else if (keycode == A || keycode == AL)
		new_x -= IMG_S;
	else if (keycode == S || keycode == AD)
		new_y += IMG_S;
	else if (keycode == D || keycode == AR)
		new_x += IMG_S;
	move_player(var, new_x, new_y);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;

	ft_bzero(&var, sizeof(var));
	if (argc != 2)
		return (print_error("Error\nMissing map file\n", 1));
	var.mlx = mlx_init();
	if (var.mlx == NULL)
		return (0);
	if (init(&var, argv[1]) || !is_map_solvable(&var))
		return (print_error("Error\nThe map is not solvable\n", 1));
	var.nb_move = 0;
	var.nb_coin = 0;
	ft_printf("number of movement : %d\n", var.nb_move);
	mlx_hook(var.win, 2, 1L << 0, handle_key, &var);
	mlx_loop(var.mlx);
	return (0);
}
