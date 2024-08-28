/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:06:44 by joncurci          #+#    #+#             */
/*   Updated: 2024/08/28 23:18:28 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	open_close_thedoor(t_data *data)
{
	if (data->bonus_data->door.is_open == 0
			&& data->bonus_data->collected_count == data->map_data->num_collectibles)
		data->bonus_data->door.is_open = 1;
	else if (data->bonus_data->door.is_open == 1)
	{
		data->bonus_data->door.is_open = 0;
		data->bonus_data->door.flag_incr_decr = 0;
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
			if (elapsed_time >= 1000) // Changer d'image entre les timings des chevrons
			{
				data->bonus_data->door.texture_id++;
				// Réinitialiser le temps pour la prochaine image
				data->bonus_data->door.last_time_texture = current_time_ms;
			}
		}
		else if (data->bonus_data->door.texture_id > 12 && data->bonus_data->door.texture_id < 30)
		{
			if (elapsed_time >= 20) // Changer d'image toutes les 20 millisecondes
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
			if (elapsed_time >= 20) // Changer d'image toutes les 20 millisecondes
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
