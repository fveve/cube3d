/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:10:28 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 15:37:44 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	fill_triangle_part4(t_minimap *minimap, int y)
{
	if (minimap->end_y_left != minimap->end_y_right)
		minimap->x_start = minimap->end_x_right + (minimap->end_x_left
				- minimap->end_x_right) * (y - minimap->end_y_right)
			/ (minimap->end_y_left - minimap->end_y_right);
	else
		minimap->x_start = minimap->end_x_right;
	if (minimap->end_y_left != minimap->start_y)
		minimap->x_end = minimap->start_x + (minimap->end_x_left
				- minimap->start_x) * (y - minimap->start_y)
			/ (minimap->end_y_left - minimap->start_y);
	else
		minimap->x_end = minimap->start_x;
}

void	set_triangle_points1(t_minimap *minimap)
{
	minimap->tmp_x = minimap->start_x;
	minimap->tmp_y = minimap->start_y;
	minimap->start_x = minimap->end_x_right;
	minimap->start_y = minimap->end_y_right;
	minimap->end_x_right = minimap->tmp_x;
	minimap->end_y_right = minimap->tmp_y;
}

void	set_triangle_points2(t_minimap *minimap)
{
	minimap->tmp_x = minimap->start_x;
	minimap->tmp_y = minimap->start_y;
	minimap->start_x = minimap->end_x_left;
	minimap->start_y = minimap->end_y_left;
	minimap->end_x_left = minimap->tmp_x;
	minimap->end_y_left = minimap->tmp_y;
}

void	set_triangle_points3(t_minimap *minimap)
{
	minimap->tmp_x = minimap->end_x_right;
	minimap->tmp_y = minimap->end_y_right;
	minimap->end_x_right = minimap->end_x_left;
	minimap->end_y_right = minimap->end_y_left;
	minimap->end_x_left = minimap->tmp_x;
	minimap->end_y_left = minimap->tmp_y;
}

void	fill_triangle_within_bounds_transparent(t_data *data,
	t_minimap *minimap, int color)
{
	int	y;

	minimap->min_y = 0;
	minimap->max_y = data->trace_data->h * minimap->tile_size;
	minimap->min_x = 0;
	minimap->max_x = data->trace_data->w * minimap->tile_size;
	if (minimap->start_y > minimap->end_y_right)
		set_triangle_points1(minimap);
	if (minimap->start_y > minimap->end_y_left)
		set_triangle_points2(minimap);
	if (minimap->end_y_right > minimap->end_y_left)
		set_triangle_points3(minimap);
	y = minimap->start_y;
	while (y <= minimap->end_y_left)
	{
		if (y < minimap->end_y_right)
			fill_triangle_part3(minimap, y);
		else
			fill_triangle_part4(minimap, y);
		if (y >= minimap->min_y && y <= minimap->max_y)
			draw_horizontal_line_within_bounds(data, minimap, y, color);
		y++;
	}
}
