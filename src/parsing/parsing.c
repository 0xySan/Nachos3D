/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaquet <etaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:01:29 by etaquet           #+#    #+#             */
/*   Updated: 2025/03/18 15:52:01 by etaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

void	count_chars_in_str(char *str, char *c, t_map *map, int i)
{
	int	j;
	int	chars;

	j = 0;
	while (str[j])
	{
		chars = 0;
		while (c[chars])
		{
			if (str[j] == c[chars])
			{
				map->dir = c[chars];
				map->player++;
				map->pos[0] = j;
				map->pos[1] = i - 9;
			}
			chars++;
		}
		j++;
	}
}

void	check_map_helper(int i, char *line, t_map *map)
{
	if (i == 1 && (ft_memcmp(line, "NO ", 3) || ft_strlen(line) <= 4))
		map->error = 1;
	if (i == 2 && (ft_memcmp(line, "SO ", 3) || ft_strlen(line) <= 4))
		map->error = 2;
	if (i == 3 && (ft_memcmp(line, "WE ", 3) || ft_strlen(line) <= 4))
		map->error = 3;
	if (i == 4 && (ft_memcmp(line, "EA ", 3) || ft_strlen(line) <= 4))
		map->error = 4;
	if (i == 6 && (ft_memcmp(line, "F ", 2) || ft_strlen(line) <= 3))
		map->error = 5;
	if (i == 7 && (ft_memcmp(line, "C ", 2) || ft_strlen(line) <= 3))
		map->error = 6;
	if (i > 8)
		count_chars_in_str(line, "NSEW", map, i);
}

void	check_map(char *path, t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	i = 1;
	while (line)
	{
		check_map_helper(i, line, map);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	if (map->player != 1)
		map->error = 7;
	if (i < 11)
		map->error = 8;
	ft_exit(map->error);
}

int	parsing(t_map *map, char *path)
{
	char	*line;
	int		fd;
	int		i;

	check_map(path, map);
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
	close(fd);
	write_map(map, path, i);
	if (check_walls(map->map) == -1)
		map->error = 9;
	return (0);
}
