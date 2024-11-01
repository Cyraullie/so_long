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

int add_floor(void *mlx, int wh, int ww, t_map map, t_img img)
{
	void	*win;

	if (!img.img_wall || !img.img_floor || !img.img_collectible || !img.img_exit || !img.img_player)
		return (1); 
	win = mlx_new_window(mlx, ww, wh, "so_long");
	if (!win)
	{
		mlx_destroy_image(mlx, img.img_wall);
		mlx_destroy_image(mlx, img.img_floor);
		mlx_destroy_image(mlx, img.img_collectible);
		mlx_destroy_image(mlx, img.img_exit);
		mlx_destroy_image(mlx, img.img_player);
		return (1);
	}
	put_img(mlx, win, img, map);

	// Détruire les images une fois l'affichage terminé
	mlx_destroy_image(mlx, img.img_wall);
	mlx_destroy_image(mlx, img.img_floor);
	mlx_destroy_image(mlx, img.img_collectible);
	mlx_destroy_image(mlx, img.img_exit);
	mlx_destroy_image(mlx, img.img_player);

	return (0);
}

void	put_img(void *mlx, void *win, t_img img, t_map map)
{
	int		x;
	int		y;
	void	*current_img;

	current_img = NULL;
	y = 0;
	x = 0;
	while (y < map.rows)
	{
		while (x < map.cols)
		{
			if (map.map[y][x] == '1')
				current_img = img.img_wall;
			else if (map.map[y][x] == '0')
				current_img = img.img_floor;
			else if (map.map[y][x] == 'C')
				current_img = img.img_collectible;
			else if (map.map[y][x] == 'E')
				current_img = img.img_exit;
			else if (map.map[y][x] == 'P')
				current_img = img.img_player;
			if (current_img)
				mlx_put_image_to_window(mlx, win, current_img, x * img.img_width, y * img.img_height);
		}
	}
}

t_img	init_img(void *mlx)
{
	t_img	data;
	int	img_width;
	int	img_height;

	data.img_wall = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
	data.img_floor = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &img_width, &img_height);
	data.img_collectible = mlx_xpm_file_to_image(mlx, "textures/collectible.xpm", &img_width, &img_height);
	data.img_exit = mlx_xpm_file_to_image(mlx, "textures/exit_close.xpm", &img_width, &img_height);
	data.img_player = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &img_width, &img_height);
	data.img_width = img_width;
	data.img_height = img_height;
	return (data);
}

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

int	main(void)
{
	t_map	map;
	void	*mlx;
	char	*buffer;
	int		i;

	mlx = mlx_init();
	if (mlx == NULL)
		return (0);
	i = 0;
	buffer = NULL;
	buffer = open_read_map("maps/map1.ber");
	printf("%s", buffer);
	if (get_map_data(buffer))
		return (0);
	get_map_size(buffer, &map.rows, &map.cols);
	map.map = convert_buffer_to_map(buffer, map.rows, map.cols);
	add_floor(mlx, map.rows * IMG_S, map.cols * IMG_S, map, init_img(mlx));
	while (i < map.rows)
		free(map.map[i++]);
	free(map.map);
	mlx_loop(mlx);
	return (0);
}
