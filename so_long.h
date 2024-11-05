/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:26:24 by cgoldens          #+#    #+#             */
/*   Updated: 2024/11/05 14:04:55 by cgoldens         ###   ########.fr       */
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
# define AA 126
# define AL 123
# define AD 125
# define AR 124
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
	int		nb_item;
}				t_map;

typedef struct s_img {
	void	*img_wall;
	void	*img_floor;
	void	*img_collectible;
	void	*img_exit_c;
	void	*img_exit_o;
	void	*img_player;
	int		iw;
	int		ih;
}				t_img;

typedef struct s_var {
	void	*mlx;
	void	*win;
	int		player_x;
	int		player_y;
	t_map	map;
	char	**tmp_map;
	int		nb_move;
	int		nb_coin;
}				t_var;

typedef struct s_check {
	int	collectibles_found;
	int	exit_found;
}				t_check;

// main part
int		init(t_var *var, char *file);
void	get_map_size(char *buffer, int *rows, int *cols);
char	**convert_buffer_to_map(char *buffer, int rows, int cols);
int		handle_key(int keycode, t_var *var);
//image part
int		add_floor(t_var *var, int wh, int ww);
t_img	init_img(t_var *var);
void	put_img(t_var *v, t_img i, t_map map);
void	*load_image(void *mlx_ptr, char *file_path, int *width, int *height);
void	*choose_image(char c, t_img img, t_var *var);
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
void	count_items(char *buffer, int *nb_items);
void	fuck_norminette(t_var *var, t_img img, int x, int y);
// move part
void	move_player(t_var *var, int new_x, int new_y);
// algo part
int		is_map_solvable(t_var *var);
char	**copy_map(char **original_map, int rows);
void	explore_direction(int x, int y, t_var *var, t_check *check);
void	mark_position(char **map, int x, int y, t_check *check);
#endif