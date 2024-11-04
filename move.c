/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:33:03 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/04 16:45:17 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_var *var, int new_x, int new_y)
{
	if (var->map.map[new_y / IMG_S][new_x / IMG_S] != '1')
	{
		var->map.map[var->player_y / IMG_S][var->player_x / IMG_S] = '0';
		var->player_x = new_x;
		var->nb_move++;
		var->player_y = new_y;
		var->map.map[var->player_y / IMG_S][var->player_x / IMG_S] = 'P';
		put_img(var, init_img(var), var->map);
	}
}
