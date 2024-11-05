/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:03:34 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/05 15:33:06 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	insert_coin_frame(t_img *data, t_var *var, int *iw, int *ih)
{
	data->img_collectible[0] = load_image(var->mlx,
			"textures/coin1.xpm", iw, ih);
	data->img_collectible[1] = load_image(var->mlx,
			"textures/coin2.xpm", iw, ih);
	data->img_collectible[2] = load_image(var->mlx,
			"textures/coin3.xpm", iw, ih);
	data->img_collectible[3] = load_image(var->mlx,
			"textures/coin4.xpm", iw, ih);
	data->img_collectible[4] = load_image(var->mlx,
			"textures/coin5.xpm", iw, ih);
	data->img_collectible[5] = load_image(var->mlx,
			"textures/coin6.xpm", iw, ih);
	data->img_collectible[6] = load_image(var->mlx,
			"textures/coin7.xpm", iw, ih);
	data->img_collectible[7] = load_image(var->mlx,
			"textures/coin8.xpm", iw, ih);
	data->img_collectible[8] = load_image(var->mlx,
			"textures/coin9.xpm", iw, ih);
	data->img_collectible[9] = load_image(var->mlx,
			"textures/coin10.xpm", iw, ih);
	data->img_collectible[10] = load_image(var->mlx,
			"textures/coin11.xpm", iw, ih);
}

void	animate_collectibles(t_var *v, t_img img, t_map map)
{
	int		x;
	int		y;
	void	*coin_img;
	void	*floor;

	y = 0;
	floor = img.img_floor;
	while (y < map.rows)
	{
		x = 0;
		while (x < map.cols)
		{
			if (map.map[y][x] == 'C')
			{
				coin_img = img.img_collectible[v->anim_frame % 11];
				mlx_put_image_to_window(v->mlx, v->win, floor,
					x * img.iw, y * img.ih);
				mlx_put_image_to_window(v->mlx, v->win, coin_img,
					x * img.iw, y * img.ih);
			}
			x++;
		}
		y++;
	}
	v->anim_frame++;
}
