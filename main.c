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

int add_floor(void *mlx, int wh, int ww, t_map map)
{
	void	*win;
	void	*img_wall, *img_floor, *img_collectible, *img_exit, *img_player;
	int	img_width, img_height;

	// Charger les images correspondant à chaque type d'élément
	img_wall = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
	img_floor = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &img_width, &img_height);
	img_collectible = mlx_xpm_file_to_image(mlx, "textures/collectible.xpm", &img_width, &img_height);
	img_exit = mlx_xpm_file_to_image(mlx, "textures/exit_close.xpm", &img_width, &img_height);
	img_player = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &img_width, &img_height);

	if (!img_wall || !img_floor || !img_collectible || !img_exit || !img_player)
		return (1); // Vérifier que toutes les images sont chargées

	// Créer la fenêtre pour afficher la carte
	win = mlx_new_window(mlx, ww, wh, "Map Viewer");
	if (!win)
	{
		// Détruire les images si la fenêtre ne peut pas être créée
		mlx_destroy_image(mlx, img_wall);
		mlx_destroy_image(mlx, img_floor);
		mlx_destroy_image(mlx, img_collectible);
		mlx_destroy_image(mlx, img_exit);
		mlx_destroy_image(mlx, img_player);
		return (1);
	}

	// Afficher chaque élément de la carte en fonction de son type
	for (int y = 0; y < map.rows; y++)
	{
		for (int x = 0; x < map.cols; x++)
		{
			void *current_img = NULL;
			// Choisir l'image à afficher en fonction du caractère dans la carte
			if (map.map[y][x] == '1')
				current_img = img_wall;
			else if (map.map[y][x] == '0')
				current_img = img_floor;
			else if (map.map[y][x] == 'C')
				current_img = img_collectible;
			else if (map.map[y][x] == 'E')
				current_img = img_exit;
			else if (map.map[y][x] == 'P')
				current_img = img_player;

			if (current_img)
				mlx_put_image_to_window(mlx, win, current_img, x * img_width, y * img_height);
		}
	}

	// Détruire les images une fois l'affichage terminé
	mlx_destroy_image(mlx, img_wall);
	mlx_destroy_image(mlx, img_floor);
	mlx_destroy_image(mlx, img_collectible);
	mlx_destroy_image(mlx, img_exit);
	mlx_destroy_image(mlx, img_player);

	return (0);
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
	add_floor(mlx, map.rows * IMG_S, map.cols * IMG_S, map);
	while (i < map.rows)
		free(map.map[i++]);
	free(map.map);
	mlx_loop(mlx);
	return (0);
}
