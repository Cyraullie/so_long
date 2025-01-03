/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:33:03 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/07 11:20:29 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_var *var, int new_x, int new_y)
{
	if (var->map.map[new_y / IMG_S][new_x / IMG_S] != '1'
		&& var->map.map[new_y / IMG_S][new_x / IMG_S] != 'E')
	{
		if (var->map.map[new_y / IMG_S][new_x / IMG_S] == 'C')
			var->nb_coin++;
		var->map.map[var->player_y / IMG_S][var->player_x / IMG_S] = '0';
		var->player_x = new_x;
		var->nb_move++;
		var->player_y = new_y;
		var->map.map[var->player_y / IMG_S][var->player_x / IMG_S] = 'P';
		put_img(var, init_img(var), var->map);
	}
	if (var->map.map[new_y / IMG_S][new_x / IMG_S] == 'E'
		&& var->map.nb_item == var->nb_coin)
	{
		var->map.map[var->player_y / IMG_S][var->player_x / IMG_S] = '0';
		var->player_x = new_x;
		var->nb_move++;
		var->player_y = new_y;
		var->map.map[var->player_y / IMG_S][var->player_x / IMG_S] = '0';
		var->end = 0;
		put_img(var, init_img(var), var->map);
		display_end_screen(var);
	}
	ft_printf("number of movement : %d\n", var->nb_move);
}
