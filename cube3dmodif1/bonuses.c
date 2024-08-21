/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:45:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/08/19 17:39:25 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*void draw_square(t_data *data, int x, int y, int size, int color)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            my_mlx_pixel_put(data->mlx_data->img, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_minimap(t_data *data)
{
    int map_x;
    int map_y;
    int tile_size = 5;  // Taille d'une cellule sur la mini-carte

    map_y = 0;
    while (map_y < data->map_data->map_height)
    {
        map_x = 0;
        while (map_x < data->map_data->map_width)
        {
            int color;
            if (data->map_data->map[map_y][map_x] == '1')
                color = 0xFFFFFF;  // Blanc pour les murs
            else if (map_y == (int)data->map_data->pos_y && map_x == (int)data->map_data->pos_x)
                color = 0xFF0000;  // Rouge pour la position du joueur
            else
                color = 0x000000;  // Noir pour les espaces ouverts

            // Dessiner le carré correspondant sur la mini-carte
            int screen_x = map_x * tile_size;
            int screen_y = map_y * tile_size;
            draw_square(data, screen_x, screen_y, tile_size, color);

            map_x++;
        }
        map_y++;
    }
}*/

void	calculate_map_size(t_data *data)
{
	int		i;
	char	**tab;
	int		templen;

	i = 0;
	templen = 0;
	tab = data->map_data->map;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) > templen)
			templen = tab[i];
		i++;
	}
	data->trace_data->w = templen;
	data->trace_data->h = i;
	printf("h = %d\n", data->trace_data->h);
	printf("w = %d\n", data->trace_data->w);
}

int blend_colors(int color1, int color2, float alpha)
{
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;

    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    int r = (int)(alpha * r1 + (1.0 - alpha) * r2);
    int g = (int)(alpha * g1 + (1.0 - alpha) * g2);
    int b = (int)(alpha * b1 + (1.0 - alpha) * b2);

    return (r << 16) | (g << 8) | b;
}

void draw_square(t_data *data, int x, int y, int size, int color, float alpha)
{
    int i;
    int j;
    int current_color;
    int blended_color;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            // Récupérer la couleur actuelle du pixel sur l'image
            current_color = get_pixel(data->mlx_data->img, x + i, y + j);

            // Mélanger la couleur actuelle avec la couleur de la mini-carte
            blended_color = blend_colors(color, current_color, alpha);

            // Dessiner le pixel avec la couleur mélangée
            my_mlx_pixel_put(data->mlx_data->img, x + i, y + j, blended_color);
            j++;
        }
        i++;
    }
}

void draw_minimap(t_data *data)
{
    int map_x;
    int map_y;
    int tile_size = 5;  // Taille d'une cellule sur la mini-carte
    float alpha = 0.5;  // 50% de transparence

    map_y = 0;
    while (map_y < data->trace_data->h)
    {
        map_x = 0;
        while (map_x < data->trace_data->w)
        {
            int color;
            if (data->map_data->map[map_y][map_x] == '1')
                color = 0xFFFFFF;  // Blanc pour les murs
            else if (map_y == (int)data->map_data->pos_y && map_x == (int)data->map_data->pos_x)
                color = 0xFF0000;  // Rouge pour la position du joueur
            else
                color = 0x000000;  // Noir pour les espaces ouverts

            // Dessiner le carré correspondant sur la mini-carte avec transparence
            int screen_x = map_x * tile_size;
            int screen_y = map_y * tile_size;
            draw_square(data, screen_x, screen_y, tile_size, color, alpha);

            map_x++;
        }
        map_y++;
    }
}

