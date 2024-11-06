/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:57:50 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/06 14:15:25 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_anime(t_img img, t_var *var)
{
	int	i;

	i = 0;
	while (i < 11)
		mlx_destroy_image(var->mlx, img.img_collectible[i++]);
	i = 0;
	while (i < 11)
		mlx_destroy_image(var->mlx, img.img_player[i++]);
}
