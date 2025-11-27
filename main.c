/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbenmou <abbenmou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:09:56 by abbenmou          #+#    #+#             */
/*   Updated: 2025/11/27 18:19:11 by abbenmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char *map[] = {
	"111111111111111111111111111111111111111111", // 42 chars
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
	game->win_height = 800;
	game->win_width = 800;
	
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3d");
	game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	game->addr = mlx_get_data_addr(game->img, &(game->bits_per_pixel), &(game->line_length), &(game->endian));
}
void	render_img(t_game *game, t_player *player)
{
	int i = -1, j = -1;
	int x, y;

	while (++i < game->win_height)
	{
		y = (int)((float)i / game->win_height * map_len(map));

		while (++j < game->win_width)
		{
			x = (int)((float)j / game->win_width * ft_strlen(map[y]));


			int px = (float)player->x / ft_strlen(map[y]) * game->win_width;

			int py = (float)player->y / map_len(map) * game->win_height;

			int psize = game->win_width / ft_strlen(map[0]);
			int ksize = game->win_height / map_len(map);

			if (i > py && i < py + psize && j -1 > px && j <= px + psize)
			{
				*(int *)(game->addr + i * game->line_length
					+ j * (game->bits_per_pixel / 8)) = 0x00FF00;
			}
			else if (map[y][x] == '1')
				*(int *)(game->addr + i * game->line_length
					+ j * (game->bits_per_pixel / 8)) = 0x0000FF;

			else
				*(int *)(game->addr + i * game->line_length
					+ j * (game->bits_per_pixel / 8)) = 0x000000;

			
		}
		j = -1;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);     // x = 3    y = 6 .5  *32 
}

int	handle_moves(int keycode,t_program_data *data)
{
	double	new_x, new_y;
	printf("key == %d\n", keycode);

	if (keycode == 119)//w
	{
		new_x = data->player->x + data->player->dir_x * 0.05;
		new_y = data->player->y + data->player->dir_y * 0.05;

		if (map[(int)new_y][(int)new_x] == '1')
			return 1;
		data->player->x = new_x;
		data->player->y = new_y;
	}
	if (keycode == 115)//s
	{
		new_x = data->player->x - data->player->dir_x * 0.05;
		new_y = data->player->y - data->player->dir_y * 0.05;

		if (map[(int)new_y][(int)new_x] == '1')
			return 1;
		data->player->x = new_x;
		data->player->y = new_y;
	}
	if (keycode == 97)//a
	{
		new_x = data->player->x - data->player->dir_y * 0.05;
		new_y = data->player->y + data->player->dir_x * 0.05;
		
		if (map[(int)new_y][(int)new_x] == '1')
			return 1;
		data->player->x = new_x;
		data->player->y = new_y;
	}
	if (keycode == 100)//d
	{
		new_x = data->player->x + data->player->dir_y * 0.05;
		new_y = data->player->y - data->player->dir_x * 0.05;
		
		if (map[(int)new_y][(int)new_x] == '1')
			return 1;
		data->player->x = new_x;
		data->player->y = new_y;
	}
	if (keycode == 65363)
	{
		data->player->dir_x = data->player->dir_x * cos(0.05) - data->player->dir_y * sin(0.05);
		data->player->dir_y = data->player->dir_x * sin(0.05) + data->player->dir_y * cos(0.05);
	}
	if (keycode == 65361)
	{
		data->player->dir_x = data->player->dir_x * cos(-0.05) - data->player->dir_y * sin(-0.05);
		data->player->dir_y = data->player->dir_x * sin(-0.05) + data->player->dir_y * cos(-0.05); 
	}
	render_img(data->game, data->player);
	return 0;
}
int	main(int argc, char **argv)
{
	t_program_data prog_data;
	
	prog_data.game = malloc(sizeof(t_game));
	prog_data.player = malloc(sizeof(t_player));
	prog_data.player->x = 9.00;
	prog_data.player->y = 9.00;
	prog_data.player->dir_x = -1;
	prog_data.player->dir_y = 0;
	init_mlx(prog_data.game);
	render_img(prog_data.game, prog_data.player);
	mlx_hook((prog_data.game)->win , 2, 1L << 0, handle_moves, &prog_data);
	mlx_loop((prog_data.game)->mlx);
	return (0);
}
