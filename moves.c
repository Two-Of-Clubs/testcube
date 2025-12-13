#include "cube.h"

void handle_rotation(int keycode, t_program_data *data)
{
	double old_x;
	double len;

	old_x = data->player->dir_x;
	len = 0.00;
	if (keycode == 65363)
	{
		data->player->dir_x = old_x * cos(rot) - data->player->dir_y * sin(rot);
		data->player->dir_y = old_x * sin(rot) + data->player->dir_y * cos(rot);
	}
	else if (keycode == 65361)
	{
		data->player->dir_x = old_x * cos(rot) + data->player->dir_y * sin(rot);
		data->player->dir_y = -old_x * sin(rot) + data->player->dir_y * cos(rot);
	}
	len = sqrt(data->player->dir_x * data->player->dir_x + data->player->dir_y * data->player->dir_y);
	if (len == 0.00)
		return ;
	data->player->dir_x /= len;
	data->player->dir_y /= len;
	data->player->plane_x = data->player->dir_y * 0.66;
	data->player->plane_y = -data->player->dir_x * 0.66;
}

void	handle_ws(int keycode,t_program_data *data)
{
	double	new_x;
	double	new_y;

	if (keycode == 119)//w
	{
		new_x = data->player->x - data->player->dir_x * 0.05;
		new_y = data->player->y - data->player->dir_y * 0.05;
		if (map[(int)(new_y)][(int)data->player->x] != '1'
			&& map[(int)(new_y)][(int)data->player->x] != '1')
			data->player->y = new_y;
		if (map[(int)data->player->y][(int)(new_x)] != '1'
			&& map[(int)data->player->y][(int)(new_x)] != '1')
			data->player->x = new_x;
	}
	else if (keycode == 115)//s
	{
		new_x = data->player->x + data->player->dir_x * 0.05;
		new_y = data->player->y + data->player->dir_y * 0.05;
		if (map[(int)(new_y)][(int)data->player->x] != '1'
			&& map[(int)(new_y)][(int)data->player->x] != '1')
			data->player->y = new_y;
		if (map[(int)data->player->y][(int)(new_x)] != '1'
			&& map[(int)data->player->y][(int)(new_x)] != '1')
			data->player->x = new_x;
	}
}

void	handle_ad(int keycode,t_program_data *data)
{
	double	new_x;
	double	new_y;

	if (keycode == 97)//a
	{
		new_x = data->player->x - data->player->dir_y * 0.05;
		new_y = data->player->y + data->player->dir_x * 0.05;
		if (map[(int)(new_y)][(int)data->player->x] != '1'
			&& map[(int)(new_y)][(int)data->player->x] != '1')
			data->player->y = new_y;
		if (map[(int)data->player->y][(int)(new_x)] != '1'
			&& map[(int)data->player->y][(int)(new_x)] != '1')
			data->player->x = new_x;
	}
	else if (keycode == 100)//d
	{
		new_x = data->player->x + data->player->dir_y * 0.05;
		new_y = data->player->y - data->player->dir_x * 0.05;
		if (map[(int)(new_y)][(int)data->player->x] != '1'
			&& map[(int)(new_y)][(int)data->player->x] != '1')
			data->player->y = new_y;
		if (map[(int)data->player->y][(int)(new_x)] != '1'
			&& map[(int)data->player->y][(int)(new_x)] != '1')
			data->player->x = new_x;
	}
}

int	handle_moves(int keycode,t_program_data *data)
{
	printf("key == %d\n", keycode);	
	if (keycode == 97 || keycode == 100)
		handle_ad(keycode, data);
	else if(keycode == 115 || keycode == 119)
		handle_ws(keycode, data);
	else if (keycode == 65363 || keycode == 65361)
		handle_rotation(keycode, data);
	printf("dirx = %f || diry = %f \n",data->player->dir_x,data->player->dir_y);
	castray(data);
	// render_img(data->game, data->player);
	return 0;
}
