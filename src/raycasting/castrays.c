# include "../../inc/cub3d.h"

void    init_x_row(t_game *game)
{
    int     i;
    int     j;

    game->map->x_row = malloc(sizeof(int) * (game->map->max_y + 1));
    if (game->map->x_row == NULL)
    {
        ft_putstr_fd("malloc failed", 2);
        exit(EXIT_FAILURE);
    }
    i = 0;
    j = 0;
    while (game->map->map_cpy[i] != NULL)
    {
        game->map->x_row[j] = ft_strlen(game->map->map_cpy[i]);
        i++;
        j++;
    }
}

void    init_max_y(t_game *game)
{
    int     i;

    i = 0;
    while (game->map->map_cpy[i] != NULL)
        i++;
    game->map->max_y = i;
}

void    init_max_x(t_game *game)
{
    int     i;
    int     len;

    i = 0;
    len = 0;
    game->map->max_x = 0;
    while (game->map->map_cpy[i] != NULL)
    {
        len = ft_strlen(game->map->map_cpy[i]);
        if ((unsigned int)len > game->map->max_x)
            game->map->max_x = len;
        i++;
    }
}

bool    check_hit(t_game *game, double x, double y)
{
    unsigned int    x_m;
    unsigned int    y_m;

    if (x < 0 || y < 0)
        return true;
    x_m = (unsigned int)floor(x / TILESIZE);
    y_m = (unsigned int)floor(y / TILESIZE);
    if ((y_m >= game->map->max_y || x_m >= game->map->x_row[y_m]))
        return (true);
    if (game->map->map_cpy[(int)y_m])
    {
        if (game->map->map_cpy[(int)y_m][(int)x_m])
        {
            if (game->map->map_cpy[(int)y_m][(int)x_m] == '1')
                return (true);
        }
    }
    return (false);
}

int     check_inter(t_game *game, double *step, double *inter, t_orientation o)
{
    if (o == HORIZONTAL)
    {
        if (game->ray.angle > 0 && game->ray.angle < M_PI)
        {
            *inter += TILESIZE;
            return (-1);
        }
        *step *= -1;
    }
    else if (o == VERTICAL)
    {
        if (!(game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI /2))
        {
            *inter += TILESIZE;
            return (-1);
        }
        *step *= -1;
    }
    return (1);
}

void    check_move(double new_x, double new_y, t_game *game)
{
    long	map_x;
    long	map_y;

    map_x = ((game->player.x + new_x) / TILESIZE);
    map_y = ((game->player.y + new_y) / TILESIZE);
    if (map_y < 0 || map_x < 0)
        return ;
    if (map_y >= game->map->max_y || map_x >= game->map->max_x)
        return ;

    if (game->map->map_cpy[map_y][map_x] == '0'
            || game->map->map_cpy[map_y][map_x] == (char)game->player.orientation)
    {
        game->player.x += new_x;
        game->player.y += new_y;
    }
}

void    move_player(t_game *game, double new_x, double new_y)
{
    if (game->player.ws == 1)
	{
		new_x = cos(game->player.angle) * MOVESPEED;
		new_y = sin(game->player.angle) * MOVESPEED;
	}
	else if (game->player.ws == -1)
	{
		new_x = -cos(game->player.angle) * MOVESPEED;
		new_y = -sin(game->player.angle) * MOVESPEED;
	}
	else if (game->player.ad == 1)
	{
		new_x = -sin(game->player.angle) * MOVESPEED;
		new_y = cos(game->player.angle) * MOVESPEED;
	}
	else if (game->player.ad == -1)
	{
		new_x = sin(game->player.angle) * MOVESPEED;
		new_y = -cos(game->player.angle) * MOVESPEED;
	}
	check_move(new_x, new_y, game);
}

double  angle_reset(double angle)
{
    if (angle > M_PI * 2)
        return (angle -= M_PI * 2);
    if (angle < 0)
        return (angle += M_PI * 2);
    else
        return (angle);
}

void    player_controller(t_game *game)
{
    if (game->player.rotate == 1)
    {
		game->player.angle += 0.001 * ROTSPEED;
    }
	else if (game->player.rotate == -1)
    {
		game->player.angle -= 0.001 * ROTSPEED;
    }
	if (game->player.ws != 0 || game->player.ad != 0)
    {
		move_player(game, 0, 0);
    }
	game->player.angle = angle_reset(game->player.angle);
}

double  get_h_inter(t_game *game)
{
    double  h_x;
    double  h_y;
    double  x_step;
    double  y_step;
    int         pixel;

    y_step = TILESIZE;
    x_step = TILESIZE / tan(game->ray.angle);
    h_y = floor(game->player.y / TILESIZE) * TILESIZE;
    pixel = check_inter(game, &y_step, &h_y, HORIZONTAL);
    h_x = game->player.x + (h_y - game->player.y) / tan(game->ray.angle);
    if ((game->ray.angle > M_PI / 2 && game->ray.angle < (3 * M_PI) /2 ) &&\
            x_step > 0)
    {
        x_step *= -1; 
    }
    else if ((game->ray.angle > (3 * M_PI) /2 || game->ray.angle < M_PI / 2)\
            && x_step < 0)
    {
        x_step *= -1;
    }
    while (!check_hit(game, h_x, h_y - pixel))
    {
        h_x += x_step;
        h_y += y_step;
    }
    game->ray.x_h = h_x;
    game->ray.y_h = h_y;
    return (sqrt(pow(h_x - game->player.x, 2) + pow(h_y - game->player.y, 2)));
}

