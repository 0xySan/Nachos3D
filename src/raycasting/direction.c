/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:32:03 by tle-goff          #+#    #+#             */
/*   Updated: 2025/03/19 19:14:52 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

void	draw_extrem(t_raycasting *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < s_height)
	{
		x = 0;
		while (x < s_width)
		{
			data->buffer[y][x] = data->settings->floor;
			x++;
		}
		y++;
	}
	y = s_height / 2;
	while (y < s_height)
	{
		x = 0;
		while (x < s_width)
		{
			data->buffer[y][x] = data->settings->sky;
			x++;
		}
		y++;
	}
}

void	raydirection(t_raycasting *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->x - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->x) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->y - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->y) * data->deltadisty;
	}
}

void	hit_side(t_raycasting *data)
{
	while (data->hit == 0)
	{
		if (data->sidedistx < data->sidedisty)
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			data->side = 0;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			data->side = 1;
		}
		if (data->map[data->mapx][data->mapy] > 0)
			data->hit = 1;
	}
}

void	wall_direction(int linewidth, t_raycasting *data)
{
	data->drawstart = -linewidth / 2 + s_height / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = linewidth / 2 + s_height / 2;
	if (data->drawend >= s_height)
		data->drawend = s_height - 1;
	if (data->side == 0)
		data->wallx = data->y + data->perpwalldist * data->raydiry;
	else
		data->wallx = data->x + data->perpwalldist * data->raydirx;
	data->wallx -= floor((data->wallx));
	data->texx = (int)(data->wallx * (double)pixel_tex);
	if (data->side == 0 && data->raydirx > 0)
		data->texx = pixel_tex - data->texx - 1;
	if (data->side == 1 && data->raydiry < 0)
		data->texx = pixel_tex - data->texx - 1;
}

void	if_choice(t_raycasting *data)
{
	if (data->side == 0)
	{
		if (data->raydirx > 0)
			data->texnum = 1;
		else
			data->texnum = 3;
	}
	else
	{
		if (data->raydiry > 0)
			data->texnum = 2;
		else
			data->texnum = 0;
	}
}
