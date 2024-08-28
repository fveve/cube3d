/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:06:44 by joncurci          #+#    #+#             */
/*   Updated: 2024/08/26 14:27:31 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	find_collectible_at(t_bonus_data *bonus_data, int map_y, int map_x)
{
    int i;

    i = 0;
    while (i < bonus_data->num_collectibles)
    {
        // Vérifie si les coordonnées correspondent à celles du collectible
		//printf("COLLEX mapX == %d // mapY == %d \n", map_x, map_y);
		//printf("COllectible#4 c_x == %f // c_y == %f \n", bonus_data->collectibles[i].c_x, bonus_data->collectibles[i].c_y);
		
        if ((int)(bonus_data->collectibles[i].c_x) == map_x &&
            (int)(bonus_data->collectibles[i].c_y) == map_y)
        {
			//!!!!!!!!!!!!!!
			//printf("INDEX du Collec == %d || ", i);
			//printf("COLLEX mapX == %d // mapY == %d \n", map_x, map_y);
			//!!!!!!!-------------------------
            return (i);  // Retourne l'index du collectible trouvé
        }
        i++;
    }
    return (-1);  // Retourne -1 si aucun collectible n'a été trouvé à ces coordonnées
}

void collect_item(t_data *data)
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
}

// Fonction pour vérifier si une couleur est proche du vert avec une tolérance
int is_near_green(int color, int tolerance)
{
    int r = (color >> 16) & 0xFF; // Extraction de la composante rouge
    int g = (color >> 8) & 0xFF;  // Extraction de la composante verte
    int b = color & 0xFF;         // Extraction de la composante bleue

    // Vérification si la composante verte est dominante et si les composantes rouge et bleue sont proches de 0
    if (g >= 255 - tolerance && r <= tolerance && b <= tolerance)
        return 1; // C'est une couleur proche du vert
    return 0;     // Ce n'est pas vert
}