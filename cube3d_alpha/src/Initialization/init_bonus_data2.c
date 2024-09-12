/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus_data2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:01:16 by arafa             #+#    #+#             */
/*   Updated: 2024/09/09 16:17:16 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_doors(t_map_data *map_data, t_bonus_data *bonus_data)
{
	int	x;
	int	y;

	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			if (map_data->map[y][x] == 'D')
			{
				bonus_data->door.x = x;
				bonus_data->door.y = y;
				bonus_data->door.is_open = 0;
				bonus_data->door.last_time_texture = 0;
				bonus_data->door.time_to_change = 0;
				bonus_data->door.texture_id = 6;
				bonus_data->door.flag_incr_decr = 0;
				break ;
			}
			x++;
		}
		y++;
	}
}

void	init_projectiles(t_bonus_data *bonus_data)
{
	int	i;
	int	num_projectiles;

	num_projectiles = 10;
	i = 0;
	bonus_data->num_projectiles = num_projectiles;
	bonus_data->projectiles = (t_projectile *)malloc(sizeof(t_projectile)
			* num_projectiles);
	while (i < num_projectiles)
	{
		bonus_data->projectiles[i].pos_x = 0;
		bonus_data->projectiles[i].pos_y = 0;
		bonus_data->projectiles[i].dir_x = 0;
		bonus_data->projectiles[i].dir_y = 0;
		bonus_data->projectiles[i].is_active = 0;
		bonus_data->projectiles[i].speed = 0.1;
		i++;
	}
}
