/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaquet <etaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:01:29 by etaquet           #+#    #+#             */
/*   Updated: 2025/03/17 17:39:19 by etaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

void	write_map_helper(t_map *map, char *line, int i)
{
	char	**temp;
	char	*temp2;

	if (i == 4)
		map->EA_Wall = ft_substr(line, 3, ft_strlen(line) - 4);
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
		write_map_helper(map, line, i);
		if (i > 8)
			map->map[i - 9] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	map->map[i - 9] = NULL;
}

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
	exit(i);
}

int	count_chars_in_str(char *str, char *c)
{
	int	i;
	int	count;
	int chars;

	i = 0;
	count = 0;
	while (str[i])
	{
		chars = 0;
		while (c[chars])
		{
			if (str[i] == c[chars])
				count++;
			chars++;
		}
		i++;
	}
	return (count);
}

void	check_map_helper(int i, char *line, int *error, int *player)
{
	if (i == 1 && (ft_memcmp(line, "NO ", 3) || ft_strlen(line) <= 4))
		*error = 1;
	if (i == 2 && (ft_memcmp(line, "SO ", 3) || ft_strlen(line) <= 4))
		*error = 2;
	if (i == 3 && (ft_memcmp(line, "WE ", 3) || ft_strlen(line) <= 4))
		*error = 3;
	if (i == 4 && (ft_memcmp(line, "EA ", 3) || ft_strlen(line) <= 4))
		*error = 4;
	if (i == 6 && (ft_memcmp(line, "F ", 2) || ft_strlen(line) <= 3))
		*error = 5;
	if (i == 7 && (ft_memcmp(line, "C ", 2) || ft_strlen(line) <= 3))
		*error = 6;
	if (i > 8)
		*player += count_chars_in_str(line, "NSEW");
}

void	check_map(char *path)
{
	char	*line;
	int		fd;
	int		i;
	int		error;
	int		player;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	i = 1;
	error = 0;
	player = 0;
	while (line)
	{
		check_map_helper(i, line, &error, &player);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	if (player != 1)
		error = 7;
	if (i < 11)
		error = 8;
	ft_exit(error);
}

int	parsing(t_map *map, char *path)
{
	char	*line;
	int		fd;
	int		i;

	check_map(path);
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
	return (0);
}
