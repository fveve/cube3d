/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:07:21 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 13:07:02 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	find_ennemy_at(t_bonus_data *bonus_data, int map_y, int map_x)
{
	int	i;

	i = 0;
	while (i < bonus_data->num_enemies)
	{
		if ((int)(bonus_data->enemies[i].pos_x) == map_x &&
			(int)(bonus_data->enemies[i].pos_y) == map_y)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_check_if_ennemy(t_data *data)
{
	int				ennemy_index;
	struct timeval	start_time;
	long			elapsed_time;

	ennemy_index = find_ennemy_at(data->bonus_data, (int)data->map_data->pos_x,
			(int)data->map_data->pos_y);
	if (ennemy_index != -1)
	{
		data->mlx_data->window = resize_window(data, 1920, 1080);
		playsound("cub3d_death_sound", 0, 1, 0);
		gettimeofday(&start_time, NULL);
		while (1)
		{
			elapsed_time = get_elapsed_time_ms(start_time);
			if (elapsed_time >= 8000)
				break ;
			mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
				data->bonus_data->cinematic[4], 0, 0);
		}
		printf("YOU LOSE! ....Never seen Such a Looser... -_-'\n");
		exit_manager(data);
	}
}

void	enter_the_vortex(t_data *data)
{
	int	num_images;
	int	delay_ms;

	num_images = data->bonus_data->num_cinematic1;
	delay_ms = 40;
	if ((int)(data->bonus_data->door.x) == (int)data->map_data->pos_y &&
			(int)(data->bonus_data->door.y) == (int)data->map_data->pos_x)
	{
		cinematic(data, num_images, delay_ms);
		exit_manager(data);
		return ;
	}
}
