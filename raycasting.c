# include "cub3d.h"

void	raycasting(void)
{
	int		cs_x; // current_screen
	t_ray		c_ray; // current ray
	t_vector	player_pos_to_plane_center;	
	t_vector	c_pos_on_plane;
	t_vector	plane_iter;

	cs_x = -1;
	player_pos_to_plane_center = ft_scale_vector(
		camera.direction,
		camera.projection_plane_size
	);
	camera.left_plane_half = ft_rotate_vector(
			camera.direction,
			M_PI / 2
	);
	camera.left_plane_half = ft_rotate_vector(
			camera.left_plane_half
			camera.projection_plane_size / 2
	);
	c_pos_on_plane = ft_add_vector(
			player_pos_to_center,
			camera.left_plane_half
	);
	plane_iter = ft_scale_vector(
			camera.left_plane_half,
			-(2 / SCREEN_WIDTH)

	);
	while (++cs_x < SCREEN_WIDTH)
	{
		c_ray.pos = ft_normalize_vector(c_pos_on_plane);
		c_pos_on_plane = ft_add_vector(
				c_pos_on_plane,
				plane_iter
		);
	}
}
