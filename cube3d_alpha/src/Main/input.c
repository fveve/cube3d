/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:33:34 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/12 11:22:49 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	going_down(t_data *data)
{
	if (data->map_data->map[(int)(data->map_data->pos_x - data->trace_data->dirx
			* data->trace_data->movespeed)][(int)data->map_data->pos_y] != '1'
			&& (data->map_data->map[(int)(data->map_data->pos_x
			- data->trace_data->dirx * data->trace_data->movespeed)]
			[(int)data->map_data->pos_y] != 'D' || (data->map_data->map[(int)
			(data->map_data->pos_x - data->trace_data->dirx * data->trace_data
			->movespeed)][(int)data->map_data->pos_y] == 'D'
			&& data->bonus_data->door.is_open == 1)))
		data->map_data->pos_x -= data->trace_data->dirx
			* data->trace_data->movespeed;
	if (data->map_data->map[(int)data->map_data->pos_x][(int)
		(data->map_data->pos_y - data->trace_data->diry
			* data->trace_data->movespeed)]
			!= '1' && (data->map_data->map[(int)data->map_data->pos_x][(int)
			(data->map_data->pos_y - data->trace_data->diry
			* data->trace_data->movespeed)] != 'D' || (data->map_data->map
			[(int)data->map_data->pos_x][(int)(data->map_data->pos_y
			- data->trace_data->diry * data->trace_data->movespeed)] == 'D'
			&& data->bonus_data->door.is_open == 1)))
		data->map_data->pos_y -= data->trace_data->diry
			* data->trace_data->movespeed;
	collect_item(data);
	ft_check_if_ennemy(data);
	enter_the_vortex(data);
}

void	going_up(t_data *data)
{
	if (data->map_data->map[(int)(data->map_data->pos_x + data->trace_data->dirx
			* data->trace_data->movespeed)][(int)data->map_data->pos_y] != '1'
			&& (data->map_data->map[(int)(data->map_data->pos_x
			+ data->trace_data->dirx * data->trace_data->movespeed)]
			[(int)data->map_data->pos_y] != 'D' || (data->map_data->map[(int)
			(data->map_data->pos_x + data->trace_data->dirx
			* data->trace_data->movespeed)][(int)data->map_data->pos_y] == 'D'
			&& data->bonus_data->door.is_open == 1)))
		data->map_data->pos_x += data->trace_data->dirx
			* data->trace_data->movespeed;
	if (data->map_data->map[(int)data->map_data->pos_x]
		[(int)(data->map_data->pos_y + data->trace_data->diry
			* data->trace_data->movespeed)] != '1'
			&& (data->map_data->map[(int)data->map_data->pos_x]
		[(int)(data->map_data->pos_y + data->trace_data->diry
			* data->trace_data->movespeed)] != 'D'
			|| (data->map_data->map[(int)data->map_data->pos_x]
		[(int)(data->map_data->pos_y + data->trace_data->diry
			* data->trace_data->movespeed)] == 'D'
			&& data->bonus_data->door.is_open == 1)))
		data->map_data->pos_y += data->trace_data->diry
			*data->trace_data->movespeed;
	collect_item(data);
	ft_check_if_ennemy(data);
	enter_the_vortex(data);
}

void	going_left(t_data *data)
{
	if (data->map_data->map[(int)(data->map_data->pos_x - data->trace_data->diry
			* data->trace_data->movespeed)][(int)data->map_data->pos_y] != '1'
			&& (data->map_data->map[(int)(data->map_data->pos_x
			- data->trace_data->diry * data->trace_data->movespeed)]
			[(int)data->map_data->pos_y] != 'D' || (data->map_data->map[(int)
			(data->map_data->pos_x - data->trace_data->diry
			* data->trace_data->movespeed)][(int)data->map_data->pos_y] == 'D'
			&& data->bonus_data->door.is_open == 1)))
		data->map_data->pos_x -= data->trace_data->diry
			* data->trace_data->movespeed;
	if (data->map_data->map[(int)data->map_data->pos_x][(int)
		(data->map_data->pos_y + data->trace_data->dirx
			*data->trace_data->movespeed)] != '1' && (data->map_data->map
			[(int)data->map_data->pos_x][(int)(data->map_data->pos_y
			+ data->trace_data->dirx * data->trace_data->movespeed)] != 'D'
			|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y + data->trace_data->dirx
			*data->trace_data->movespeed)] == 'D'
			&& data->bonus_data->door.is_open == 1)))
		data->map_data->pos_y += data->trace_data->dirx
			* data->trace_data->movespeed;
	collect_item(data);
	ft_check_if_ennemy(data);
	enter_the_vortex(data);
}

void	going_right(t_data *data)
{
	if (data->map_data->map[(int)(data->map_data->pos_x + data->trace_data->diry
			* data->trace_data->movespeed)][(int)data->map_data->pos_y] != '1'
			&& (data->map_data->map[(int)(data->map_data->pos_x
			+ data->trace_data->diry * data->trace_data->movespeed)]
			[(int)data->map_data->pos_y] != 'D' || (data->map_data->map[(int)
			(data->map_data->pos_x + data->trace_data->diry
			* data->trace_data->movespeed)][(int)data->map_data->pos_y] == 'D'
			&& data->bonus_data->door.is_open == 1)))
		data->map_data->pos_x += data->trace_data->diry
			* data->trace_data->movespeed;
	if (data->map_data->map[(int)data->map_data->pos_x][(int)
		(data->map_data->pos_y - data->trace_data->dirx
			* data->trace_data->movespeed)] != '1' && (data->map_data->map
			[(int)data->map_data->pos_x][(int)(data->map_data->pos_y
			- data->trace_data->dirx * data->trace_data->movespeed)] != 'D'
			|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y - data->trace_data->dirx
			* data->trace_data->movespeed)] == 'D'
			&& data->bonus_data->door.is_open == 1)))
		data->map_data->pos_y -= data->trace_data->dirx
			*data->trace_data->movespeed;
	collect_item(data);
	ft_check_if_ennemy(data);
	enter_the_vortex(data);
}

int	input(int key, t_data *data)
{
	mlx_do_key_autorepeaton(data->mlx_data->mlx);
	if (key == KEY_UP || key == KEY_W)
		going_up(data);
	if (key == KEY_DOWN || key == KEY_S)
		going_down(data);
	if (key == KEY_A)
		going_left(data);
	if (key == KEY_D)
		going_right(data);
	if (key == KEY_RIGHT)
		camera_right(data);
	if (key == KEY_LEFT)
		camera_left(data);
	if (key == KEY_ESCAPE)
		exit_manager(data);
	if (key == 32)
		open_close_thedoor(data);
	return (0);
}
