/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:06:44 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:24 by joncurci         ###   ########.fr       */
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

/*void	ft_check_if_ennemy(t_data *data)
{
    int ennemy_index;
	struct timeval current_time;
    long current_time_ms;
    long last_time;
    long elapsed_time;

    // Obtenir le temps actuel en secondes et microsecondes
    gettimeofday(&current_time, NULL);
    current_time_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000; // Convertir en millisecondes

    last_time = current_time_ms;

	
    // Vérifiez si le joueur est sur une case contenant un collectible
	ennemy_index = find_ennemy_at(data->bonus_data, (int)data->map_data->pos_x, (int)data->map_data->pos_y);

    if (ennemy_index != -1)
    {
		
		// Play le son de GAME OVER
		data->mlx_data->window = resize_window(data, 1920, 1080);
		
		playsound("cub3d_death_sound", 0, 1, 0);
		
		while (1) 
		{
			gettimeofday(&current_time, NULL);
			current_time_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000; // Recalcule le temps actuel
			elapsed_time = current_time_ms - last_time; // Temps écoulé en millisecondes

			if (elapsed_time >= 10000) // Si 6 secondes (6000 ms) se sont écoulées
				break ;

			mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[4], 0, 0);
		}
	
        // Lancer le generique de GAME OVER
		
		// nettoyer le game et tout detruire.
		printf("YOU LOOSE ESPECE DE GROSSE MERDE !!!!!!\n");
		exit_manager(data);
        
    }
	//printf("OBJETS COLLECTES == %d \n", data->bonus_data->collected_count);
}*/



void	ft_check_if_ennemy(t_data *data)
{
    int ennemy_index;
    struct timeval start_time;
    long elapsed_time;

    // Vérifiez si le joueur est sur une case contenant un ennemi
    ennemy_index = find_ennemy_at(data->bonus_data, (int)data->map_data->pos_x, (int)data->map_data->pos_y);

    if (ennemy_index != -1) // Si un ennemi est trouvé
    {
        // Play le son de GAME OVER
        data->mlx_data->window = resize_window(data, 1920, 1080);
        playsound("cub3d_death_sound", 0, 1, 0);

        // Obtenez le temps de départ
        gettimeofday(&start_time, NULL);

        // Boucle pour afficher l'image de GAME OVER pendant 10 secondes
        while (1)
        {
            elapsed_time = get_elapsed_time_ms(start_time); // Temps écoulé en millisecondes

            if (elapsed_time >= 10000) // Si 10 secondes (10000 ms) se sont écoulées
                break;

            mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[4], 0, 0);
        }

        // Lancer le générique de GAME OVER et nettoyer
        printf("YOU LOSE!\n");
        exit_manager(data);
    }
}
