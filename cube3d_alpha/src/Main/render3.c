/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:11:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 20:38:17 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_column2(t_data *data, int x, int tex_index2)
{
	int	y;

	if (tex_index2 != -1)
	{
		y = data->trace_data->drawstart;
		while (y < data->trace_data->drawend)
		{
			data->trace_data->texy = (int)data->trace_data->texpos
				& (TEX_HEIGHT - 1);
			data->trace_data->texpos += data->trace_data->step;
			data->trace_data->color = get_pixel(data->mlx_data->texture
				[tex_index2], data->trace_data->texx, data->trace_data->texy);
			if (!is_near_green(data->trace_data->color, 110))
				data->trace_data->buffer[y][x] = data->trace_data->color;
			y++;
		}
	}
}

void	clear_buffer(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			data->trace_data->buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	init_ray_part1(t_data *data)
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
		data->trace_data->sidedisty = (data->trace_data->mapy + 1.0
				- data->map_data->pos_y) * data->trace_data->deltadisty;
	}
}

void	init_ray(t_data *data, int x)
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
	init_ray_part1(data);
}

void	if_ennemy_loop1(t_data *data, int *tex_index2, int *collectible_index)
{
	*collectible_index = find_ennemy_at(data->bonus_data,
			data->trace_data->mapx, data->trace_data->mapy);
	if (*collectible_index != -1 && data->bonus_data->enemies
		[*collectible_index].is_alive == 1)
	{
		*tex_index2 = 4;
		data->trace_data->hit = 0;
	}
}
