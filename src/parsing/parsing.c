/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaquet <etaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:01:29 by etaquet           #+#    #+#             */
/*   Updated: 2025/03/17 16:51:12 by etaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

void	write_map_helper(t_map *map, char *line, int i)
{
	char	**temp;
	char	*temp2;

	if (i == 6)
	{
		temp = ft_split(line, ',');
		temp2 = ft_substr(temp[0], 2, ft_strlen(temp[0]) - 1);
		map->floor[0] = ft_atoi(temp2);
		map->floor[1] = ft_atoi(temp[1]);
		map->floor[2] = ft_atoi(temp[2]);
		free(temp);
		free(temp2);
	}
	if (i == 7)
	{
		temp = ft_split(line, ',');
		temp2 = ft_substr(temp[0], 2, ft_strlen(temp[0]) - 1);
		map->sky[0] = ft_atoi(temp2);
		map->sky[1] = ft_atoi(temp[1]);
		map->sky[2] = ft_atoi(temp[2]);
		free(temp);
		free(temp2);
	}
}

void	write_map(t_map *map, char *path, int len)
{
	char	*line;
	int		fd;
	int		i;

	map->map = malloc(sizeof(char *) * (len + 1));
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	map->NO_Wall = ft_substr(line, 3, ft_strlen(line) - 4);
	i = 1;
	while (line)
	{
		if (i == 2)
			map->SO_Wall = ft_substr(line, 3, ft_strlen(line) - 4);
		if (i == 3)
			map->WE_Wall = ft_substr(line, 3, ft_strlen(line) - 4);
		if (i == 4)
			map->EA_Wall = ft_substr(line, 3, ft_strlen(line) - 4);
		write_map_helper(map, line, i);
		if (i > 8)
			map->map[i - 9] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

int	parsing(t_map *map, char *path)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "Error\nCan't open file %s\n", path);
		return (1);
	}
	line = get_next_line(fd);
	i = 1;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	line = NULL;
	close(fd);
	write_map(map, path, i);
	return (0);
}
