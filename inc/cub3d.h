# ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>

# define map_width 24
# define map_height 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define NUM_TEXTURES 2

/* Definitions: */
// FOV a.k.a Field Of View => in the context of optical devices, it refers to the max
// 	area that the device can capture.
//
// 	Using the player's looking angle and his coordinates, we can 
// 		determine the rays' vector.
//

/*
 * - Horizontal Grid Lines is the (NORTH & SOUTH).
 * - Vertical Grid Lines is the (WEST & EAST).
 *
 */

typedef struct s_mlx_
{
	int		*texture_buffer[NUM_TEXTURES];
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	dir;
	t_vector	left_plane_half;
	t_vector	iter;
	t_vector	ray;
	t_vector	intersect_pos;
	double	projection_plane_distance;
	double	projection_plane_size;
}	t_camera;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	//
}	t_player;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	pos;
	//
}	t_ray;

typedef struct s_cub_env
{
	t_camera	camera;
}		t_cub_env;

extern t_cub_env	g_cub_env;


/* ------ Functions Prototype -------- */
void		calc_ray(void);



















# endif
