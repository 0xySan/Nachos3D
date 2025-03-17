#ifndef NACHOS3D_H
#define NACHOS3D_H

# include "../ft_dprintf/ft_printf.h"
# include "../gnl/get_next_line.h"
# include "../minilibx/mlx42.h"
# include "../libft/libft.h"

typedef struct t_map
{
	char	*NO_Wall;
	char	*SO_Wall;
	char	*WE_Wall;
	char	*EA_Wall;
	int		floor[3];
	int		sky[3];
	char	**map;
}	s_map;

#endif
