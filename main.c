/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbenmou <abbenmou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:09:56 by abbenmou          #+#    #+#             */
/*   Updated: 2025/12/08 15:55:19 by abbenmou         ###   ########.fr       */
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


void cast_ray(t_program_data *data)
{
	int i;
	double x_raydir;
	double y_raydir;
	double delta_x;
	double delta_y;
	int step_x, step_y;
	double ray_ratio;
	i = 0;
	while (i < data->game->win_width)
	{
		ray_ratio = 2 * (double)i / data->game->win_width - 1;
		x_raydir = data->player->dir_x + data->player->plane_x * ray_ratio;
		y_raydir = data->player->dir_y + data->player->plane_y * ray_ratio;
		delta_x = fabs(1.0 / x_raydir);
		delta_y = fabs(1.0 / y_raydir);
		if (x_raydir < 0)
			step_x = -1;
		else
			step_x = 1;
		if (y_raydir < 0)
			step_y = -1;
		else
			step_y = 1;
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
