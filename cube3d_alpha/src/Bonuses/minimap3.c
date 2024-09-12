/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap3                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:10:28 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 15:38:31 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	safe_cos(double angle)
{
	double	result;

	result = cos(angle);
	if (isnan(result) || isinf(result))
		return (0.0);
	return (result);
}

double	safe_sin(double angle)
{
	double	result;

	result = sin(angle);
	if (isnan(result) || isinf(result))
		return (0.0);
	return (result);
}

void	draw_vision_lines(t_data *data, t_minimap *minimap)
{
	fill_triangle_within_bounds_transparent(data, minimap, 0xFF0000);
}

void	init_minimap_struct_part2(t_minimap *minimap)
{
	minimap->new_dirx_right = minimap->dirx * safe_cos(minimap->angle)
		- minimap->diry * safe_sin(minimap->angle);
	minimap->new_diry_right = minimap->dirx * safe_sin(minimap->angle)
		+ minimap->diry * safe_cos(minimap->angle);
	minimap->new_dirx_left = minimap->dirx * safe_cos(-minimap->angle)
		- minimap->diry * safe_sin(-minimap->angle);
	minimap->new_diry_left = minimap->dirx * safe_sin(-minimap->angle)
		+ minimap->diry * safe_cos(-minimap->angle);
	minimap->hypot_length = sqrt(2 * ((2 * minimap->tile_size)
				* (2 * minimap->tile_size)));
	minimap->end_x_right = minimap->start_x + (int)(minimap->new_diry_right
			* minimap->hypot_length);
	minimap->end_y_right = minimap->start_y + (int)(minimap->new_dirx_right
			* minimap->hypot_length);
	minimap->end_x_left = minimap->start_x + (int)(minimap->new_diry_left
			* minimap->hypot_length);
	minimap->end_y_left = minimap->start_y + (int)(minimap->new_dirx_left
			* minimap->hypot_length);
}

void	init_minimap_struct(t_data *data, t_minimap *minimap)
{
	int	tile_w;
	int	tile_h;

	tile_w = ((3 * SCREEN_WIDTH) / 10) / data->trace_data->w;
	tile_h = ((3 * SCREEN_HEIGHT) / 10) / data->trace_data->h;
	if (tile_w >= tile_h)
		minimap->tile_size = tile_w;
	else
		minimap->tile_size = tile_h;
	minimap->map_y = 0;
	minimap->playerx = data->map_data->pos_y;
	minimap->playery = data->map_data->pos_x;
	minimap->dirx = data->trace_data->dirx;
	minimap->diry = data->trace_data->diry;
	minimap->start_x = minimap->playerx * minimap->tile_size
		+ minimap->tile_size / 2;
	minimap->start_y = minimap->playery * minimap->tile_size
		+ minimap->tile_size / 2;
	minimap->angle = PI / 6;
	init_minimap_struct_part2(minimap);
}
