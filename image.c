/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:48:44 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/05 14:13:04 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	add_floor(t_var *var, int wh, int ww)
{
	t_img	img;

	img = init_img(var);
	if (!img.img_wall || !img.img_floor || !img.img_collectible
		|| !img.img_exit_c || !img.img_exit_o || !img.img_player)
	{
		mlx_destroy_image(var->mlx, img.img_wall);
		mlx_destroy_image(var->mlx, img.img_floor);
		mlx_destroy_image(var->mlx, img.img_collectible);
		mlx_destroy_image(var->mlx, img.img_exit_c);
		mlx_destroy_image(var->mlx, img.img_exit_o);
		mlx_destroy_image(var->mlx, img.img_player);
		return (1);
	}
	var->win = mlx_new_window(var->mlx, ww, wh, "so_long");
	if (!var->win)
		return (1);
	put_img(var, img, var->map);
	return (0);
}

void	*choose_image(char c, t_img img, t_var *var)
{
	if (c == '1')
		return (img.img_wall);
	else if (c == '0')
		return (img.img_floor);
	else if (c == 'C')
		return (img.img_collectible);
	else if (c == 'E')
	{
		if (var->map.nb_item == var->nb_coin)
			return (img.img_exit_o);
		else
			return (img.img_exit_c);
	}
	else if (c == 'P')
		return (img.img_player);
	return (NULL);
}

void	put_img(t_var *var, t_img img, t_map map)
{
	int		x;
	int		y;
	char	*move;
	void	*c;

	c = NULL;
	y = 0;
	x = 0;
	while (y < map.rows)
	{
		while (x < map.cols)
		{
			fuck_norminette(var, img, x, y);
			x++;
		}
		y++;
		x = 0;
	}
	move = ft_itoa(var->nb_move);
	mlx_string_put(var->mlx, var->win, 15, 15, 0xFFFFFF, move);
}

t_img	init_img(t_var *var)
{
	t_img	data;
	int		iw;
	int		ih;

	data.img_wall = load_image(var->mlx, "textures/wall.xpm", &iw, &ih);
	data.img_floor = load_image(var->mlx, "textures/floor.xpm", &iw, &ih);
	data.img_collectible = load_image(var->mlx, "textures/coin1.xpm", &iw, &ih);
	data.img_exit_c = load_image(var->mlx, "textures/exit_close.xpm", &iw, &ih);
	data.img_exit_o = load_image(var->mlx, "textures/exit_open.xpm", &iw, &ih);
	data.img_player = load_image(var->mlx, "textures/player.xpm", &iw, &ih);
	data.iw = iw;
	data.ih = ih;
	return (data);
}

void	*load_image(void *mlx_ptr, char *file_path, int *width, int *height)
{
	void	*image;

	image = mlx_xpm_file_to_image(mlx_ptr, file_path, width, height);
	if (image == NULL)
	{
		ft_printf("Error\n Failed to load image %s\n", file_path);
	}
	return (image);
}
