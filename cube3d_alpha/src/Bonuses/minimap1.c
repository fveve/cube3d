/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:10:28 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/12 11:03:54 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calculate_map_size(t_data *data)
{
	int		i;
	char	**tab;
	int		templen;

	i = 0;
	templen = 0;
	tab = data->map_data->map;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) > templen)
			templen = ft_strlen(tab[i]);
		i++;
	}
	data->trace_data->w = templen - 1;
	data->trace_data->h = i;
}

int	blend_colors(t_minimap *minimap, int color1, int color2, float alpha)
{
	minimap->r1 = (color1 >> 16) & 0xFF;
	minimap->g1 = (color1 >> 8) & 0xFF;
	minimap->b1 = color1 & 0xFF;
	minimap->r2 = (color2 >> 16) & 0xFF;
	minimap->g2 = (color2 >> 8) & 0xFF;
	minimap->b2 = color2 & 0xFF;
	minimap->r = (int)(alpha * minimap->r1 + (1.0 - alpha) * minimap->r2);
	minimap->g = (int)(alpha * minimap->g1 + (1.0 - alpha) * minimap->g2);
	minimap->b = (int)(alpha * minimap->b1 + (1.0 - alpha) * minimap->b2);
	return ((minimap->r << 16) | (minimap->g << 8) | minimap->b);
}

void	draw_square(t_data *data, float x, float y, int color)
{
	int	i;
	int	j;
	int	current_color;
	int	blended_color;

	i = 0;
	data->bonus_data->minimap.alpha = 0.5;
	while (i < data->bonus_data->minimap.tile_size)
	{
		j = 0;
		while (j < data->bonus_data->minimap.tile_size)
		{
			current_color = get_pixel(data->mlx_data->img, (int)(x + i),
					(int)(y + j));
			blended_color = blend_colors(&data->bonus_data->minimap, color,
					current_color, data->bonus_data->minimap.alpha);
			my_mlx_pixel_put(data->mlx_data->img, (int)(x + i), (int)(y + j),
				blended_color);
			j++;
		}
		i++;
	}
}

void	draw_horizontal_line_within_bounds(t_data *data,
	t_minimap *minimap, int y, int color)
{
	int	tmp;
	int	current_color;
	int	blended_color;

	data->bonus_data->minimap.alpha = 0.5;
	if (minimap->x_start > minimap->x_end)
	{
		tmp = minimap->x_start;
		minimap->x_start = minimap->x_end;
		minimap->x_end = tmp;
	}
	while (minimap->x_start <= minimap->x_end)
	{
		if (minimap->x_start >= minimap->min_x && minimap->x_start
			<= minimap->max_x)
		{
			current_color = get_pixel(data->mlx_data->img, minimap->x_start, y);
			blended_color = blend_colors(&data->bonus_data->minimap,
					color, current_color, minimap->alpha / 2);
			my_mlx_pixel_put(data->mlx_data->img, minimap->x_start,
				y, blended_color);
		}
		minimap->x_start++;
	}
}

void	fill_triangle_part3(t_minimap *minimap, int y)
{
	if (minimap->end_y_right != minimap->start_y)
		minimap->x_start = minimap->start_x + (minimap->end_x_right
				- minimap->start_x) * (y - minimap->start_y)
			/ (minimap->end_y_right - minimap->start_y);
	else
		minimap->x_start = minimap->start_x;
	if (minimap->end_y_left != minimap->start_y)
		minimap->x_end = minimap->start_x + (minimap->end_x_left
				- minimap->start_x) * (y - minimap->start_y)
			/ (minimap->end_y_left - minimap->start_y);
	else
		minimap->x_end = minimap->start_x;
}
