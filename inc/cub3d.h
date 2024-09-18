# ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>

/* Defines */

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





typedef enum e_valid_chars
{
	EMPTY = '0',
	WALL = '1',
	NORTH = 'N',
	SOUTH = 'S',
	WEST = 'W',
	EAST = 'E'

}	t_valid_chars;

typedef struct e_orientation
{
	HORIZONTAL,
	VERTICAL

}	t_orientation;

typedef struct s_map
{
	char	*file;
	char	**file_arr;
	char	**item_line;
	t_texture	textures;
	t_color		floor;
	t_color		ceiling;
	int		*color_arr;
	char		**map_cpy;
	unsigned int	max_y;
	unsigned int	max_x;
	unsigned int	*x_row;;
	mlx_image_t	*map_img;	

}	t_map;

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

typedef struct s_player
{
	t_valid_chars	orientation;
	double		angle;
	double		rd_fov;
	double		x;
	double		y;
	int			ws;
	int			ad;
	int			rotate;

}	t_player;

typedef struct s_game
{
	t_map		*map;
	t_player	player;
	t_texture	textures;
	t_ray		ray;
	mlx_t		*mlx;
	mlx_image_t	*pixel;

}	t_game;


/* ------ Functions Prototype -------- */



















# endif
