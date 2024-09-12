/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_trace_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:53:38 by arafa             #+#    #+#             */
/*   Updated: 2024/09/10 16:19:58 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_trace_data2(t_map_data *map_data,
		t_trace_data *data, t_mlx_data *mlx_data)
{
	data->camerax = 0;
	data->raydirx = 0;
	data->raydiry = 0;
	data->mapx = (int)map_data->pos_x;
	data->mapy = (int)map_data->pos_y;
	data->deltadistx = 0;
	data->deltadisty = 0;
	data->perpwalldist = 0;
	data->stepx = 0;
	data->stepy = 0;
	data->hit = 0;
	data->side = 0;
	data->lineheight = 0;
	data->drawstart = 0;
	data->drawend = 0;
	data->olddirx = 0;
	data->oldplanex = 0;
	data->movespeed = 0.09;
	data->rotspeed = 0.05;
	data->map_data = map_data;
	data->mlx_data = mlx_data;
}

void	init_trace_data4(t_trace_data *data)
{
	data->dirx = 0;
	data->diry = -1;
	data->planex = -0.55;
	data->planey = 0;
}

void	init_trace_data3(t_map_data *map_data, t_trace_data *data)
{
	if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'W')
		init_trace_data4(data);
	else if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'E')
	{
		data->dirx = 0;
		data->diry = 1;
		data->planex = 0.55;
		data->planey = 0;
	}
	else if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'N')
	{
		data->dirx = -1;
		data->diry = 0;
		data->planex = 0;
		data->planey = 0.55;
	}
	else
	{
		data->dirx = 1;
		data->diry = 0;
		data->planex = 0;
		data->planey = -0.55;
	}
}

void	init_trace_data(t_map_data *map_data,
		t_trace_data *data, t_mlx_data *mlx_data)
{
	init_trace_data2(map_data, data, mlx_data);
	data->h = 0;
	data->w = 0;
	data->texx = 0;
	data->color = 0;
	data->texy = 0;
	data->texpos = 0;
	data->prev_mouse_x = SCREEN_WIDTH / 2;
	data->mouse_initialized = 0;
	init_trace_data3(map_data, data);
}
