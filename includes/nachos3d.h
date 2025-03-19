#ifndef NACHOS3D_H
#define NACHOS3D_H

# include "../ft_dprintf/ft_printf.h"
# include "../gnl/get_next_line.h"
# include "../minilibx/mlx42.h"
# include "../libft/libft.h"

typedef struct s_map
{
	char		*NO_Wall;
	char		*SO_Wall;
	char		*WE_Wall;
	char		*EA_Wall;
	int			player;
	int			pos[2];
	size_t		length;
	size_t		height;
	uint32_t	floor;
	int			error;
	char		**map;
	uint32_t	sky;
	char		dir;
}	t_map;

void	parsing(t_map *map, char *path);
int		check_walls(char **map);
void	write_map(t_map *map, char *path, int len);
void	free_exit(t_map *map);
void	ft_exit(int i);
void	ft_free(t_map *map);

#endif
