/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:26:24 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/01 16:21:44 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>

# define IMG_S 32
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP -1
# define DOWN 1
# define LEFT -1
# define RIGHT 1
# define BUFFER_SIZE 4200

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map {
	char	**map;
	int		rows;
	int		cols;
}				t_map;

typedef struct s_img {
	void	*img_wall;
	void	*img_floor;
	void	*img_collectible;
	void	*img_exit;
	void	*img_player;
}				t_img;


// main part
void	get_map_size(char *buffer, int *rows, int *cols);
char	**convert_buffer_to_map(char *buffer, int rows, int cols);
int		add_floor(void *mlx, int wh, int ww, t_map map);
// map part
int		get_map_data(char *map);
int		handle_error_map(char *map, int rows, int cols);
int		check_wall(char *map, int rows, int cols);
int		check_item(char *map, int *e, int *c, int *p);
int		check_map(char *map, int rows, int cols);
// read part
char	*ft_free(char *buffer, char *buf);
char	*read_map(int fd, char *res);
char	*open_read_map(char *file);
// utils map
int		print_error(char *text, int status);
#endif