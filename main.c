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

int	main(void)
{
    void *mlx;
    void *win;
    void *img;
    int img_width, img_height;
    int x, y;
    int *data;
    int bpp, size_line, endian;
    
    // Initialisation de la connexion à MiniLibX
    mlx = mlx_init();
    if (mlx == NULL)
        return (1);
    
    // Chargement de l'image .xpm
    img = mlx_xpm_file_to_image(mlx, "./textures/player.xpm", &img_width, &img_height);
    if (img == NULL)
        return (1);

    // Création d'une fenêtre qui s'adapte à la taille agrandie de l'image
    win = mlx_new_window(mlx, img_width * SCALE_FACTOR, img_height * SCALE_FACTOR, "Image agrandie");
    if (win == NULL)
        return (1);

    // Obtenir l'adresse de la mémoire de l'image
    data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

    // Agrandissement : Redessin de chaque pixel
    for (y = 0; y < img_height; y++)
    {
        for (x = 0; x < img_width; x++)
        {
            int color = data[y * (size_line / 4) + x];  // Couleur du pixel (x, y)

            // Dessine un "bloc" de pixels pour agrandir
            for (int dy = 0; dy < SCALE_FACTOR; dy++)
            {
                for (int dx = 0; dx < SCALE_FACTOR; dx++)
                {
                    mlx_pixel_put(mlx, win, x * SCALE_FACTOR + dx, y * SCALE_FACTOR + dy, color);
                }
            }
        }
    }

    // Boucle pour garder la fenêtre ouverte
    mlx_loop(mlx);

    // Libération des ressources
    mlx_destroy_image(mlx, img);
    mlx_destroy_window(mlx, win);
    return (0);

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