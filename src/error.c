/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaquet <etaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:52:11 by etaquet           #+#    #+#             */
/*   Updated: 2025/03/18 16:07:43 by etaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nachos3d.h"

void	ft_exit(int i)
{
	if (i == 0)
		return ;
	if (i == 1)
		ft_dprintf(2, "Error\nNO Wall format is wrong\n");
	if (i == 2)
		ft_dprintf(2, "Error\nSO Wall format is wrong\n");
	if (i == 3)
		ft_dprintf(2, "Error\nWE Wall format is wrong\n");
	if (i == 4)
		ft_dprintf(2, "Error\nEA Wall format is wrong\n");
	if (i == 5)
		ft_dprintf(2, "Error\nFloor format is wrong\n");
	if (i == 6)
		ft_dprintf(2, "Error\nSky format is wrong\n");
	if (i == 7)
		ft_dprintf(2, "Error\nPlayer is missing or too many players\n");
	if (i == 8)
		ft_dprintf(2, "Error\nMap is missing or invalid\n");
	if (i == 9)
		ft_dprintf(2, "Error\nMap is not closed\n");
	exit(i);
}

void	free_exit(t_map *map)
{
	if (map->NO_Wall)
		free(map->NO_Wall);
	if (map->SO_Wall)
		free(map->SO_Wall);
	if (map->WE_Wall)
		free(map->WE_Wall);
	if (map->EA_Wall)
		free(map->EA_Wall);
	if (map->map)
		ft_free_args(map->map);
	ft_exit(map->error);
}

void	ft_free(t_map *map)
{
	if (map->NO_Wall)
		free(map->NO_Wall);
	if (map->SO_Wall)
		free(map->SO_Wall);
	if (map->WE_Wall)
		free(map->WE_Wall);
	if (map->EA_Wall)
		free(map->EA_Wall);
	if (map->map)
		ft_free_args(map->map);
}
