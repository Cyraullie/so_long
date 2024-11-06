/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:39:19 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/06 13:56:07 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_end_screen(t_var *var)
{
	char	*message;
	char	*moves_str;
	char	*final_message;

	message = "Congratulations!";
	moves_str = ft_itoa(var->nb_move);
	final_message = ft_strjoin("Total moves: ", moves_str);
	mlx_clear_window(var->mlx, var->win);
	mlx_string_put(var->mlx, var->win, 100, 70, 0x00FF00, message);
	mlx_string_put(var->mlx, var->win, 100, 100, 0x00FF00, final_message);
	mlx_string_put(var->mlx, var->win, 100, 130, 0xFF0000, "Press ESC to quit");
	free(moves_str);
	free(final_message);
}
