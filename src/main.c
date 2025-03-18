/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaquet <etaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:38:50 by etaquet           #+#    #+#             */
/*   Updated: 2025/03/18 16:03:47 by etaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nachos3d.h"

void	check_format_type(char **argv)
{
	char		*file_ext;

	file_ext = ft_substr(argv[1],
			ft_strlen(argv[1]) - 4, ft_strlen(argv[1]));
	if (ft_memcmp(file_ext, ".cub", 4))
	{
		free(file_ext);
		ft_dprintf(2, "Error\nFormat usage : [map_file.cub] not [%s]\n",
			argv[1]);
		exit(1);
	}
	free(file_ext);
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
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		ft_dprintf(2, "Error\nUsage: %s [map_path]\n", argv[0]);
		return (1);
	}
	init_map(&map);
	check_format_type(argv);
	if (parsing(&map, argv[1]))
		return (1);
	if (map.error)
		free_exit(&map);
	ft_free(&map);
	return (0);
}
