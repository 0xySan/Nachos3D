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
	uint32_t	floor;
	int			error;
	char		**map;
	uint32_t	sky;
	char		dir;
}	t_map;

int	parsing(t_map *map, char *path);

#endif
