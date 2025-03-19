/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:38:50 by etaquet           #+#    #+#             */
/*   Updated: 2025/03/19 19:59:34 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nachos3d.h"

void	count_height_and_length(t_map *map)
{
	int		i;

	i = 0;
	while (map->map[i])
	{
		if (map->length < ft_strlen(map->map[i]))
			map->length = ft_strlen(map->map[i]);
		i++;
	}
	map->height = i;
}

int	**init_int_map(t_map *map)
{
	int		**int_map;
	size_t	i;
	size_t	j;

	i = 0;
	int_map = malloc(sizeof(int *) * map->height);
	while (i < map->height)
	{
		int_map[i] = malloc(sizeof(int) * map->length);
		j = 0;
		while (j < map->length)
		{
			if (j > ft_strlen(map->map[i])
				|| !map->map[i][j] || map->map[i][j] == ' ')
				int_map[i][j] = 2;
			else if (map->map[i][j] == '1')
				int_map[i][j] = 1;
			else
				int_map[i][j] = 0;
			j++;
		}
		i++;
	}
	return (int_map);
}

void	init_map(t_map *map)
{
	map->pos[0] = 0;
	map->pos[1] = 0;
	map->dir = 0;
	map->NO_Wall = NULL;
	map->SO_Wall = NULL;
	map->WE_Wall = NULL;
	map->EA_Wall = NULL;
	map->floor = 0;
	map->sky = 0;
	map->player = 0;
	map->error = 0;
	map->length = 0;
	map->height = 0;
}

void	show_map(int **int_map, t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->length)
		{
			ft_dprintf(2, "%d", int_map[i][j]);
			j++;
		}
		ft_dprintf(2, "\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		**int_map;

	int_map = NULL;
	if (argc != 2)
	{
		ft_dprintf(2, "Error\nUsage: %s [map_path]\n", argv[0]);
		return (1);
	}
	init_map(&map);
	check_format_type(argv);
	parsing(&map, argv[1]);
	if (map.error)
		free_exit(&map);
	count_height_and_length(&map);
	int_map = init_int_map(&map);
	start_project(&map, int_map);
	ft_free(&map);
	return (0);
}
