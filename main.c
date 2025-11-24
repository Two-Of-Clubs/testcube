/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbenmou <abbenmou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:09:56 by abbenmou          #+#    #+#             */
/*   Updated: 2025/11/24 16:38:11 by abbenmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char *map[] = {
	"000000000000000111111111111000000000000000",
	"000000000000000000000000000000000000000000",
	"000000000111111011101110111111100000000000",
	"000000001111101011010110101111110000000000",
	"000000001111101111011110111111110000000000",
	"000000001111101011010110101111110000000000",
	"000000000111111011101110111111100000000000",
	"000000000001111111111111111110000000000000",
	"000000000000011111111111111000000000000000",
	"000000000000011110000001111000000000000000",
	"000000000000111100000000111100000000000000",
	"000000000001111111111111111110000000000000",
	"000000000001111111111111111110000000000000",
	"000000000000011111111111111000000000000000",
	"000000000000000111111111110000000000000000",
	"000000000000011111111111111000000000000000",
	"000000000001111111111111111110000000000000",
	"000000000011110000000000011111000000000000",
	"000000000111100000000000001111100000000000",
	"000000001111000000000000000111110000000000",
	"000000011111111111111111111111111000000000",
	"000000011111111111111111111111111000000000",
	"000000000111111111111111111111100000000000",
	"000000000011111111111111111111000000000000",
	"000000000001111111111111111110000000000000",
	"000000000000111111111111111100000000000000",
	"000000000000011111111111111000000000000000",
	"000000000000001111111111110000000000000000",
	"000000000000000111111111100000000000000000",
	"000000000000000000000000000000000000000000",
	"000000000000000000111100000000000000000000",
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
void	render_img(t_program_data *data)
{
	int i = -1, j = -1;
	int x, y;

	while (++i < data->game->win_height)
	{
		y = (int)((float)i / data->game->win_height * map_len(map));

		while (++j < data->game->win_width)
		{
			x = (int)((float)j / data->game->win_width * ft_strlen(map[y]));


			int px = (float)data->player->x / ft_strlen(map[y]) 
						* data->game->win_width;

			int py = (float)data->player->y / map_len(map)
						* data->game->win_height;

			int psize = data->game->win_width / ft_strlen(map[0]);

			if (i >= py && i < py + psize && j >= px && j < px + psize)
			{
				*(int *)(data->game->addr + i * data->game->line_length
					+ j * (data->game->bits_per_pixel / 8)) = 0x00FF00;
			}
			else if (map[y][x] == '1')
				*(int *)(data->game->addr + i * data->game->line_length
					+ j * (data->game->bits_per_pixel / 8)) = 0x0000FF;

			else
				*(int *)(data->game->addr + i * data->game->line_length
					+ j * (data->game->bits_per_pixel / 8)) = 0x000000;

			
		}
		j = -1;
	}
	mlx_put_image_to_window(data->game->mlx, data->game->win, data->game->img, 0, 0);
}


int	handle_moves(int keycode,t_program_data *data)
{
	printf("key == %d\n", keycode);
	if (keycode == 119)
	{
		data->player->y -= 0.05;
	}
	if (keycode == 115)
	{
		data->player->y += 0.05;
	}
	if (keycode == 97)
	{
		data->player->x -= 0.05;
	}
	if (keycode == 100)
	{
		data->player->x += 0.05;
	}
	render_img(data);
	return 0;
}
int	main(int argc, char **argv)
{
	t_program_data prog_data;
	
	prog_data.game = malloc(sizeof(t_game));
	prog_data.player = malloc(sizeof(t_player));
	prog_data.player->x = 9.00;
	prog_data.player->y = 9.00;
	init_mlx(prog_data.game);
	render_img(&prog_data);
	mlx_hook((prog_data.game)->win , 2, 1L << 0, handle_moves, &prog_data);
	mlx_loop((prog_data.game)->mlx);
	return (0);
}
