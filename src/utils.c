/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:59:24 by tle-goff          #+#    #+#             */
/*   Updated: 2025/03/19 19:59:42 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nachos3d.h"

void	free_tab(t_map *map, int **tab)
{
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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
