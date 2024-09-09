# include "cub3d.h"

void	init(t_camera *camera, t_player *player)
{
	g_cub_env.camera.pos = (t_vector){0, 0};
	g_cub_env.camera.dir = ft_normalize_vector((t_vector){1, 1});
	g_cub_env.camera.projection_plance_distance = 50;
	g_cub_env.camera.projection_plane_size = 100;
}
