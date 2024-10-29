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

	void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
	{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	}

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
	void    *mlx;
	int		fd;
	char	*buffer;
	int y;
	int i;
    int rows, cols;
    char **map;

	mlx = mlx_init();
	if (mlx == NULL)
		return (1);
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
	map = convert_buffer_to_map(buffer, &rows, &cols);
    free(buffer);
	i--;

	add_floor(mlx, y * IMG_S, (i / y) * IMG_S, map, rows, cols);

	for (int i = 0; i < rows; i++)
		free(map[i]);
	free(map);
	mlx_loop(mlx);

	/*
	void *mlx;
	void *win;
	void *img;
	void *scaled_img;
	int img_width, img_height;
	int new_width, new_height;
	int win_width = 800;  // Largeur de la fenêtre
	int win_height = 600; // Hauteur de la fenêtre
	int *data, *scaled_data;
	int bpp, size_line, endian;
	int scaled_bpp, scaled_size_line, scaled_endian;

	// Initialisation de MiniLibX
	mlx = mlx_init();
	if (mlx == NULL)
		return (1);

	// Chargement de l'image originale en .xpm
	img = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &img_width, &img_height);
	if (img == NULL)
		return (1);

	// Dimensions de l'image agrandie
	new_width = img_width * SCALE_FACTOR;
	new_height = img_height * SCALE_FACTOR;

	// Création de l'image agrandie
	scaled_img = mlx_new_image(mlx, new_width, new_height);
	if (scaled_img == NULL)
	{
		mlx_destroy_image(mlx, img);
		return (1);
	}

	// Récupération des données de l'image originale et de l'image agrandie
	data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	scaled_data = (int *)mlx_get_data_addr(scaled_img, &scaled_bpp, &scaled_size_line, &scaled_endian);

	// Redimensionnement de l'image
	for (int y = 0; y < img_height; y++)
	{
		for (int x = 0; x < img_width; x++)
		{
			int color = data[y * (size_line / 4) + x];

			// Remplit chaque pixel agrandi dans la nouvelle image
			for (int dy = 0; dy < SCALE_FACTOR; dy++)
			{
				for (int dx = 0; dx < SCALE_FACTOR; dx++)
				{
					int scaled_x = x * SCALE_FACTOR + dx;
					int scaled_y = y * SCALE_FACTOR + dy;
					scaled_data[scaled_y * (scaled_size_line / 4) + scaled_x] = color;
				}
			}
		}
	}

	// Création de la fenêtre pour afficher l'image répétée
	win = mlx_new_window(mlx, win_width, win_height, "Image en background");
	if (win == NULL)
	{
		mlx_destroy_image(mlx, img);
		mlx_destroy_image(mlx, scaled_img);
		return (1);
	}

	// Répétition de l'image agrandie pour remplir la fenêtre
	for (int y = 0; y < win_height; y += new_height)
	{
		for (int x = 0; x < win_width; x += new_width)
		{
			mlx_put_image_to_window(mlx, win, scaled_img, x, y);
		}
	}

	// Boucle principale pour garder la fenêtre ouverte
	mlx_loop(mlx);

	// Libération des ressources
	mlx_destroy_image(mlx, img);
	mlx_destroy_image(mlx, scaled_img);
	mlx_destroy_window(mlx, win);
	return (0);
	*/
	/*
	void *img;
	int img_width, img_height;
	int win_width = 800; // Largeur de la fenêtre
	int win_height = 600; // Hauteur de la fenêtre
	int x, y;

	// Initialisation de MiniLibX

	// Création de la fenêtre
	win = mlx_new_window(mlx, win_width, win_height, "Image repetee");
	if (win == NULL)
		return (1);

	// Chargement de l'image
	img = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &img_width, &img_height);
	if (img == NULL)
	{
		mlx_destroy_window(mlx, win);
		return (1);
	}

	// Boucle pour répéter l'image sur toute la surface de la fenêtre
	for (y = 0; y < win_height; y += img_height)
	{
		for (x = 0; x < win_width; x += img_width)
		{
			mlx_put_image_to_window(mlx, win, img, x, y);
		}
	}

	// Boucle principale de MiniLibX pour garder la fenêtre ouverte
	mlx_loop(mlx);

	// Libération des ressources (facultatif dans ce cas, car mlx_loop est bloquant)
	mlx_destroy_image(mlx, img);
	mlx_destroy_window(mlx, win);
	return (0);
	*/

	/*
	void *mlx;
	void *win;
	void *img;
	void *scaled_img;
	int img_width, img_height;
	int new_width, new_height;
	int *data, *scaled_data;
	int bpp, size_line, endian;
	int scaled_bpp, scaled_size_line, scaled_endian;

	// Initialisation de la connexion à MiniLibX
	mlx = mlx_init();
	if (mlx == NULL)
		return (1);

	// Chargement de l'image .xpm
	img = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &img_width, &img_height);
	if (img == NULL)
		return (1);

	// Dimensions de la nouvelle image
	new_width = img_width * SCALE_FACTOR;
	new_height = img_height * SCALE_FACTOR;

	// Création d'une nouvelle image agrandie
	scaled_img = mlx_new_image(mlx, new_width, new_height);
	if (scaled_img == NULL)
		return (1);

	// Récupération des données de l'image originale
	data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	scaled_data = (int *)mlx_get_data_addr(scaled_img, &scaled_bpp, &scaled_size_line, &scaled_endian);

	// Redimensionnement de l'image en copiant chaque pixel avec agrandissement
	for (int y = 0; y < img_height; y++)
	{
		for (int x = 0; x < img_width; x++)
		{
			int color = data[y * (size_line / 4) + x];

			// Copier le pixel dans une zone agrandie de la nouvelle image
			for (int dy = 0; dy < SCALE_FACTOR; dy++)
			{
				for (int dx = 0; dx < SCALE_FACTOR; dx++)
				{
					int scaled_x = x * SCALE_FACTOR + dx;
					int scaled_y = y * SCALE_FACTOR + dy;
					scaled_data[scaled_y * (scaled_size_line / 4) + scaled_x] = color;
				}
			}
		}
	}

	// Création de la fenêtre pour afficher l'image agrandie
	win = mlx_new_window(mlx, 900, 600, "Image agrandie");
	if (win == NULL)
		return (1);

	// Affichage de l'image agrandie dans la fenêtre
	mlx_put_image_to_window(mlx, win, scaled_img, 0, 0);

	// Boucle pour garder la fenêtre ouverte
	mlx_loop(mlx);

	// Libération des ressources
	mlx_destroy_image(mlx, img);
	mlx_destroy_image(mlx, scaled_img);
	mlx_destroy_window(mlx, win);
	return (0);

	*/

	/*void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);*/
}