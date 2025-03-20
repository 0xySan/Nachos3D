/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaquet <etaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:10:53 by tle-goff          #+#    #+#             */
/*   Updated: 2025/03/20 14:47:08 by etaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

void	draw_wall(t_raycasting *data, int linewidth, int x)
{
	double		texpos;
	uint32_t	color;
	int			texy;
	int			y;

	data->step = 1.0 * pixel_tex / linewidth;
	texpos = (data->drawstart - s_height / 2 + linewidth / 2) * data->step;
	y = data->drawstart;
	while (y < data->drawend)
	{
		texy = (int)texpos & (pixel_tex - 1);
		texpos += data->step;
		if_choice(data);
		color = data->texture[data->texnum][pixel_tex * texy + data->texx];
		data->buffer[y][x] = color;
		y++;
	}
}

void	raycasting(void *param)
{
	int				linewidth;
	t_raycasting	*data;
	int				x;

	x = 0;
	data = param;
	draw_extrem(data);
	while (x < s_width)
	{
		set_elem(data, x);
		raydirection(data);
		hit_side(data);
		if (data->side == 0)
			data->perpwalldist = (data->sidedistx - data->deltadistx);
		else
			data->perpwalldist = (data->sidedisty - data->deltadisty);
		if (data->perpwalldist < 0.000001)
			data->perpwalldist = 0.000001;
		linewidth = (int)(s_height / data->perpwalldist);
		wall_direction(linewidth, data);
		draw_wall(data, linewidth, x++);
	}
	drawbuffer(data->buffer, data->image);
	clear_buffer(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

void	direction_selector(t_map *map, t_raycasting *data)
{
	double	fov;

	fov = tan((90 * 3.1415 / 180) / 2);
	if (map->dir == 'E')
	{
		data->plane_y = fov;
		data->v_x = 1;
	}
	if (map->dir == 'S')
	{
		data->plane_x = -fov;
		data->v_y = 1;
	}
	if (map->dir == 'N')
	{
		data->plane_x = fov;
		data->v_y = -1;
	}
	if (map->dir == 'W')
	{
		data->plane_y = -fov;
		data->v_x = -1;
	}
}

void	set_elem_data(t_raycasting *data, t_map *map)
{
	data->x = map->pos[1];
	data->y = map->pos[0];
	data->plane_x = 0;
	data->plane_y = 0;
	data->v_x = 0;
	data->v_y = 0;
	data->mousex = 0;
	data->mousey = 0;
	direction_selector(map, data);
	data->image = mlx_new_image(data->mlx, s_width, s_height);
	data->mapx = 0;
	data->mapy = 0;
	data->buffer = malloc(sizeof(uint32_t[s_height][1920]));
	data->texture = malloc(sizeof(uint32_t[4096]) * 8);
	data->settings = map;
}

void	start_project(t_map *map, int **mapping)
{
	t_raycasting	*data;
	mlx_t			*mlx;

	mlx = mlx_init(s_width, s_height, "Nachos", true);
	data = malloc(sizeof(t_raycasting));
	data->map = mapping;
	data->mlx = mlx;
	set_elem_data(data, map);
	loadimage(data->texture[0], map->NO_Wall);
	loadimage(data->texture[1], map->EA_Wall);
	loadimage(data->texture[2], map->WE_Wall);
	loadimage(data->texture[3], map->SO_Wall);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_cursor_hook(data->mlx, cursor_test, data);
	raycasting((void *)data);
	mlx_loop(mlx);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free_tab(map, data->map);
	free(data->buffer);
	free(data->texture);
	free(data);
}
