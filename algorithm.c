/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:38:56 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/05 15:31:52 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mark_position(char **map, int x, int y, t_check *check)
{
	if (map[y][x] == 'C')
		check->collectibles_found++;
	if (map[y][x] == 'E')
		check->exit_found = 1;
	map[y][x] = 'V';
}

void	explore_direction(int x, int y, t_var *var, t_check *check)
{
	if (x < 0 || x >= var->map.cols || y < 0 || y >= var->map.rows)
		return ;
	if (var->tmp_map[y][x] == '1' || var->tmp_map[y][x] == 'V')
		return ;
	mark_position(var->tmp_map, x, y, check);
	explore_direction(x + 1, y, var, check);
	explore_direction(x - 1, y, var, check);
	explore_direction(x, y + 1, var, check);
	explore_direction(x, y - 1, var, check);
}

char	**copy_map(char **original_map, int rows)
{
	char	**map_copy;
	int		y;

	map_copy = malloc(sizeof(char *) * rows);
	if (!map_copy)
		return (NULL);
	y = 0;
	while (y < rows)
	{
		map_copy[y] = ft_strdup(original_map[y]);
		if (!map_copy[y])
		{
			while (y-- > 0)
				free(map_copy[y]);
			free(map_copy);
			return (NULL);
		}
		y++;
	}
	return (map_copy);
}

int	is_map_solvable(t_var *var)
{
	t_check	check;
	int		y;

	check.collectibles_found = 0;
	check.exit_found = 0;
	var->tmp_map = copy_map(var->map.map, var->map.rows);
	if (!var->tmp_map)
		return (0);
	explore_direction(var->player_x / IMG_S,
		var->player_y / IMG_S, var, &check);
	y = 0;
	while (y < var->map.rows)
		free(var->tmp_map[y++]);
	free(var->tmp_map);
	return (check.collectibles_found == var->map.nb_item && check.exit_found);
}
