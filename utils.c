/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:12:15 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/05 14:51:45 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_error(char *text, int status)
{
	ft_printf("%s", text);
	return (status);
}

void	count_items(char *buffer, int *nb_items)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == 'C')
			c++;
		i++;
	}
	*nb_items = c;
}

void	fuck_norminette(t_var *var, t_img img, int x, int y)
{
	void	*c;

	c = NULL;
	c = choose_image(var->map.map[y][x], img, var);
	if (c)
		mlx_put_image_to_window(var->mlx, var->win, c, x * img.iw, y * img.ih);
	if (var->map.map[y][x] == 'P')
	{
		var->player_x = x * img.iw;
		var->player_y = y * img.ih;
	}
}

char	**convert_buffer_to_map(char *buffer, int rows, int cols)
{
	int		row;
	int		col;
	int		i;
	char	**map;
	int		j;

	j = 0;
	i = 0;
	col = 0;
	row = 0;
	map = malloc(sizeof(char *) * rows);
	while (j < rows)
		map[j++] = malloc(sizeof(char) * (cols + 1));
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			map[row++][col] = '\0';
			col = 0;
		}
		else
			map[row][col++] = buffer[i];
		i++;
	}
	return (map);
}
