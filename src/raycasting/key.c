/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:01:28 by tle-goff          #+#    #+#             */
/*   Updated: 2025/03/19 19:41:16 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

static void	w_s(mlx_key_data_t keydata, t_raycasting *dat)
{
	if (keydata.key == MLX_KEY_W)
	{
		if (dat->map[(int)(dat->x + dat->v_x * speed)][(int)dat->y] == false)
			dat->x += dat->v_x * speed;
		if (dat->map[(int)dat->x][(int)(dat->y + dat->v_y * speed)] == false)
			dat->y += dat->v_y * speed;
	}
	if (keydata.key == MLX_KEY_S)
	{
		if (dat->map[(int)(dat->x - dat->v_x * speed)][(int)dat->y] == false)
			dat->x -= dat->v_x * speed;
		if (dat->map[(int)dat->x][(int)(dat->y - dat->v_y * speed)] == false)
			dat->y -= dat->v_y * speed;
	}
}

static void	a_d(mlx_key_data_t keydata, t_raycasting *dat)
{
	if (keydata.key == MLX_KEY_A)
	{
		if (dat->map[(int)(dat->x + dat->v_y * speed)][(int)dat->y] == false)
			dat->x += dat->v_y * speed;
		if (dat->map[(int)dat->x][(int)(dat->y - dat->v_x * speed)] == false)
			dat->y -= dat->v_x * speed;
	}
	if (keydata.key == MLX_KEY_D)
	{
		if (dat->map[(int)(dat->x - dat->v_y * speed)][(int)dat->y] == false)
			dat->x -= dat->v_y * speed;
		if (dat->map[(int)dat->x][(int)(dat->y + dat->v_x * speed)] == false)
			dat->y += dat->v_x * speed;
	}
}

static void	arrow(mlx_key_data_t keydata, t_raycasting *data)
{
	double	oldplanex;
	double	olddirx;

	if (keydata.key == MLX_KEY_LEFT)
	{
		olddirx = data->v_x;
		data->v_x = data->v_x * cos(-rotSpeed) - data->v_y * sin(-rotSpeed);
		data->v_y = olddirx * sin(-rotSpeed) + data->v_y * cos(-rotSpeed);
		oldplanex = data->plane_x;
		data->plane_x = data->plane_x
			* cos(-rotSpeed) - data->plane_y * sin(-rotSpeed);
		data->plane_y = oldplanex
			* sin(-rotSpeed) + data->plane_y * cos(-rotSpeed);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		olddirx = data->v_x;
		data->v_x = data->v_x * cos(rotSpeed) - data->v_y * sin(rotSpeed);
		data->v_y = olddirx * sin(rotSpeed) + data->v_y * cos(rotSpeed);
		oldplanex = data->plane_x;
		data->plane_x = data->plane_x
			* cos(rotSpeed) - data->plane_y * sin(rotSpeed);
		data->plane_y = oldplanex
			* sin(rotSpeed) + data->plane_y * cos(rotSpeed);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_raycasting	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
		free(data->buffer);
		free(data->texture);
		ft_free(data->settings);
		free_tab(data->settings, data->map);
		free(data);
		exit(0);
	}
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		a_d(keydata, data);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
		w_s(keydata, data);
	else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		arrow(keydata, data);
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, s_width, s_height);
	raycasting(param);
}
