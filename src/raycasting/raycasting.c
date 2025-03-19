/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:10:53 by tle-goff          #+#    #+#             */
/*   Updated: 2025/03/19 19:36:00 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"
#include <float.h>

void draw_wall(t_raycasting *data, int linewidth, int x)
{
	double		texpos;
	uint32_t	color;
	int			texy;

	data->step = 1.0 * pixel_tex / linewidth;
	texpos = (data->drawstart - s_height / 2 + linewidth / 2) * data->step;
	int y = data->drawstart;
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

void	set_elem(t_raycasting *data, int x)
{
	data->camerax = 2 * x / (double)s_width - 1;
	data->raydirx = data->v_x + data->plane_x * data->camerax;
	data->raydiry = data->v_y + data->plane_y * data->camerax;
	data->mapx = (int)data->x;
	data->mapy = (int)data->y;
	data->deltadistx = (data->raydirx == 0) ? DBL_MAX : fabs(1.0 / data->raydirx);
	data->deltadisty = (data->raydiry == 0) ? DBL_MAX : fabs(1.0 / data->raydiry);
	data->hit = 0;
}

void	clear_buffer(t_raycasting *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < s_height)
	{
		x = 0;
		while (x < s_width)
		{
			data->buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}

void raycasting(void *param)
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
		if(data->side == 0)
			data->perpwalldist = (data->sidedistx - data->deltadistx);
		else
			data->perpwalldist = (data->sidedisty - data->deltadisty);
		if (data->perpwalldist < 0.000001)
			data->perpwalldist = 0.000001;
		linewidth = (int)(s_height / data->perpwalldist);
		wall_direction(linewidth, data);
		draw_wall(data, linewidth, x++);
	}
	drawBuffer(data->buffer, data->image);
	clear_buffer(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

void	direction_selector(t_map *map, t_raycasting *data)
{
	double fov = tan((90 * 3.1415 / 180) / 2);


	data->plane_x = 0;
	data->plane_y = 0;
	data->v_x = 0;
	data->v_y = 0;
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

void	free_tab(t_map *map, int **tab)
{
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	start_project(t_map *map, int **mapping)
{
	t_raycasting	*data;
	mlx_t			*mlx;

	mlx = mlx_init(s_width, s_height, "Nachos", true);
	data = malloc(sizeof(t_raycasting));
	data->map = mapping;
	data->mlx = mlx;
	data->x = map->pos[1];
	data->y = map->pos[0];
	printf("%i %i\n", map->pos[0], map->pos[1]);
	show_map(data->map, map);
	direction_selector(map, data);
	data->image = mlx_new_image(data->mlx, s_width, s_height);
	data->mapx = 0;
	data->mapy = 0;
	data->buffer = malloc(sizeof(uint32_t[s_height][1920]));
	data->texture = malloc(sizeof(uint32_t[4096]) * 8);
	data->settings = map;
	loadImage(data->texture[0], map->NO_Wall);
	loadImage(data->texture[1], map->EA_Wall);
	loadImage(data->texture[2], map->WE_Wall);
	loadImage(data->texture[3], map->SO_Wall);
	mlx_key_hook(data->mlx, key_hook, data);
	raycasting((void *)data);
	mlx_loop(mlx);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free_tab(map, data->map);
	free(data->buffer);
	free(data->texture);
	free(data);
}
