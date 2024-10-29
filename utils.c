/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:31:34 by cgoldens          #+#    #+#             */
/*   Updated: 2024/10/29 11:31:48 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	if (!buf)
		buf = ft_calloc(1, sizeof(char));
	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}