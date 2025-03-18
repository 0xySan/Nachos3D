/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaquet <etaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:45:47 by etaquet           #+#    #+#             */
/*   Updated: 2025/03/18 16:04:18 by etaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nachos3d.h"

static int	check_neighbors(char **map, int rows, int i, int j)
{
	int	neighbor_len;

	if (i - 1 < 0)
		return (-1);
	neighbor_len = ft_strlen(map[i - 1]);
	if (j >= neighbor_len || map[i - 1][j] == ' ')
		return (-1);
	if (i + 1 >= rows)
		return (-1);
	neighbor_len = ft_strlen(map[i + 1]);
	if (j >= neighbor_len || map[i + 1][j] == ' ')
		return (-1);
	if (j - 1 < 0 || map[i][j - 1] == ' ')
		return (-1);
	neighbor_len = ft_strlen(map[i]);
	if (j + 1 >= neighbor_len || map[i][j + 1] == ' ')
		return (-1);
	return (0);
}

static int	check_line(char **map, int i, int rows)
{
	int		j;
	int		len;
	char	cell;

	j = 0;
	len = ft_strlen(map[i]);
	while (j < len)
	{
		cell = map[i][j];
		if (cell != '1' && cell != ' ')
		{
			if (check_neighbors(map, rows, i, j) == -1)
				return (-1);
		}
		j++;
	}
	return (0);
}

int	check_walls(char **map)
{
	int	rows;
	int	i;

	if (!map)
		return (-1);
	rows = 0;
	while (map[rows])
		rows++;
	if (rows == 0)
		return (-1);
	i = 0;
	while (i < rows)
	{
		if (check_line(map, i, rows) == -1)
			return (-1);
		i++;
	}
	return (0);
}
