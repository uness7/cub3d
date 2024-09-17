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
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define NUM_TEXTURES 2
# define FOV 60
# define TILESIZE 40


/*
 * - Horizontal Grid Lines is the (NORTH & SOUTH).
 * - Vertical Grid Lines is the (WEST & EAST).
 */

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


/* Typedefs */

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


typedef struct s_player
{

}	t_player;

typedef struct s_mlx
{
	// we need image struct in here
	void	*mlx;
	void	*win;

}	t_mlx;

typedef struct s_game
{
	t_map		*map;
	t_player	player;
	t_ray		ray;
	t_mlx		*mlx;

}	t_game;

/* ------ Functions Prototype -------- */



















# endif
