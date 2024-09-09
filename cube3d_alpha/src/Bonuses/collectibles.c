/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:23:04 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/09 14:26:58 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	find_collectible_at(t_bonus_data *bonus_data, int map_y, int map_x)
{
	int	i;

	i = 0;
	while (i < bonus_data->num_collectibles)
	{
		if ((int)(bonus_data->collectibles[i].c_x) == map_x &&
			(int)(bonus_data->collectibles[i].c_y) == map_y)
			return (i);
		i++;
	}
	return (-1);
}

void	collect_item(t_data *data)
{
	int	collectible_index;

	collectible_index = find_collectible_at(data->bonus_data,
			(int)data->map_data->pos_x, (int)data->map_data->pos_y);
	if (collectible_index != -1 && data->bonus_data->collectibles
		[collectible_index].is_collected == 0)
	{
		data->bonus_data->collectibles[collectible_index].is_collected = 1;
		data->bonus_data->collected_count++;
		playsound("cub3d_collectible_sound", 0, 0, 0);
		if (data->bonus_data->collected_count == 1)
			playsound("cub3d_tablet_sound1", 0, 0, 0);
		else if (data->bonus_data->collected_count == 2)
			playsound("cub3d_tablet_sound2", 0, 0, 0);
		else if (data->bonus_data->collected_count == 3)
			playsound("cub3d_tablet_sound3", 0, 0, 0);
		else if (data->bonus_data->collected_count == 4)
			playsound("cub3d_tablet_sound4", 0, 0, 0);
		else if (data->bonus_data->collected_count == 5)
			playsound("cub3d_tablet_sound5", 0, 0, 0);
		else if (data->bonus_data->collected_count
			== data->bonus_data->num_collectibles - 1)
			playsound("cub3d_tablet_sound6", 0, 0, 0);
		else if (data->bonus_data->collected_count
			== data->bonus_data->num_collectibles)
			playsound("cub3d_tablet_sound7", 0, 0, 0);
	}
	printf("OBJETS COLLECTES == %d \n", data->bonus_data->collected_count);
}

int	is_near_green(int color, int tolerance)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (g >= 255 - tolerance && r <= tolerance && b <= tolerance)
		return (1);
	return (0);
}
