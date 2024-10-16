/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:24:40 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/14 14:58:58 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define NUM_TEXTURES 2
# define FOV 60
# define TILESIZE 40
# define ROTSPEED 20
# define MOVESPEED 3
# define TRANSPARENT 0x00000000

# define NUM_OF_RGB_VALUES 3
# define NUM_OF_TEXTURES 4

typedef struct seen
{
	bool			no_seen;
	bool			so_seen;
	bool			we_seen;
	bool			ea_seen;
}					t_seen;

typedef enum e_valid_chars
{
	EMPTY = '0',
	WALL = '1',
	NORTH = 'N',
	SOUTH = 'S',
	WEST = 'W',
	EAST = 'E'
}					t_valid_chars;

typedef enum e_orientation
{
	HORIZONTAL,
	VERTICAL
}					t_orientation;

typedef struct s_ray
{
	double			angle;
	double			distance;
	double			wall_l;
	double			x_h;
	double			x_v;
	double			y_h;
	double			y_v;
	t_orientation	type;
}					t_ray;

typedef struct s_color
{
	int				rgb;
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_texture
{
	char			*north;
	mlx_texture_t	*north_tx;
	char			*south;
	mlx_texture_t	*south_tx;
	char			*west;
	mlx_texture_t	*west_tx;
	char			*east;
	mlx_texture_t	*east_tx;

}					t_texture;

typedef struct s_map
{
	t_texture		textures;
	t_color			floor;
	t_color			ceiling;
	char			**map_cpy;
	unsigned int	*x_row;
	unsigned int	max_x;
	unsigned int	max_y;
}					t_map;

typedef struct s_playerCub3D
{
	t_valid_chars	orientation;
	double			angle;
	double			rd_fov;
	double			x;
	double			y;
	int				ws;
	int				ad;
	int				rotate;
}					t_player;

typedef struct s_game
{
	t_map			*map;
	t_player		player;
	t_ray			ray;
	mlx_t			*mlx;
	mlx_image_t		*pixel;

}					t_game;

/* ------ Functions Prototype -------- */

/* ---- src/parser/ ---- */
int					parser(int ac, char **av, t_game *game);
int					parse_textures_colors(char **lines, t_game *game);
void				find_player(t_game *game, char **map);
double				get_player_angle(t_game *game);
void				init_player(t_game *game);
int					validate_colors(t_game *game, char **cpy_lines);
int					parse_map(t_game *game, char **arr);
int					check_double_textures(char **textures);
char				**copy_textures(char **cpy_lines);
char				**copy_colors(char **cpy_lines);
int					copy_valid_map(t_game *game, char **map, char **lines,
						int num_lines);
char				**allocate_map(int num_lines);

/* ---- src/utils/ ---- */
bool				check_file_format(const char *file_path, char *format);
bool				is_textures_diff(char **textures);
bool				is_textures_formats(char **textures);
bool				is_valid_colors(char **colors);
bool				is_colors_diff(char **colors);
char				**ft_remove_empty_lines(char **cpy_lines);
int					validate_textures(t_game *game, char **cpy_lines);
int					parser(__attribute__((unused)) int ac, char **av,
						t_game *game);
void				toggle_bool(bool *b);

/* Map Validation */
bool				is_map_valid(char **map, int num_lines);
bool				check_adjacent_to_spaces(char **map, int rows);
bool				check_row_longer_than_top(char **map, int rows);
bool				check_row_longer_than_bottom(char **map, int rows);
bool				check_first_nd_last_char(char **map, int num_lines);
bool				has_multi_valid_chars(char **map, int rows);
bool				check_first_nd_last_rows(char **map, int rows);
bool				is_composed_of_valid_chars(char **map);
int					count_lines(char *filename);

char				**extract_lines(int fd, char *av, t_game *game);
char				**ft_remove_empyt_lines(char **cpy_lines);

/* Initialization */
/* src/init */
t_game				*allocate_memory_for_game(void);
void				print_game_data(t_game *game);
void				get_colors(t_game *game, char *rgb, char *space);
void				init_colors(t_game *game, t_color colors, char *space);
int					get_textures(t_game *game, char **textures);
void				load_textures(t_game *game);
void				load_colors(t_game *game, char **colors);
int					load_map(t_game *game, char **map, int num_lines);

/* RAYCASTING */
void				init_window(t_game *game);
void				init_player(t_game *game);
double				get_p_angle(t_game *game);
void				game_loop(void *gameptr);
void				castrays(t_game *game);
double				get_v_inter(t_game *game);
double				get_h_inter(t_game *game);
int					check_inter(t_game *game, double *step, double *inter,
						t_orientation o);
bool				check_hit(t_game *game, double x, double y);
void				render_line(t_game *game, int ray);
void				put_line(int t_pixel, int b_pixel, int ray, t_game *game);
void				put_floor_sky(t_game *game, int ray, int top_p,
						int bottom_p);
mlx_texture_t		*get_ray_texture(t_game *game);
int					reverse_bytes(int c);
double				get_x_o(t_game *game, int t_width);
void				draw_player(t_game *game);
void				draw_square(t_game *game, int map_x, int map_y, int color);
void				terminate_game(void *gameptr);

/* MOVEMENT */
void				keypress(mlx_key_data_t keydata, void *gameptr);
void				keyrelease(mlx_key_data_t keydata, t_game *game);
void				player_controller(t_game *game);
double				angle_reset(double angle);
void				check_move(double new_x, double new_y, t_game *game);
void				move_player(t_game *game, double new_x, double new_y);

int					init_max_x(t_game *game);
int					init_max_y(t_game *game);
int					init_x_row(t_game *game);

/* Memory Management */
void				free_game(t_game *game);

#endif
