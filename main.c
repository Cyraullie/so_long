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
int add_floor(void *mlx, int wh, int ww, char **map, int rows, int cols)
{
	void *win;
	void *img_wall, *img_floor, *img_collectible, *img_exit, *img_player;
	int img_width, img_height;

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
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			void *current_img = NULL;
			// Choisir l'image à afficher en fonction du caractère dans la carte
			if (map[y][x] == '1')
				current_img = img_wall;
			else if (map[y][x] == '0')
				current_img = img_floor;
			else if (map[y][x] == 'C')
				current_img = img_collectible;
			else if (map[y][x] == 'E')
				current_img = img_exit;
			else if (map[y][x] == 'P')
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

char **convert_buffer_to_map(char *buffer, int *rows, int *cols)
{
	int row_count = 0;
	int col_count = 0;
	int i = 0;

	// Compter les lignes et colonnes
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			row_count++;
		else if (row_count == 0)
			col_count++;
		i++;
	}

	*rows = row_count;
	*cols = col_count;

	// Allouer la carte en 2D
	char **map = malloc(sizeof(char *) * row_count);
	for (int j = 0; j < row_count; j++)
		map[j] = malloc(sizeof(char) * (col_count + 1));

	// Copier le contenu du buffer dans le tableau 2D
	int row = 0, col = 0;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			map[row][col] = '\0'; // Fin de ligne
			row++;
			col = 0;
		}
		else
		{
			map[row][col] = buffer[i];
			col++;
		}
		i++;
	}

	return map;
}

int	main(void)
{
	//void    *mlx;
	int		fd;
	char	*buffer;
	int y;
	int i;
    int rows, cols;
    char **map;

	/*mlx = mlx_init();
	if (mlx == NULL)
		return (1);*/
	buffer = NULL;
	fd = open("maps/map1.ber", O_RDONLY);
	if (fd < 0)
		return (1);
	y = 0;
	i = 0;
	buffer = read_map(fd, buffer);
	close(fd);
    if (!buffer)
        return (1);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			y++;
		i++;
	}
	i--;
	map = convert_buffer_to_map(buffer, &rows, &cols);
    free(buffer);
	check_map(map, rows, cols);

	//add_floor(mlx, y * IMG_S, (i / y) * IMG_S, map, rows, cols);

	for (int i = 0; i < rows; i++)
		free(map[i]);
	free(map);
	//mlx_loop(mlx);
}