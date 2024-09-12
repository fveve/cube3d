/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:11:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 20:36:49 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	if_collec_loop1(t_data *data, int *tex_index2, int *collectible_index)
{
	*collectible_index = find_collectible_at(data->bonus_data,
			data->trace_data->mapx, data->trace_data->mapy);
	if (*collectible_index != -1 && data->bonus_data->collectibles
		[*collectible_index].is_collected == 0)
	{
		*tex_index2 = 5;
		data->trace_data->hit = 0;
	}
}

void	set_the_hit_loop1(t_data *data, int *tex_index2, int collectible_index,
	char current_tile)
{
	if (data->trace_data->sidedistx < data->trace_data->sidedisty)
	{
		data->trace_data->sidedistx += data->trace_data->deltadistx;
		data->trace_data->mapx += data->trace_data->stepx;
		data->trace_data->side = 0;
	}
	else
	{
		data->trace_data->sidedisty += data->trace_data->deltadisty;
		data->trace_data->mapy += data->trace_data->stepy;
		data->trace_data->side = 1;
	}
	current_tile = data->map_data->map[data->trace_data->mapx]
	[data->trace_data->mapy];
	if (current_tile == '1')
		data->trace_data->hit = 1;
	else if (current_tile == 'D')
		if_door_loop2(data);
	else if (current_tile == 'C')
		if_collec_loop1(data, tex_index2, &collectible_index);
	else if (current_tile == 'Z')
		if_ennemy_loop1(data, tex_index2, &collectible_index);
}

void	dda_loop(t_data *data, int *tex_index2)
{
	char	current_tile;
	int		collectible_index;

	current_tile = '0';
	collectible_index = 0;
	while (data->trace_data->hit == 0)
		set_the_hit_loop1(data, tex_index2, collectible_index, current_tile);
}

void	calculate_distance1_part1(t_data *data)
{
	if (data->trace_data->side == 0)
		data->trace_data->perpwalldist = (data->trace_data->sidedistx
				- data->trace_data->deltadistx);
	else
		data->trace_data->perpwalldist = (data->trace_data->sidedisty
				- data->trace_data->deltadisty);
	data->trace_data->lineheight = (int)(SCREEN_HEIGHT
			/ data->trace_data->perpwalldist);
	data->trace_data->drawstart = -data->trace_data->lineheight
		/ 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawstart < 0)
		data->trace_data->drawstart = 0;
	data->trace_data->drawend = data->trace_data->lineheight
		/ 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawend >= SCREEN_HEIGHT)
		data->trace_data->drawend = SCREEN_HEIGHT - 1;
	if (data->trace_data->side == 0)
		data->trace_data->wallx = data->map_data->pos_y
			+ data->trace_data->perpwalldist * data->trace_data->raydiry;
	else
		data->trace_data->wallx = data->map_data->pos_x
			+ data->trace_data->perpwalldist * data->trace_data->raydirx;
}

void	calculate_distance(t_data *data)
{
	calculate_distance1_part1(data);
	data->trace_data->wallx -= floor(data->trace_data->wallx);
	data->trace_data->texx = (int)(data->trace_data->wallx * (double)TEX_WIDTH);
	if (data->trace_data->side == 0 && data->trace_data->raydirx > 0)
		data->trace_data->texx = TEX_WIDTH - data->trace_data->texx - 1;
	if (data->trace_data->side == 1 && data->trace_data->raydiry < 0)
		data->trace_data->texx = TEX_HEIGHT - data->trace_data->texx - 1;
	data->trace_data->step = 1.0 * TEX_HEIGHT / data->trace_data->lineheight;
	data->trace_data->texpos = (data->trace_data->drawstart - SCREEN_HEIGHT
			/ 2 + data->trace_data->lineheight / 2) * data->trace_data->step;
}
