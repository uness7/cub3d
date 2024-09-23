# ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>


# include "../libft/libft.h"
# include "../mlx/include/MLX42/MLX42.h"

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 1200 
# define NUM_TEXTURES 2
# define FOV 60
# define TILESIZE 40
# define ROTSPEED 20
# define MOVESPEED 3
# define MMAP_WALL 0x000000FF
# define MMAP_SPACE 0xFFFFFFFF
# define TRANSPARENT 0x00000000
# define MMAP_PLAYER 0xFF0000FF

# define NUM_OF_RGB_VALUES 3 /* used to allocate memory */
# define NUM_OF_TEXTURES 4

typedef enum e_valid_chars
{
	EMPTY = '0',
	WALL = '1',
	NORTH = 'N',
	SOUTH = 'S',
	WEST = 'W',
	EAST = 'E'

}	t_valid_chars;

typedef enum e_orientation
{
	HORIZONTAL,
	VERTICAL
}	t_orientation;

typedef struct s_ray
{
	double		angle;
	double		distance;
	double		wall_l;
	double		x_h;
	double		x_v;
	double		y_h;
	double		y_v;
	t_orientation	type;
}	t_ray;

typedef struct s_color
{
	int		rgb;
	int		r;
	int		g;
	int		b;
}	t_color;

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

}	t_texture; 

typedef struct s_map
{
	char	*file;
	char	**file_arr;
	char	**item_line;
	t_texture	textures; // filled
	t_color		floor; // filled
	t_color		ceiling; // filled
	int		*color_arr;
	char		**map_cpy;
	unsigned int	max_y;
	unsigned int	max_x;
	unsigned int	*x_row;;
	mlx_image_t	*map_img;	

}	t_map;

typedef struct s_player
{
	t_valid_chars	orientation; // filled
	double		angle; // filled
	double		rd_fov;
	double		x; // filled
	double		y; // fillled
	int			ws;
	int			ad;
	int			rotate;

}	t_player;

typedef struct s_game
{
	t_map		*map; // needs allocation
	t_player	player;
	t_texture	textures;
	t_ray		ray;
	mlx_t		*mlx;
	mlx_image_t	*pixel;

}	t_game;


/* ------ Functions Prototype -------- */

/* ---- src/parser/ ---- */
void	parser(int ac, char **av, t_game *game);
void    parse_textures_colors(char **lines , t_game *game);
void    find_player(t_game *game, char **map);
double  get_player_angle(t_game *game);
void	init_player(t_game *game);

/* ---- src/utils/ ---- */
bool	check_file_format(const char *file_path, char *format);
bool	is_textures_diff(char **textures);
bool	is_textures_formats(char **textures);
bool	is_valid_colors(char **colors);
bool	is_colors_diff(char **colors);

/* Map Validation */
bool	is_map_valid(char **map, int num_lines); // Checker Function
bool	check_adjacent_to_spaces(char **map, int rows);
bool	check_row_longer_than_top(char **map, int rows);
bool	check_row_longer_than_bottom(char **map, int rows);
bool	check_first_nd_last_char(char **map, int num_lines); // Rule 4
bool    has_multi_valid_chars(char **map, int rows); // Rule 3
bool 	check_first_nd_last_rows(char **map, int rows); // Rule 2
bool	is_composed_of_valid_chars(char **map); // Rule 1

int			count_lines(char *filename);

char	**extract_lines(int fd, char *av);
char	**ft_remove_empyt_lines(char **cpy_lines);

/* Initialization */
/* src/init */
void 	allocate_memory_for_game(t_game **game);
void	print_game_data(t_game *game);
void    get_colors(t_game *game, char *rgb, char *space);
void    init_colors(t_game *game, t_color colors, char *space);
void    get_textures(t_game *game, char **textures);
void 	load_textures(t_game *game);
void 	load_colors(t_game *game, char **colors);
void	load_map(t_game *game, char **map, int num_lines);


















# endif
