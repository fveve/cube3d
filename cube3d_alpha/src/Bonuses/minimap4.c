/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap4                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:10:28 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 15:39:41 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_enn_and_coll(t_data *data, t_minimap *minimap)
{
	minimap->i = 0;
	while (minimap->i < data->bonus_data->num_collectibles)
	{
		if (data->bonus_data->collectibles[minimap->i].is_collected == 0)
		{
			minimap->screen_x = data->bonus_data->collectibles[minimap->i].c_x
				* minimap->tile_size;
			minimap->screen_y = data->bonus_data->collectibles[minimap->i].c_y
				* minimap->tile_size;
			draw_square(data, minimap->screen_x, minimap->screen_y, 0x00C400);
		}
		minimap->i++;
	}
	minimap->i = 0;
	while (minimap->i < data->bonus_data->num_enemies)
	{
		minimap->screen_x = data->bonus_data->enemies[minimap->i].pos_x
			* minimap->tile_size;
		minimap->screen_y = data->bonus_data->enemies[minimap->i].pos_y
			* minimap->tile_size;
		draw_square(data, minimap->screen_x, minimap->screen_y, 0xFFFF00);
		minimap->i++;
	}
}

void	draw_minimap(t_data *data, t_minimap *minimap)
{
	int	color;

	init_minimap_struct(data, minimap);
	while (minimap->map_y < data->trace_data->h)
	{
		minimap->map_x = 0;
		while (minimap->map_x < data->trace_data->w)
		{
			if (minimap->map_x < ft_strlen(data->map_data->map[minimap->map_y])
				&& data->map_data->map[minimap->map_y][minimap->map_x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			minimap->screen_x = minimap->map_x * minimap->tile_size;
			minimap->screen_y = minimap->map_y * minimap->tile_size;
			draw_square(data, minimap->screen_x, minimap->screen_y, color);
			minimap->map_x++;
		}
		minimap->map_y++;
	}
	minimap->screen_x = data->map_data->pos_y * minimap->tile_size;
	minimap->screen_y = data->map_data->pos_x * minimap->tile_size;
	draw_square(data, minimap->screen_x, minimap->screen_y, 0xFF0000);
	draw_enn_and_coll(data, minimap);
	draw_vision_lines(data, minimap);
}
