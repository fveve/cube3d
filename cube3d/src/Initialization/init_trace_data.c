/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_trace_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:53:38 by arafa             #+#    #+#             */
/*   Updated: 2024/09/09 13:01:10 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_trace_data2(t_map_data *map_data,
		t_trace_data *data, t_mlx_data *mlx_data)
{
	data->cameraX = 0;
	data->rayDirX = 0;
	data->rayDirY = 0;
	data->mapX = (int)map_data->pos_x;
	data->mapY = (int)map_data->pos_y;
	data->deltaDistX = 0;
	data->deltaDistY = 0;
	data->perpWallDist = 0;
	data->stepX = 0;
	data->stepY = 0;
	data->hit = 0;
	data->side = 0;
	data->lineHeight = 0;
	data->drawStart = 0;
	data->drawEnd = 0;
	data->oldDirX = 0;
	data->oldPlaneX = 0;
	data->moveSpeed = 0.09;
	data->rotSpeed = 0.05;
	data->map_data = map_data;
	data->mlx_data = mlx_data;
}

void	init_trace_data4(t_trace_data *data)
{
	data->dirX = 0;
	data->dirY = -1;
	data->planeX = -0.55;
	data->planeY = 0;
}

void	init_trace_data3(t_map_data *map_data, t_trace_data *data)
{
	if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'W')
		init_trace_data4(data);
	else if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'E')
	{
		data->dirX = 0;
		data->dirY = 1;
		data->planeX = 0.55;
		data->planeY = 0;
	}
	else if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'N')
	{
		data->dirX = -1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = 0.55;
	}
	else
	{
		data->dirX = 1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = -0.55;
	}
}

void	init_trace_data(t_map_data *map_data,
		t_trace_data *data, t_mlx_data *mlx_data)
{
	init_trace_data2(map_data, data, mlx_data);
	data->h = 0;
	data->w = 0;
	data->texX = 0;
	data->color = 0;
	data->texY = 0;
	data->texPos = 0;
	data->prev_mouse_x = SCREEN_WIDTH / 2;
	data->mouse_initialized = 0;
	//  |  Initialisation of the direction the player is facing   |
	//	V														  V
	init_trace_data3(map_data, data);
}
