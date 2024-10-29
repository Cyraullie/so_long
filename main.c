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

void    create_window(char *buffer)
{
    void *mlx;
    void *win;
    int x;
    int y;
    int i;

    y = 0;
    x = 0;
    i = 0;
    mlx = mlx_init();
    if (mlx == NULL)
        return (1);
    while (buffer[i] != '\0')
    {
        if (buffer[i] == '\n')
            y++;
        i++;
    }
    i--;
    printf("%d\n", y);
    printf("%d", i / y);
    x = i / y;

    win = mlx_new_window(mlx, x * IMG_S, y * IMG_S, "Image agrandie");
    mlx_loop(mlx);
}


int	main(void)
{
	int		fd1;
	char	*buffer;

    buffer = NULL;
	fd1 = open("maps/map1.ber", O_RDONLY);
	buffer = read_map(fd1, buffer);
    printf("%s", buffer);
    create_window(buffer);

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