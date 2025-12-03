#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include <math.h>

#define rot 0.2

extern char *map[];

typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int win_width;
	int win_height;
} t_game;

typedef struct s_player
{
	double x;
	double y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_program_data
{
	t_game *game;
	t_player *player;
} t_program_data;

int	handle_moves(int keycode,t_program_data *data);
void	render_img(t_game *game, t_player *player);

#endif