/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:12:15 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/04 16:15:49 by cgoldens         ###   ########.fr       */
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
