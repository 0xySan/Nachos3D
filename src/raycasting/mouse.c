/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaquet <etaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:00:13 by etaquet           #+#    #+#             */
/*   Updated: 2025/03/20 15:12:18 by etaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

void	left_move(double x, t_raycasting *data)
{
	double	olddirx;
	double	oldplanex;
	double rotspeed;

	rotspeed = (data->mousex - x) / 75;
	if (rotspeed > 0.15)
		rotspeed = 0.15;
	olddirx = data->v_x;
	data->v_x = data->v_x * cos(-rotspeed) - data->v_y * sin(-rotspeed);
	data->v_y = olddirx * sin(-rotspeed) + data->v_y * cos(-rotspeed);
	oldplanex = data->plane_x;
	data->plane_x = data->plane_x * cos(-rotspeed) - data->plane_y * sin(-rotspeed);
	data->plane_y = oldplanex * sin(-rotspeed) + data->plane_y * cos(-rotspeed);
}

void	move_right(double x, t_raycasting *data)
{
	double	olddirx;
	double	oldplanex;
	double rotspeed;

	rotspeed = (x - data->mousex) / 75;
	if (rotspeed > 0.15)
		rotspeed = 0.15;
	olddirx = data->v_x;
	data->v_x = data->v_x * cos(rotspeed) - data->v_y * sin(rotspeed);
	data->v_y = olddirx * sin(rotspeed) + data->v_y * cos(rotspeed);
	oldplanex = data->plane_x;
	data->plane_x = data->plane_x * cos(rotspeed) - data->plane_y * sin(rotspeed);
	data->plane_y = oldplanex * sin(rotspeed) + data->plane_y * cos(rotspeed);
}

void	cursor_test(double x, double y, void *param)
{
	t_raycasting *data;

	data = param;
	if (x < data->mousex && data->mousex != s_width / 2)
		left_move(x, data);
	else if (x > data->mousex && data->mousex != s_width / 2)
		move_right(x, data);
	data->mousex = x;
	data->mousey = y;
	if (x < s_width / 2 - 25 || x > s_width / 2 + 25 || y < s_height / 2 - 25 || y > s_height / 2 + 25)
	{
		mlx_set_mouse_pos(data->mlx, s_width / 2, s_height / 2);
		data->mousex = s_width / 2;
		data->mousey = s_height / 2;
		return ;
	}
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, s_width, s_height);
	raycasting(param);
}
