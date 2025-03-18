/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaquet <etaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:47:38 by etaquet           #+#    #+#             */
/*   Updated: 2025/03/18 16:01:18 by etaquet          ###   ########.fr       */
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
		map->floor = (ft_atoi(temp2) << 24 | ft_atoi(temp[1]) << 16
				| ft_atoi(temp[2]) << 8 | 255);
		ft_free_args(temp);
		free(temp2);
	}
	if (i == 7)
	{
		temp = ft_split(line, ',');
		temp2 = ft_substr(temp[0], 2, ft_strlen(temp[0]) - 1);
		map->sky = (ft_atoi(temp2) << 24 | ft_atoi(temp[1]) << 16
				| ft_atoi(temp[2]) << 8 | 255);
		ft_free_args(temp);
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
			map->map[i - 9] = ft_substr(line, 0, ft_strlen(line) - 1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	map->map[i - 9] = NULL;
}
