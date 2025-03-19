/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:41:58 by tle-goff          #+#    #+#             */
/*   Updated: 2025/03/19 19:58:09 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

void	set_elem(t_raycasting *data, int x)
{
	data->camerax = 2 * x / (double)s_width - 1;
	data->raydirx = data->v_x + data->plane_x * data->camerax;
	data->raydiry = data->v_y + data->plane_y * data->camerax;
	data->mapx = (int)data->x;
	data->mapy = (int)data->y;
	if (data->raydirx == 0)
		data->deltadistx = 1.7976931348623157e+308;
	else
		data->deltadistx = fabs(1.0 / data->raydirx);
	if (data->raydiry == 0)
		data->deltadisty = 1.7976931348623157e+308;
	else
		data->deltadisty = fabs(1.0 / data->raydiry);
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

void	drawbuffer(uint32_t buffer[s_height][s_width], mlx_image_t *image)
{
	uint32_t	color;
	int			y;
	int			x;

	y = 0;
	while (y < s_height)
	{
		x = 0;
		while (x < s_width)
		{
			color = buffer[y][x];
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	texture_set(int y, int x,
	mlx_texture_t *tex, uint32_t texture[pixel_tex*pixel_tex])
{
	int		index;
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	index = (y * pixel_tex + x) * 4;
	a = tex->pixels[index];
	r = tex->pixels[index + 1];
	g = tex->pixels[index + 2];
	b = tex->pixels[index + 3];
	texture[y * pixel_tex + x] = (a << 24) | (r << 16) | (g << 8) | b;
}

void	loadimage(uint32_t texture[pixel_tex*pixel_tex], const char *filename)
{
	mlx_texture_t	*tex;
	int				y;
	int				x;

	y = 0;
	tex = mlx_load_png(filename);
	while (y < pixel_tex)
	{
		x = 0;
		while (x < pixel_tex)
		{
			texture_set(y, x, tex, texture);
			x++;
		}
		y++;
	}
	mlx_delete_texture(tex);
}
