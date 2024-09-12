/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:11:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 20:39:13 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_ray2b(t_data *data)
{
	if (data->trace_data->raydirx < 0)
	{
		data->trace_data->stepx = -1;
		data->trace_data->sidedistx = (data->map_data->pos_x
				- data->trace_data->mapx) * data->trace_data->deltadistx;
	}
	else
	{
		data->trace_data->stepx = 1;
		data->trace_data->sidedistx = (data->trace_data->mapx + 1.0
				- data->map_data->pos_x) * data->trace_data->deltadistx;
	}
	if (data->trace_data->raydiry < 0)
	{
		data->trace_data->stepy = -1;
		data->trace_data->sidedisty = (data->map_data->pos_y
				- data->trace_data->mapy) * data->trace_data->deltadisty;
	}
	else
	{
		data->trace_data->stepy = 1;
		data->trace_data->sidedisty = (data->trace_data->mapy
				+ 1.0 - data->map_data->pos_y) * data->trace_data->deltadisty;
	}
}

void	init_ray2(t_data *data, int x)
{
	data->trace_data->camerax = (2 * x / (double)SCREEN_WIDTH - 1)
		* (SCREEN_WIDTH / (double)SCREEN_HEIGHT);
	data->trace_data->raydirx = data->trace_data->dirx
		+ data->trace_data->planex * data->trace_data->camerax;
	data->trace_data->raydiry = data->trace_data->diry
		+ data->trace_data->planey * data->trace_data->camerax;
	data->trace_data->mapx = (int)data->map_data->pos_x;
	data->trace_data->mapy = (int)data->map_data->pos_y;
	if (data->trace_data->raydirx == 0)
		data->trace_data->deltadistx = 1e30;
	else
		data->trace_data->deltadistx = ft_abs(1 / data->trace_data->raydirx);
	if (data->trace_data->raydiry == 0)
		data->trace_data->deltadisty = 1e30;
	else
		data->trace_data->deltadisty = ft_abs(1 / data->trace_data->raydiry);
	data->trace_data->hit = 0;
	init_ray2b(data);
}

void	if_ennemy_loop2(t_data *data, int *tex_index2, int *collectible_index)
{
	*collectible_index = find_ennemy_at(data->bonus_data,
			data->trace_data->mapx, data->trace_data->mapy);
	if (*collectible_index != -1 && data->bonus_data->enemies
		[*collectible_index].is_alive == 1)
	{
		*tex_index2 = 4;
		data->trace_data->hit = 1;
	}
}

void	if_collec_loop2(t_data *data, int *tex_index2, int *collectible_index)
{
	*collectible_index = find_collectible_at(data->bonus_data,
			data->trace_data->mapx, data->trace_data->mapy);
	if (*collectible_index != -1 && data->bonus_data->collectibles
		[*collectible_index].is_collected == 0)
	{
		*tex_index2 = 5;
		data->trace_data->hit = 1;
	}
}
