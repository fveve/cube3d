/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:51:58 by arafa             #+#    #+#             */
/*   Updated: 2024/09/09 14:01:13 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_bonus_data(t_data *data)
{
	data->bonus_data->num_doors = data->map_data->num_doors;
	//data->bonus_data->door = (t_door *)malloc(sizeof(t_door)
	//	* data->bonus_data->num_doors);
	//TODO init le reste des bonus.
	data->bonus_data->num_cinematic1 = 173;
	data->bonus_data->cinematic_w = 1920;
	data->bonus_data->cinematic_h = 1080;
	//data->bonus_data->cinematic1 = malloc(sizeof(void) * data->bonus_data->num_cinematic1);
}

void	init_collectibles2(t_map_data *map_data, t_bonus_data *bonus_data)
{
	// Allocation du tableau de collectibles
	bonus_data->num_collectibles = map_data->num_collectibles;
	bonus_data->collectibles = (t_collectible *)malloc(sizeof(t_collectible)
			* bonus_data->num_collectibles);
}

void	init_collectibles(t_map_data *map_data, t_bonus_data *bonus_data)
{
	int	collectible_index;
	int	x;
	int	y;

	collectible_index = 0;
	init_collectibles2(map_data, bonus_data);
	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			if (map_data->map[y][x] == 'C') // 'C' représente un collectible sur la carte
			{
				bonus_data->collectibles[collectible_index].c_x = (double)x;
				bonus_data->collectibles[collectible_index].c_y = (double)y;
				bonus_data->collectibles[collectible_index].is_collected = 0; // Pas encore ramassé
				collectible_index++;
			}
			x++;
		}
		y++;
	}
	// Initialiser le compteur de collectibles ramassés à 0
	bonus_data->collected_count = 0;
}

int	init_enemies2(t_map_data *map_data, t_bonus_data *bonus_data)
{
	bonus_data->num_enemies = map_data->num_ennemies;
	bonus_data->enemies = (t_enemy *)malloc(sizeof(t_enemy)
			* bonus_data->num_enemies);
	return (0);
}

void	init_enemies(t_map_data *map_data, t_bonus_data *bonus_data)
{
	int	enemy_index;
	int x;
	int	y;
	// Allocation du tableau d'ennemis
	enemy_index = init_enemies2(map_data, bonus_data);
	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			if (map_data->map[y][x] == 'Z') // 'Z' représente un ennemi sur la carte
			{
				bonus_data->enemies[enemy_index].pos_x = (double)x;
				bonus_data->enemies[enemy_index].pos_y = (double)y;
				bonus_data->enemies[enemy_index].hp = 100; // Exemple : 100 points de vie
				bonus_data->enemies[enemy_index].is_alive = 1;
				bonus_data->enemies[enemy_index].is_moving = 0;
				bonus_data->enemies[enemy_index].speed = 0.05; // Exemple de vitesse
				enemy_index++;
			}
			x++;
		}
		y++;
	}
}
