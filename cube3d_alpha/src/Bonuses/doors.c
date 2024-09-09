/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: john <john@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:06:44 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/07 22:36:31 by john             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	open_close_thedoor(t_data *data)
{
	if (data->bonus_data->door.is_open == 0
			&& data->bonus_data->collected_count == data->map_data->num_collectibles)
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

int get_door_texture_animation(t_data *data)
{
    struct timeval current_time;
    long current_time_ms;
    long last_time;
    long elapsed_time;

    // Obtenir le temps actuel en secondes et microsecondes
    gettimeofday(&current_time, NULL);
    current_time_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000; // Convertir en millisecondes

    last_time = data->bonus_data->door.last_time_texture;

    // Si c'est la première fois, initialiser last_time
    if (last_time == 0)
    {
        data->bonus_data->door.last_time_texture = current_time_ms;
        return data->bonus_data->door.texture_id;
    }

    elapsed_time = current_time_ms - last_time; // Temps écoulé depuis la dernière mise à jour

    
	if (data->bonus_data->door.is_open == 1)
	{
		if (data->bonus_data->door.texture_id == 6)
			data->bonus_data->door.texture_id++;
		else if (data->bonus_data->door.texture_id > 6 && data->bonus_data->door.texture_id < 13)
		{
			if (elapsed_time >= 1200) // Changer d'image entre les timings des chevrons
			{
				data->bonus_data->door.texture_id++;
				// Réinitialiser le temps pour la prochaine image
				data->bonus_data->door.last_time_texture = current_time_ms;
			}
		}
		else if (data->bonus_data->door.texture_id == 13)
		{
			if (elapsed_time >= 2000) // Changer d'image toutes les 20 millisecondes
			{
				data->bonus_data->door.texture_id++;
				data->bonus_data->door.last_time_texture = current_time_ms;
			}
		}
		else if (data->bonus_data->door.texture_id > 12 && data->bonus_data->door.texture_id < 30)
		{
			if (elapsed_time >= 30) // Changer d'image toutes les 20 millisecondes
			{
				data->bonus_data->door.texture_id++;
				if (data->bonus_data->door.texture_id == 30)
					data->bonus_data->door.flag_incr_decr = 1;
				// Réinitialiser le temps pour la prochaine image
				data->bonus_data->door.last_time_texture = current_time_ms;
			}
		}
		else if (data->bonus_data->door.texture_id > 29 && data->bonus_data->door.texture_id <= 36)
		{
			if (elapsed_time >= 30) // Changer d'image toutes les 20 millisecondes
			{
				if (data->bonus_data->door.texture_id == 29)
				{
					data->bonus_data->door.texture_id++;
					data->bonus_data->door.flag_incr_decr = 1;
				}
				else if (data->bonus_data->door.texture_id > 29 && data->bonus_data->door.texture_id < 36 && data->bonus_data->door.flag_incr_decr == 1)
					data->bonus_data->door.texture_id++;
				else if (data->bonus_data->door.texture_id > 29 && data->bonus_data->door.texture_id < 36 && data->bonus_data->door.flag_incr_decr == -1)
					data->bonus_data->door.texture_id--;
				else if (data->bonus_data->door.texture_id == 36)
				{
					data->bonus_data->door.texture_id--;
					data->bonus_data->door.flag_incr_decr = -1;
				}
				// Réinitialiser le temps pour la prochaine image
				data->bonus_data->door.last_time_texture = current_time_ms;
			}
		}
    }
    // Retourner la texture actuelle
    return (data->bonus_data->door.texture_id);
}

void enter_the_vortex(t_data *data)
{
	int	num_images;
	int	delay_ms;

	num_images = data->bonus_data->num_cinematic1;
	delay_ms = 40;
    if ((int)(data->bonus_data->door.x) == (int)data->map_data->pos_y &&
            (int)(data->bonus_data->door.y) == (int)data->map_data->pos_x)
	{
		//!!!!!!!!!!!!!!
		cinematic(data, num_images, delay_ms);//TODO
		//printf("DoorX == %d // Y == %d \n", (int)data->map_data->pos_y, (int)data->map_data->pos_x);


		//data->mlx_data->window = resize_window(data, 1920, 1080);
		//usleep(500 * 1000); // Convertir ms en microsecondes pour usleep
		//mlx_do_sync(data->mlx_data->mlx);
		//data->mlx_data->window = resize_window(data, 1920, 1080);
		/*while (1)
		{
			mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[3], 0, 0);
		}*/
		//usleep(20000 * 1000); // Convertir ms en microsecondes pour usleep
		//mlx_do_sync(data->mlx_data->mlx);
			
		//!!!!!!!-------------------------
		exit_manager(data);
		return ;  // Retourne l'index de l'ennemy trouvé
	}
	
}