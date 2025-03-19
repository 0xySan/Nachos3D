#ifndef NACHOS3D_H
#define NACHOS3D_H

# include "../ft_dprintf/ft_printf.h"
# include "../gnl/get_next_line.h"
# include "../minilibx/mlx42.h"
# include "../libft/libft.h"
# include "math.h"

#define speed		0.1
#define rotSpeed	0.1
#define s_height	1080
#define s_width		1920
#define	pixel_tex	64

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

void show_map(int **int_map, t_map *map);
void	free_tab(t_map *map, int **tab);

// Raycasting parts:
typedef struct s_raycasting
{
	int			**map;
	double		x;
	double		y;
	double		v_x;
	double		v_y;
	double		plane_x;
	double		plane_y;
	double		raydirx;
	double		raydiry;
	double		camerax;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	int			stepy;
	int			stepx;
	int			hit;
	int			side;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			drawstart;
	int			drawend;
	double		wallx;
	int			texx;
	double		step;
	int			texnum;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_map		*settings;
	uint32_t	(*buffer)[1920];
	uint32_t	(*texture)[4096];
}	t_raycasting;

void	key_hook(mlx_key_data_t keydata, void *param);
void	raycasting(void *param);
void	loadImage(uint32_t texture[pixel_tex * pixel_tex], const char *filename);
void	drawBuffer(uint32_t buffer[s_height][s_width], mlx_image_t *image);
void	hit_side(t_raycasting *data);
void	wall_direction(int linewidth, t_raycasting *data);
void	if_choice(t_raycasting *data);
void	raydirection(t_raycasting *data);
void	draw_extrem(t_raycasting *data);

void	parsing(t_map *map, char *path);
int		check_walls(char **map);
void	write_map(t_map *map, char *path, int len);
void	free_exit(t_map *map);
void	ft_exit(int i);
void	ft_free(t_map *map);

void	start_project(t_map *map, int **mapping);

#endif
