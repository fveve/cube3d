/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:33:34 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 18:24:58 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	mouse_move2(t_data *data, int diffx)
{
	double	rotation_speed;

	rotation_speed = data->trace_data->rotspeed * (diffx / 20.0);
	data->trace_data->olddirx = data->trace_data->dirx;
	data->trace_data->dirx = data->trace_data->dirx
		* cos(rotation_speed) - data->trace_data->diry
		* sin(rotation_speed);
	data->trace_data->diry = data->trace_data->olddirx
		* sin(rotation_speed) + data->trace_data->diry
		* cos(rotation_speed);
	data->trace_data->oldplanex = data->trace_data->planex;
	data->trace_data->planex = data->trace_data->planex
		* cos(rotation_speed) - data->trace_data->planey
		* sin(rotation_speed);
	data->trace_data->planey = data->trace_data->oldplanex
		* sin(rotation_speed) + data->trace_data->planey
		* cos(rotation_speed);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		diffx;

	(void)y;
	if (!data->trace_data->mouse_initialized)
	{
		data->trace_data->prev_mouse_x = SCREEN_WIDTH / 2;
		data->trace_data->mouse_initialized = 1;
		return (0);
	}
	diffx = data->trace_data->prev_mouse_x - x;
	if (diffx != 0)
		mouse_move2(data, diffx);
	data->trace_data->prev_mouse_x = x;
	return (0);
}

void	camera_right(t_data *data)
{
	data->trace_data->olddirx = data->trace_data->dirx;
	data->trace_data->dirx = data->trace_data->dirx
		* cos(-data->trace_data->rotspeed)
		- data->trace_data->diry
		* sin(-data->trace_data->rotspeed);
	data->trace_data->diry = data->trace_data->olddirx
		* sin(-data->trace_data->rotspeed)
		+ data->trace_data->diry * cos(-data->trace_data->rotspeed);
	data->trace_data->oldplanex = data->trace_data->planex;
	data->trace_data->planex = data->trace_data->planex
		* cos(-data->trace_data->rotspeed)
		- data->trace_data->planey * sin(-data->trace_data->rotspeed);
	data->trace_data->planey = data->trace_data->oldplanex
		* sin(-data->trace_data->rotspeed)
		+ data->trace_data->planey * cos(-data->trace_data->rotspeed);
}

void	camera_left(t_data *data)
{
	data->trace_data->olddirx = data->trace_data->dirx;
	data->trace_data->dirx = data->trace_data->dirx
		* cos(data->trace_data->rotspeed) - data->trace_data->diry
		* sin(data->trace_data->rotspeed);
	data->trace_data->diry = data->trace_data->olddirx
		* sin(data->trace_data->rotspeed) + data->trace_data->diry
		* cos(data->trace_data->rotspeed);
	data->trace_data->oldplanex = data->trace_data->planex;
	data->trace_data->planex = data->trace_data->planex
		* cos(data->trace_data->rotspeed) - data->trace_data->planey
		* sin(data->trace_data->rotspeed);
	data->trace_data->planey = data->trace_data->oldplanex
		* sin(data->trace_data->rotspeed) + data->trace_data->planey
		* cos(data->trace_data->rotspeed);
}
