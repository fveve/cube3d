/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:45:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/05 16:11:25 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
			templen = ft_strlen(tab[i]);
		i++;
	}
	data->trace_data->w = templen - 1;
	data->trace_data->h = i;
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

    return ((r << 16) | (g << 8) | b);
}

void draw_square(t_data *data, float x, float y, int size, int color)
{
    int i = 0;
    int j;
    int current_color;
    int blended_color;
    float alpha = 0.5;// 50% de transparence

    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            		// Récupérer la couleur actuelle du pixel sur l'image
            current_color = get_pixel(data->mlx_data->img, (int)(x + i), (int)(y + j));
            		// Mélanger la couleur actuelle avec la couleur de la mini-carte
            blended_color = blend_colors(color, current_color, alpha);
            		// Dessiner le pixel avec la couleur mélangée
            my_mlx_pixel_put(data->mlx_data->img, (int)(x + i), (int)(y + j), blended_color);
            
            j++;
        }
        i++;
    }
}

void draw_line_within_bounds(t_data *data, int x0, int y0, int x1, int y1, int color, int min_x, int max_x, int min_y, int max_y)
{
    int dx = ft_abs(x1 - x0);
    int dy = ft_abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        // Vérification des limites de la minimap
        if (x0 >= min_x && x0 <= max_x && y0 >= min_y && y0 <= max_y)
            my_mlx_pixel_put(data->mlx_data->img, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// Fonction pour dessiner une ligne horizontale avec vérification des limites
void draw_horizontal_line_within_bounds(t_data *data, int y, int x_start, int x_end, int color, int min_x, int max_x, float alpha)
{
    if (x_start > x_end)
    {
        int tmp = x_start;
        x_start = x_end;
        x_end = tmp;
    }

    while (x_start <= x_end)
    {
        // Vérification des limites de la minimap en X
        if (x_start >= min_x && x_start <= max_x)
        {
            // Mélanger la couleur avec la couleur actuelle pour créer de la transparence
            int current_color = get_pixel(data->mlx_data->img, x_start, y);
            int blended_color = blend_colors(color, current_color, alpha / 2); //TODO transparence un quart
            my_mlx_pixel_put(data->mlx_data->img, x_start, y, blended_color);
        }
        x_start++;
    }
}

// Fonction pour remplir le triangle avec transparence
void fill_triangle_within_bounds_transparent(t_data *data, int x0, int y0, int x1, int y1, int x2, int y2, int color, float alpha)
{
    // Limites de la minimap
    int min_x = 0;
    int max_x = data->trace_data->w * 20;
    int min_y = 0;
    int max_y = data->trace_data->h * 20;

    // Trier les points par y croissant (y0 <= y1 <= y2)
    if (y0 > y1)
    {
        int tmp_x = x0, tmp_y = y0;
        x0 = x1;
        y0 = y1;
        x1 = tmp_x;
        y1 = tmp_y;
    }
    if (y0 > y2)
    {
        int tmp_x = x0, tmp_y = y0;
        x0 = x2;
        y0 = y2;
        x2 = tmp_x;
        y2 = tmp_y;
    }
    if (y1 > y2)
    {
        int tmp_x = x1, tmp_y = y1;
        x1 = x2;
        y1 = y2;
        x2 = tmp_x;
        y2 = tmp_y;
    }
    // Remplissage par scanline avec transparence
    int y = y0;
    while (y <= y2)
    {
        int x_start, x_end;

        if (y < y1)
        {
            // Première moitié du triangle
            if (y1 != y0)
                x_start = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
            else
                x_start = x0;
            if (y2 != y0)
                x_end = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
            else
                x_end = x0;
        }
        else
        {
            // Seconde moitié du triangle
            if (y2 != y1)
                x_start = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
            else
                x_start = x1;
            if (y2 != y0)
                x_end = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
            else
                x_end = x0;
        }
        // Vérification des limites de la minimap en Y
        if (y >= min_y && y <= max_y)
            draw_horizontal_line_within_bounds(data, y, x_start, x_end, color, min_x, max_x, alpha);
        y++;
    }
}

// Protection contre les erreurs de calcul
double safe_cos(double angle)
{
    double result = cos(angle);
    if (isnan(result) || isinf(result))
        return (0.0);  // Valeur de secours en cas d'erreur
    return (result);
}

double safe_sin(double angle)
{
    double result = sin(angle);
    if (isnan(result) || isinf(result))
        return (0.0);  // Valeur de secours en cas d'erreur
    return (result);
}

void draw_vision_lines(t_data *data, float player_x, float player_y, int tile_size, double dirX, double dirY)
{
    // Point de départ de la ligne (position du joueur)
    int start_x = player_x * tile_size + tile_size / 2;
    int start_y = player_y * tile_size + tile_size / 2;

    // Ajouter un angle de 30 degrés (converti en radians)
    double angle = PI / 6;  // 30 degrés en radians

    // Utilisation des fonctions sécurisées pour éviter les erreurs de calcul
    double new_dirX_right = dirX * safe_cos(angle) - dirY * safe_sin(angle);
    double new_dirY_right = dirX * safe_sin(angle) + dirY * safe_cos(angle);

    double new_dirX_left = dirX * safe_cos(-angle) - dirY * safe_sin(-angle);
    double new_dirY_left = dirX * safe_sin(-angle) + dirY * safe_cos(-angle);

    // Calcul des points finaux des lignes gauche et droite (plus longues que la centrale)
    double hypot_length = sqrt(2 * ((2 * tile_size) * (2 * tile_size)));  // Plus grande que la ligne centrale

    int end_x_right = start_x + (int)(new_dirY_right * hypot_length);  // Inversion des axes
    int end_y_right = start_y + (int)(new_dirX_right * hypot_length);  // Inversion des axes

    int end_x_left = start_x + (int)(new_dirY_left * hypot_length);  // Inversion des axes
    int end_y_left = start_y + (int)(new_dirX_left * hypot_length);  // Inversion des axes

    // Remplir le triangle avec transparence
    fill_triangle_within_bounds_transparent(data, start_x, start_y, end_x_right, end_y_right, end_x_left, end_y_left, 0xFF0000, 0.5);
}

// Fonction pour tracer la ligne centrale du champ de vision sur la minimap


// Mise à jour de draw_minimap pour inclure les trois lignes formant le triangle de vision
void  draw_minimap(t_data *data)
{
    int map_x;
    int map_y;
    int tile_size = 20;  // Taille d'une cellule sur la mini-carte
    float screen_x;
    float screen_y;

    map_y = 0;
    while (map_y < data->trace_data->h)
    {
        map_x = 0;
        while (map_x < data->trace_data->w)
        {
            int color;
            if (data->map_data->map[map_y][map_x] == '1')
                color = 0xFFFFFF;  // Blanc pour les murs
            else
                color = 0x000000;  // Noir pour les espaces ouverts
            // Dessiner chaque case de la mini-carte avec transparence, sauf le joueur
            screen_x = map_x * tile_size;
            screen_y = map_y * tile_size;
            draw_square(data, screen_x, screen_y, tile_size, color);

            map_x++;
        }
        map_y++;
    }

    // Dessiner le carré du joueur avec des coordonnées précises (mouvement fluide)
    screen_x = data->map_data->pos_y * tile_size;
    screen_y = data->map_data->pos_x * tile_size;
    draw_square(data, screen_x, screen_y, tile_size, 0xFF0000);  // Rouge pour le joueur

    // Dessiner les lignes du champ de vision partant de la position du joueur
    draw_vision_lines(data, data->map_data->pos_y, data->map_data->pos_x, tile_size, data->trace_data->dirX, data->trace_data->dirY);
}

