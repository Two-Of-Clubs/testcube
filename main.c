/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbenmou <abbenmou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:09:56 by abbenmou          #+#    #+#             */
/*   Updated: 2025/12/10 19:42:43 by abbenmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char *map[] = {
	"111111111111111111111111111111111111111111",
	"100000000000000000000000000000000000000001",
	"101111111110000011111111100000111111111101",
	"101000000010000010000000100000100000001101",
	"101011111011111011101110111110111011101101",
	"101010001000001010100010100010100010101101",
	"101011101111101011101110111010111011101101",
	"101000100000001000000000100010100000001101",
	"101110111011111011111110111011111011101101",
	"100000000000000000000000000000000000000001",
	"101111111111111111111111111111111111111101",
	"100000000000000000000000000000000000000001",
	"111111111111111111111111111111111111111111",
	NULL
};

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t	map_len(char **map)
{
	size_t	i;

	if (!map)
		return 0;
	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

void	init_mlx(t_game *game)
{
	game->win_height = 500;
	game->win_width = 500;
	
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3d");
	game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	game->addr = mlx_get_data_addr(game->img, &(game->bits_per_pixel), &(game->line_length), &(game->endian));
}
void render_img(t_game *game, t_player *player)
{
    int map_w = ft_strlen(map[0]);
    int map_h = map_len(map);
    float cell_w = (float)game->win_width / map_w;
    float cell_h = (float)game->win_height / map_h;
    int px = player->x * cell_w;
    int py = player->y * cell_h;
    for (int i = 0; i < game->win_height; i++)
    {
        int y = i / cell_h;
        for (int j = 0; j < game->win_width; j++)
        {
            int x = j / cell_w;
            int color;
            if (map[y][x] == '1')
                color = 0x0000FF;
            else
                color = 0x000000;
            if (i == py && j == px)
                color = 0x00FF00;
            *(int *)(game->addr + i * game->line_length
                + j * (game->bits_per_pixel / 8)) = color;
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	castray_helper(t_dda *dda, t_program_data *data)
{
	dda->delta_x = fabs(1.0 / dda->x_raydir);
	dda->delta_y = fabs(1.0 / dda->y_raydir);
	if (dda->x_raydir < 0)
	{
		dda->step_x = -1;
		dda->x_axis_dist = (data->player->x - dda->x_map) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->x_axis_dist = (dda->x_map + 1.0 - data->player->x) * dda->delta_x;
	}
	if (dda->y_raydir < 0)
	{
		dda->step_y = -1;
		dda->y_axis_dist = (data->player->y - dda->y_map) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->y_axis_dist = (dda->y_map + 1.0 - data->player->y) * dda->delta_y;
	}
}
void	dda_loop(t_dda *dda)
{
	int wall;
	
	wall = 0;
	while (!wall)
	{
		if (dda->x_axis_dist < dda->y_axis_dist)
		{
			dda->x_axis_dist += dda->delta_x;
			dda->x_map += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->y_axis_dist += dda->delta_y;
			dda->y_map += dda->step_y;
			dda->side = 1;
		}
		if (map[dda->y_map][dda->x_map] == '1')
			wall = 1;
	}
	if (wall == 0)
		dda->perp_wall_dist = dda->x_axis_dist - dda->delta_x;
	else
		dda->perp_wall_dist = dda->y_axis_dist - dda->delta_y;
}
void castray(t_program_data *data)
{
	t_dda dda;
	int i;
	
	i = 0;
	while (i < data->game->win_width)
	{
		dda.ray_ratio = 2 * (double)i / data->game->win_width - 1;
		dda.x_raydir = data->player->dir_x + data->player->plane_x * dda.ray_ratio;
		dda.y_raydir = data->player->dir_y + data->player->plane_y * dda.ray_ratio;
		castray_helper(&dda, data);
		dda_loop(&dda);
		int linehight = (int)(data->game->win_height / dda.perp_wall_dist);
		int start = -linehight / 2 + data->game->win_height / 2;
		int end = linehight / 2 + data->game->win_height / 2;
	}
}

int	main(int argc, char **argv)
{
	t_program_data prog_data;
	
	prog_data.game = malloc(sizeof(t_game));
	prog_data.player = malloc(sizeof(t_player));
	prog_data.player->x = 9.00;
	prog_data.player->y = 9.00;
	prog_data.player->dir_x = 0;
	prog_data.player->dir_y = 1;
	prog_data.player->plane_x = prog_data.player->dir_y * 0.66;
	prog_data.player->plane_y = -prog_data.player->dir_x * 0.66;
	init_mlx(prog_data.game);
	render_img(prog_data.game, prog_data.player);
	mlx_hook((prog_data.game)->win , 2, 1L << 0, handle_moves, &prog_data);
	mlx_loop((prog_data.game)->mlx);
	return (0);
}
