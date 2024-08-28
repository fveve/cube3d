/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:06:44 by joncurci          #+#    #+#             */
/*   Updated: 2024/08/26 21:50:38 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	find_ennemy_at(t_bonus_data *bonus_data, int map_y, int map_x)
{
    int i;

    i = 0;
    while (i < bonus_data->num_enemies)
    {
        // Vérifie si les coordonnées correspondent à celles du collectible
		//printf("COLLEX mapX == %d // mapY == %d \n", map_x, map_y);
		//printf("COllectible#4 c_x == %f // c_y == %f \n", bonus_data->collectibles[i].c_x, bonus_data->collectibles[i].c_y);
		
        if ((int)(bonus_data->enemies[i].pos_x) == map_x &&
            (int)(bonus_data->enemies[i].pos_y) == map_y)
        {
			//!!!!!!!!!!!!!!
			//printf("INDEX du ENNEMY == %d || ", i);
			//printf("ENNEMYX mapX == %d // mapY == %d \n", map_x, map_y);
			//!!!!!!!-------------------------
            return (i);  // Retourne l'index de l'ennemy trouvé
        }
        i++;
    }
    return (-1);  // Retourne -1 si aucun ennemy n'a été trouvé à ces coordonnées
}

/*void collect_item(t_data *data)
{
    int collectible_index;

    // Vérifiez si le joueur est sur une case contenant un collectible
    collectible_index = find_collectible_at(data->bonus_data, (int)data->map_data->pos_x, (int)data->map_data->pos_y);

    if (collectible_index != -1 && data->bonus_data->collectibles[collectible_index].is_collected == 0)
    {
        // Marquer le collectible comme collecté
        data->bonus_data->collectibles[collectible_index].is_collected = 1;

        // Mettre à jour le compteur de collectibles collectés
        data->bonus_data->collected_count++;
        
        // Vous pouvez également déclencher des effets ici, comme jouer un son ou augmenter le score
    }
	printf("OBJETS COLLECTES == %d \n", data->bonus_data->collected_count);
}*/


