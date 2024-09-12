/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:11:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 20:36:11 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_column(t_data *data, int x, int tex_index)
{
	int	y;

	y = 0;
	while (y < data->trace_data->drawstart)
	{
		data->trace_data->buffer[y][x] = data->map_data->f_color;
		y++;
	}
	y = data->trace_data->drawstart;
	while (y < data->trace_data->drawend)
	{
		data->trace_data->texy = (int)data->trace_data->texpos
			& (TEX_HEIGHT - 1);
		data->trace_data->texpos += data->trace_data->step;
		data->trace_data->color = get_pixel(data->mlx_data->texture[tex_index],
				data->trace_data->texx, data->trace_data->texy);
		if (data->trace_data->side == 1)
			data->trace_data->color = (data->trace_data->color >> 1) & 8355711;
		data->trace_data->buffer[y][x] = data->trace_data->color;
		y++;
	}
	y--;
	while (++y < SCREEN_HEIGHT)
		data->trace_data->buffer[y][x] = data->map_data->c_color;
}

void	chooze_text_2(t_data *data, int *tex_index, int collectible_index,
	int ennemy_index)
{
	if (data->trace_data->side == 0 && data->trace_data->stepx == 1)
		*tex_index = 0;
	else if (data->trace_data->side == 0 && data->trace_data->stepx == -1)
		*tex_index = 1;
	else if (data->trace_data->side == 1 && data->trace_data->stepy == 1)
		*tex_index = 3;
	else if (data->trace_data->side == 1 && data->trace_data->stepy == -1)
		*tex_index = 2;
	if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
		== 'D' && data->bonus_data->door.is_open == 0)
		*tex_index = 6;
	if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
		== 'D' && data->bonus_data->door.is_open == 1)
		*tex_index = get_door_texture_animation(data);
	collectible_index = find_collectible_at(data->bonus_data,
			data->trace_data->mapx, data->trace_data->mapy);
	ennemy_index = find_ennemy_at(data->bonus_data,
			data->trace_data->mapx, data->trace_data->mapy);
	if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
		== 'C' && data->bonus_data->collectibles
		[collectible_index].is_collected == 0)
		*tex_index = 5;
	if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
		== 'Z' && data->bonus_data->enemies[ennemy_index].is_alive == 1)
		*tex_index = 4;
}

void	chooze_text_1(t_data *data, int *tex_index)
{
	if (data->trace_data->side == 0 && data->trace_data->stepx == 1)
		*tex_index = 0;
	else if (data->trace_data->side == 0 && data->trace_data->stepx == -1)
		*tex_index = 1;
	else if (data->trace_data->side == 1 && data->trace_data->stepy == 1)
		*tex_index = 3;
	else if (data->trace_data->side == 1 && data->trace_data->stepy == -1)
		*tex_index = 2;
	if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
		== 'D' && data->bonus_data->door.is_open == 0)
		*tex_index = 6;
	if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
		== 'D' && data->bonus_data->door.is_open == 1)
		*tex_index = get_door_texture_animation(data);
}

void	chooze_text_loop1_and_2(t_data *data, int *tex_index,
	int *collectible_index, int *ennemy_index)
{
	int	x;
	int	tex_index2;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		tex_index2 = -1;
		init_ray(data, x);
		dda_loop(data, &tex_index2);
		calculate_distance(data);
		chooze_text_1(data, tex_index);
		render_column(data, x, *tex_index);
		x++;
	}
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray2(data, x);
		dda_loop2(data, &tex_index2);
		calculate_distance2(data);
		chooze_text_2(data, tex_index, *collectible_index, *ennemy_index);
		render_column2(data, x, *tex_index);
		x++;
	}
}

int	ft_render(t_data *data)
{
	int	tex_index;
	int	collectible_index;
	int	ennemy_index;

	ennemy_index = 0;
	collectible_index = 0;
	chooze_text_loop1_and_2(data, &tex_index, &collectible_index,
		&ennemy_index);
	draw_buffer(data->trace_data);
	clear_buffer(data);
	draw_minimap(data, &data->bonus_data->minimap);
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
		data->mlx_data->img->img, 0, 0);
	return (0);
}
