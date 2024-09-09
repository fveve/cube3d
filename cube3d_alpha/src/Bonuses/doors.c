/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:01:12 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/09 15:06:34 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	open_close_thedoor(t_data *data)
{
	if (data->bonus_data->door.is_open == 0 && data->bonus_data->collected_count
		== data->map_data->num_collectibles)
	{
		data->bonus_data->door.is_open = 1;
		playsound("cub3d_door_sequence", 0, 0, 0);
	}
	else if (data->bonus_data->door.is_open == 1)
	{
		data->bonus_data->door.is_open = 0;
		data->bonus_data->door.flag_incr_decr = 0;
		data->bonus_data->door.texture_id = 6;
		data->bonus_data->door.last_time_texture = 0;
	}
}

int	get_door_texture_animation(t_data *data)
{
	struct timeval	current_time;
	long			current_time_ms;
	long			last_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	current_time_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	last_time = data->bonus_data->door.last_time_texture;
	if (last_time == 0)
	{
		data->bonus_data->door.last_time_texture = current_time_ms;
		return (data->bonus_data->door.texture_id);
	}
	elapsed_time = current_time_ms - last_time;
	if (data->bonus_data->door.is_open == 1)
	{
		if (data->bonus_data->door.texture_id == 6)
			data->bonus_data->door.texture_id++;
		else if (data->bonus_data->door.texture_id > 6
			&& data->bonus_data->door.texture_id < 13)
		{
			if (elapsed_time >= 1200)
			{
				data->bonus_data->door.texture_id++;
				data->bonus_data->door.last_time_texture = current_time_ms;
			}
		}
		else if (data->bonus_data->door.texture_id == 13)
		{
			if (elapsed_time >= 2000)
			{
				data->bonus_data->door.texture_id++;
				data->bonus_data->door.last_time_texture = current_time_ms;
			}
		}
		else if (data->bonus_data->door.texture_id > 12
			&& data->bonus_data->door.texture_id < 30)
		{
			if (elapsed_time >= 30)
			{
				data->bonus_data->door.texture_id++;
				if (data->bonus_data->door.texture_id == 30)
					data->bonus_data->door.flag_incr_decr = 1;
				data->bonus_data->door.last_time_texture = current_time_ms;
			}
		}
		else if (data->bonus_data->door.texture_id > 29
			&& data->bonus_data->door.texture_id <= 36)
		{
			if (elapsed_time >= 30)
			{
				if (data->bonus_data->door.texture_id == 29)
				{
					data->bonus_data->door.texture_id++;
					data->bonus_data->door.flag_incr_decr = 1;
				}
				else if (data->bonus_data->door.texture_id > 29
					&& data->bonus_data->door.texture_id < 36
					&& data->bonus_data->door.flag_incr_decr == 1)
					data->bonus_data->door.texture_id++;
				else if (data->bonus_data->door.texture_id > 29
					&& data->bonus_data->door.texture_id < 36
					&& data->bonus_data->door.flag_incr_decr == -1)
					data->bonus_data->door.texture_id--;
				else if (data->bonus_data->door.texture_id == 36)
				{
					data->bonus_data->door.texture_id--;
					data->bonus_data->door.flag_incr_decr = -1;
				}
				data->bonus_data->door.last_time_texture = current_time_ms;
			}
		}
	}
	return (data->bonus_data->door.texture_id);
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
