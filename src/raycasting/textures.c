/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:41:58 by tle-goff          #+#    #+#             */
/*   Updated: 2025/03/19 18:38:11 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

void	drawBuffer(uint32_t buffer[s_height][s_width], mlx_image_t *image)
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

void	loadImage(uint32_t texture[pixel_tex * pixel_tex], const char *filename)
{
	int				index;
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
			index = (y * pixel_tex + x) * 4;
			uint8_t a = tex->pixels[index];
			uint8_t r = tex->pixels[index + 1];
			uint8_t g = tex->pixels[index + 2];
			uint8_t b = tex->pixels[index + 3];
			texture[y * pixel_tex + x] = (a << 24) | (r << 16) | (g << 8) | b;
			x++;
		}
		y++;
	}
	mlx_delete_texture(tex);
}