double  get_v_inter(t_game *game)
{
    double	v_x;
    double	v_y;
    double	x_step;
    double	y_step;
    int		pixel;

    x_step = TILESIZE;
    y_step = TILESIZE * tan(game->ray.angle);
    v_x = floor(game->player.x / TILESIZE) * TILESIZE;
    pixel = check_inter(game, &x_step, &v_x, VERTICAL);
    v_y = game->player.y + (v_x - game->player.x) * tan(game->ray.angle);
    if ((game->ray.angle > M_PI && game->ray.angle < 2 * M_PI) && y_step > 0)
        y_step *= -1;
    else if ((game->ray.angle < M_PI && game->ray.angle > 0) && y_step < 0)
        y_step *= -1;
    while (!check_hit(game, v_x - pixel, v_y))
    {
        v_x += x_step;
        v_y += y_step;
    }
    game->ray.x_v = v_x;
    game->ray.y_v = v_y;
    return (sqrt(pow(v_x - game->player.x, 2) + pow(v_y - game->player.y, 2)));
}

void	put_floor_sky(t_game *game, int ray, int top_p, int bottom_p)
{
	int	f_color;
	int	s_color;
	int	i;

	f_color = game->map->floor.rgb;
	s_color = game->map->ceiling.rgb;
	i = 0;
	while (bottom_p < SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->pixel, ray, bottom_p, f_color);
		bottom_p++;
	}
	while (i < top_p)
	{
		mlx_put_pixel(game->pixel, ray, i, s_color);
		i++;
	}
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

double	get_x_o(t_game *game, int t_width)
{
	double	x_o;

	if (game->ray.type == HORIZONTAL)
		x_o = (int)fmodf((game->ray.x_h * (t_width / TILESIZE)), t_width);
	else
		x_o = (int)fmodf((game->ray.y_v * (t_width / TILESIZE)), t_width);
	return (x_o);
}

mlx_texture_t	*get_ray_texture(t_game *game)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (game->ray.angle > M_PI && game->ray.angle < 2 * M_PI
		&& game->ray.type == HORIZONTAL)
		texture = game->map->textures.north_tx;
	else if (game->ray.angle < M_PI && game->ray.angle > 0
		&& game->ray.type == HORIZONTAL)
		texture = game->map->textures.south_tx;
	else if (game->ray.angle < 3 * M_PI / 2 && game->ray.angle > M_PI / 2
		&& game->ray.type == VERTICAL)
		texture = game->map->textures.west_tx;
	else if ((game->ray.angle > 3 * M_PI / 2 || game->ray.angle < M_PI / 2)
		&& game->ray.type == VERTICAL)
		texture = game->map->textures.east_tx;
	return (texture);
}

void	put_line(int top_p, int bottom_p, int ray, t_game *game)
{
	double			y_o;
	double			x_o;
	double			step;
	mlx_texture_t	*texture;
	uint32_t		*pixels;

	texture = get_ray_texture(game);
    if (texture == NULL)
    {
        ft_putstr_fd("texture variable is empty\n", 2);
        exit(1);
    }
	pixels = (uint32_t *)texture->pixels;
	step = (double)texture->width / game->ray.wall_l;
	x_o = get_x_o(game, texture->width);
	y_o = (top_p - (SCREEN_HEIGHT/ 2) + (game->ray.wall_l / 2)) * step;
	if (y_o < 0)
		y_o = 0;
	put_floor_sky(game, ray, top_p, bottom_p);
	while (top_p < bottom_p)
	{
		mlx_put_pixel(game->pixel, ray, top_p, reverse_bytes(
				pixels[(int)y_o * texture->width + (int)x_o]));
		y_o += step;
		top_p++;
	}
}

void    render_line(t_game *game, int ray)
{
    double  line_l;
    double  top_p;
    double  bottom_p;

    game->ray.distance *= cos(angle_reset(game->ray.angle - game->player.angle));
    line_l = (TILESIZE / game->ray.distance) * ((SCREEN_WIDTH / 2) / tan(game->player.rd_fov / 2));
    bottom_p = (SCREEN_HEIGHT / 2) + (line_l / 2);
    top_p = (SCREEN_HEIGHT / 2) - (line_l / 2);
    game->ray.wall_l = line_l;
    if (bottom_p > SCREEN_HEIGHT)
        bottom_p = SCREEN_HEIGHT;
    if (top_p < 0)
        top_p = 0;
    put_line(top_p, bottom_p, ray, game);
}

void    castrays(t_game *game)
{
    int         ray;
    double  h_inter;
    double  v_inter;

    ray = 0;
    game->ray.angle = game->player.angle - (game->player.rd_fov / 2);
    while (ray < SCREEN_WIDTH)
    {
        game->ray.angle = angle_reset(game->ray.angle);
        h_inter = get_h_inter(game);
        v_inter = get_v_inter(game);
        if (v_inter <= h_inter)
        {
            game->ray.distance = v_inter;
            game->ray.type = VERTICAL;
        }
        else 
        { 
            game->ray.distance = h_inter;
            game->ray.type = HORIZONTAL;
        }
        render_line(game, ray);
        ray++;
        game->ray.angle += (game->player.rd_fov / SCREEN_WIDTH);
    }
}
