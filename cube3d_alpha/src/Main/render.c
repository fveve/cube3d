/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:11:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/04 14:44:58 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void	init_ray2(t_data *data, int x)
{
	data->trace_data->cameraX = (2 * x / (double)SCREEN_WIDTH - 1) * (SCREEN_WIDTH / (double)SCREEN_HEIGHT); //TODO TTTTEESSTT
	//data->trace_data->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
	data->trace_data->rayDirX = data->trace_data->dirX + data->trace_data->planeX * data->trace_data->cameraX;
	data->trace_data->rayDirY = data->trace_data->dirY + data->trace_data->planeY * data->trace_data->cameraX;
	data->trace_data->mapX = (int)data->map_data->pos_x;
	data->trace_data->mapY = (int)data->map_data->pos_y;

	// Initialisation des distances
	if (data->trace_data->rayDirX == 0)
		data->trace_data->deltaDistX = 1e30;
	else
		data->trace_data->deltaDistX = ft_abs(1 / data->trace_data->rayDirX);

	if (data->trace_data->rayDirY == 0)
		data->trace_data->deltaDistY = 1e30;
	else
		data->trace_data->deltaDistY = ft_abs(1 / data->trace_data->rayDirY);

	data->trace_data->hit = 0;

	// Calcul des steps et sideDist
	if (data->trace_data->rayDirX < 0)
	{
		data->trace_data->stepX = -1;
		data->trace_data->sideDistX = (data->map_data->pos_x - data->trace_data->mapX) * data->trace_data->deltaDistX;
	}
	else
	{
		data->trace_data->stepX = 1;
		data->trace_data->sideDistX = (data->trace_data->mapX + 1.0 - data->map_data->pos_x) * data->trace_data->deltaDistX;
	}
	if (data->trace_data->rayDirY < 0)
	{
		data->trace_data->stepY = -1;
		data->trace_data->sideDistY = (data->map_data->pos_y - data->trace_data->mapY) * data->trace_data->deltaDistY;
	}
	else
	{
		data->trace_data->stepY = 1;
		data->trace_data->sideDistY = (data->trace_data->mapY + 1.0 - data->map_data->pos_y) * data->trace_data->deltaDistY;
	}
}


void	dda_loop2(t_data *data, int *tex_index2)
{
	char	current_tile;
	int		collectible_index;

	while (data->trace_data->hit == 0)
	{
		if (data->trace_data->sideDistX < data->trace_data->sideDistY)
		{
			data->trace_data->sideDistX += data->trace_data->deltaDistX;
			data->trace_data->mapX += data->trace_data->stepX;
			data->trace_data->side = 0;
		}
		else
		{
			data->trace_data->sideDistY += data->trace_data->deltaDistY;
			data->trace_data->mapY += data->trace_data->stepY;
			data->trace_data->side = 1;
		}

		current_tile = data->map_data->map[data->trace_data->mapX][data->trace_data->mapY];

		if (current_tile == '1') // Collision avec un mur
		{
			data->trace_data->hit = 1;
		}
		else if (current_tile == 'D') // Collision avec une porte
		{
			if (data->bonus_data->door.is_open == 0) // Si la porte est fermée
			{
				data->trace_data->hit = 1;
			}
			else if (data->bonus_data->door.is_open == 1) // Si la porte est ouverte
			{
				data->trace_data->hit = 1;
			}
		}
		else if (current_tile == 'C') // Collision avec un collectible
		{
			collectible_index = find_collectible_at(data->bonus_data, data->trace_data->mapX, data->trace_data->mapY);
			if (collectible_index != -1 && data->bonus_data->collectibles[collectible_index].is_collected == 0)
			{
				*tex_index2 = 5; // Texture du collectible
				data->trace_data->hit = 1; // Permet l'affichage du collectible
			}
		}
		else if (current_tile == 'Z') // Collision avec un ennemi
		{
			collectible_index = find_ennemy_at(data->bonus_data, data->trace_data->mapX, data->trace_data->mapY);
			if (collectible_index != -1 && data->bonus_data->enemies[collectible_index].is_alive == 1)
			{
				*tex_index2 = 4; // Texture de l'ennemi
				data->trace_data->hit = 1; // Permet l'affichage de l'ennemi
			}
		}
	}
}

void	calculate_distance2(t_data *data)
{
	if (data->trace_data->side == 0)
		data->trace_data->perpWallDist = (data->trace_data->sideDistX - data->trace_data->deltaDistX);
	else
		data->trace_data->perpWallDist = (data->trace_data->sideDistY - data->trace_data->deltaDistY);

	//--------------------------------------------
	//double aspect_ratio = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	//data->trace_data->lineHeight = (int)((SCREEN_HEIGHT / data->trace_data->perpWallDist) * aspect_ratio);
	data->trace_data->lineHeight = (int)(SCREEN_HEIGHT / data->trace_data->perpWallDist);

	data->trace_data->drawStart = -data->trace_data->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawStart < 0)
		data->trace_data->drawStart = 0;

	data->trace_data->drawEnd = data->trace_data->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawEnd >= SCREEN_HEIGHT)
		data->trace_data->drawEnd = SCREEN_HEIGHT - 1;


	// Calcul de WallX pour déterminer quelle partie de la texture utiliser
	if (data->trace_data->side == 0)
		data->trace_data->WallX = data->map_data->pos_y + data->trace_data->perpWallDist * data->trace_data->rayDirY;
	else
		data->trace_data->WallX = data->map_data->pos_x + data->trace_data->perpWallDist * data->trace_data->rayDirX;
	data->trace_data->WallX -= floor(data->trace_data->WallX);

	// Calcul de la position X de la texture
	data->trace_data->texX = (int)(data->trace_data->WallX * (double)TEX_WIDTH);
	if (data->trace_data->side == 0 && data->trace_data->rayDirX > 0)
		data->trace_data->texX = TEX_WIDTH - data->trace_data->texX - 1;
	if (data->trace_data->side == 1 && data->trace_data->rayDirY < 0)
		data->trace_data->texX = TEX_HEIGHT - data->trace_data->texX - 1;

	data->trace_data->step = 1.0 * TEX_HEIGHT / data->trace_data->lineHeight;
	data->trace_data->texPos = (data->trace_data->drawStart - SCREEN_HEIGHT / 2 + data->trace_data->lineHeight / 2) * data->trace_data->step;
}


void	render_column2(t_data *data, int x/*, int tex_index*/, int tex_index2)
{
	int	y;

	//!!!!!!------> Affichage des objets et ennemis si présents
	if (tex_index2 != -1)
	{
		y = data->trace_data->drawStart;
		while (y < data->trace_data->drawEnd)
		{
			data->trace_data->texY = (int)data->trace_data->texPos & (TEX_HEIGHT - 1);
			data->trace_data->texPos += data->trace_data->step;
			data->trace_data->color = get_pixel(data->mlx_data->texture[tex_index2], data->trace_data->texX, data->trace_data->texY);

			if (!is_near_green(data->trace_data->color, 110))
				data->trace_data->buffer[y][x] = data->trace_data->color;
			y++;
		}
	}
}













void	clear_buffer(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			data->trace_data->buffer[y][x] = 0; // Efface chaque pixel en le définissant à 0 (noir)
			x++;
		}
		y++;
	}
}

void	init_ray(t_data *data, int x)
{
	data->trace_data->cameraX = (2 * x / (double)SCREEN_WIDTH - 1) * (SCREEN_WIDTH / (double)SCREEN_HEIGHT); //TODO TTTTEESSTT
	//data->trace_data->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
	data->trace_data->rayDirX = data->trace_data->dirX + data->trace_data->planeX * data->trace_data->cameraX;
	data->trace_data->rayDirY = data->trace_data->dirY + data->trace_data->planeY * data->trace_data->cameraX;
	data->trace_data->mapX = (int)data->map_data->pos_x;
	data->trace_data->mapY = (int)data->map_data->pos_y;

	// Initialisation des distances
	if (data->trace_data->rayDirX == 0)
		data->trace_data->deltaDistX = 1e30;
	else
		data->trace_data->deltaDistX = ft_abs(1 / data->trace_data->rayDirX);

	if (data->trace_data->rayDirY == 0)
		data->trace_data->deltaDistY = 1e30;
	else
		data->trace_data->deltaDistY = ft_abs(1 / data->trace_data->rayDirY);

	data->trace_data->hit = 0;

	// Calcul des steps et sideDist
	if (data->trace_data->rayDirX < 0)
	{
		data->trace_data->stepX = -1;
		data->trace_data->sideDistX = (data->map_data->pos_x - data->trace_data->mapX) * data->trace_data->deltaDistX;
	}
	else
	{
		data->trace_data->stepX = 1;
		data->trace_data->sideDistX = (data->trace_data->mapX + 1.0 - data->map_data->pos_x) * data->trace_data->deltaDistX;
	}
	if (data->trace_data->rayDirY < 0)
	{
		data->trace_data->stepY = -1;
		data->trace_data->sideDistY = (data->map_data->pos_y - data->trace_data->mapY) * data->trace_data->deltaDistY;
	}
	else
	{
		data->trace_data->stepY = 1;
		data->trace_data->sideDistY = (data->trace_data->mapY + 1.0 - data->map_data->pos_y) * data->trace_data->deltaDistY;
	}
}

void	dda_loop(t_data *data, int *tex_index2)
{
	char	current_tile;
	int		collectible_index;

	while (data->trace_data->hit == 0)
	{
		if (data->trace_data->sideDistX < data->trace_data->sideDistY)
		{
			data->trace_data->sideDistX += data->trace_data->deltaDistX;
			data->trace_data->mapX += data->trace_data->stepX;
			data->trace_data->side = 0;
		}
		else
		{
			data->trace_data->sideDistY += data->trace_data->deltaDistY;
			data->trace_data->mapY += data->trace_data->stepY;
			data->trace_data->side = 1;
		}

		current_tile = data->map_data->map[data->trace_data->mapX][data->trace_data->mapY];

		if (current_tile == '1') // Collision avec un mur
		{
			data->trace_data->hit = 1;
		}
		else if (current_tile == 'D') // Collision avec une porte
		{
			if (data->bonus_data->door.is_open == 0) // Si la porte est fermée
			{
				data->trace_data->hit = 1;
			}
			else if (data->bonus_data->door.is_open == 1) // Si la porte est ouverte
			{
				data->trace_data->hit = 1;
			}
		}
		else if (current_tile == 'C') // Collision avec un collectible
		{
			collectible_index = find_collectible_at(data->bonus_data, data->trace_data->mapX, data->trace_data->mapY);
			if (collectible_index != -1 && data->bonus_data->collectibles[collectible_index].is_collected == 0)
			{
				*tex_index2 = 5; // Texture du collectible
				data->trace_data->hit = 0; // Permet l'affichage du collectible
			}
		}
		else if (current_tile == 'Z') // Collision avec un ennemi
		{
			collectible_index = find_ennemy_at(data->bonus_data, data->trace_data->mapX, data->trace_data->mapY);
			if (collectible_index != -1 && data->bonus_data->enemies[collectible_index].is_alive == 1)
			{
				*tex_index2 = 4; // Texture de l'ennemi
				data->trace_data->hit = 0; // Permet l'affichage de l'ennemi
			}
		}
	}
}

void	calculate_distance(t_data *data)
{
	if (data->trace_data->side == 0)
		data->trace_data->perpWallDist = (data->trace_data->sideDistX - data->trace_data->deltaDistX);
	else
		data->trace_data->perpWallDist = (data->trace_data->sideDistY - data->trace_data->deltaDistY);

	//--------------------
	//double aspect_ratio = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	//data->trace_data->lineHeight = (int)((SCREEN_HEIGHT / data->trace_data->perpWallDist) * aspect_ratio);
	data->trace_data->lineHeight = (int)(SCREEN_HEIGHT / data->trace_data->perpWallDist);

	data->trace_data->drawStart = -data->trace_data->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawStart < 0)
		data->trace_data->drawStart = 0;

	data->trace_data->drawEnd = data->trace_data->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawEnd >= SCREEN_HEIGHT)
		data->trace_data->drawEnd = SCREEN_HEIGHT - 1;



	// Calcul de WallX pour déterminer quelle partie de la texture utiliser
	if (data->trace_data->side == 0)
		data->trace_data->WallX = data->map_data->pos_y + data->trace_data->perpWallDist * data->trace_data->rayDirY;
	else
		data->trace_data->WallX = data->map_data->pos_x + data->trace_data->perpWallDist * data->trace_data->rayDirX;
	data->trace_data->WallX -= floor(data->trace_data->WallX);

	// Calcul de la position X de la texture
	data->trace_data->texX = (int)(data->trace_data->WallX * (double)TEX_WIDTH);
	if (data->trace_data->side == 0 && data->trace_data->rayDirX > 0)
		data->trace_data->texX = TEX_WIDTH - data->trace_data->texX - 1;
	if (data->trace_data->side == 1 && data->trace_data->rayDirY < 0)
		data->trace_data->texX = TEX_HEIGHT - data->trace_data->texX - 1;

	data->trace_data->step = 1.0 * TEX_HEIGHT / data->trace_data->lineHeight;
	data->trace_data->texPos = (data->trace_data->drawStart - SCREEN_HEIGHT / 2 + data->trace_data->lineHeight / 2) * data->trace_data->step;
}

void	render_column(t_data *data, int x, int tex_index/*, int tex_index2*/)
{
	int	y;

	// Dessiner le plafond
	y = 0;
	while (y < data->trace_data->drawStart)
	{
		data->trace_data->buffer[y][x] = data->map_data->F_color;
		y++;
	}

	// Rendu des pixels pour chaque colonne
	y = data->trace_data->drawStart;
	while (y < data->trace_data->drawEnd)
	{
		data->trace_data->texY = (int)data->trace_data->texPos & (TEX_HEIGHT - 1);
		data->trace_data->texPos += data->trace_data->step;
		data->trace_data->color = get_pixel(data->mlx_data->texture[tex_index], data->trace_data->texX, data->trace_data->texY);

		// Assombrir les côtés si besoin
		if (data->trace_data->side == 1)
			data->trace_data->color = (data->trace_data->color >> 1) & 8355711;

		// Vérifier si la couleur est verte (RGB = 0x00FF00)
		//if (!is_near_green(data->trace_data->color, 100))
		data->trace_data->buffer[y][x] = data->trace_data->color;
		y++;
	}

	// Dessiner le sol
	while (y < SCREEN_HEIGHT)
	{
		data->trace_data->buffer[y][x] = data->map_data->C_color;
		y++;
	}
}



/*void resize_buffer_to_window(t_data *data, int new_width, int new_height)
{
    int x, y;
    int new_x, new_y;
    int color;
    double x_ratio, y_ratio;

    // Calcul des ratios de redimensionnement
    x_ratio = (double)SCREEN_WIDTH / new_width;
    y_ratio = (double)SCREEN_HEIGHT / new_height;

    // Créer un nouveau buffer pour l'image redimensionnée
    unsigned int **new_buffer = malloc(new_height * sizeof(int *));
    for (y = 0; y < new_height; y++)
    {
        new_buffer[y] = malloc(new_width * sizeof(int));
    }

    // Remplir le nouveau buffer avec les pixels redimensionnés
    for (y = 0; y < new_height; y++)
    {
        for (x = 0; x < new_width; x++)
        {
            new_x = (int)(x * x_ratio);
            new_y = (int)(y * y_ratio);

            // On récupère la couleur du buffer original
            color = data->trace_data->buffer[new_y][new_x];

            // On assigne la couleur au nouveau buffer
            new_buffer[y][x] = color;
        }
    }

    // Remplace l'ancien buffer par le nouveau
    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        free(data->trace_data->buffer[y]);
    }
    free(data->trace_data->buffer);

    data->trace_data->buffer = new_buffer;

    // Met à jour les dimensions de l'écran
   // SCREEN_WIDTH = new_width;
   // SCREEN_HEIGHT = new_height;
}*/







int	ft_render(t_data *data)
{
	int	x;
	int	tex_index;
	int	tex_index2;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		tex_index2 = -1;
		init_ray(data, x);
		dda_loop(data, &tex_index2);
		calculate_distance(data);

		// Détermination de la texture à utiliser en fonction du type de case
		if (data->trace_data->side == 0 && data->trace_data->stepX == 1)
			tex_index = 0;
		else if (data->trace_data->side == 0 && data->trace_data->stepX == -1)
			tex_index = 1;
		else if (data->trace_data->side == 1 && data->trace_data->stepY == 1)
			tex_index = 3;
		else if (data->trace_data->side == 1 && data->trace_data->stepY == -1)
			tex_index = 2;

		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY]
			== 'D' && data->bonus_data->door.is_open == 0)
			tex_index = 6; // Texture de la porte
		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY]
			== 'D' && data->bonus_data->door.is_open == 1)
			tex_index = get_door_texture_animation(data); // Texture de la porte


		render_column(data, x, tex_index/*, tex_index2*/);
		x++;
	}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		//tex_index2 = -1;
		init_ray2(data, x);
		dda_loop2(data, &tex_index2);
		calculate_distance2(data);

		// Détermination de la texture à utiliser en fonction du type de case
		if (data->trace_data->side == 0 && data->trace_data->stepX == 1)
			tex_index = 0;
		else if (data->trace_data->side == 0 && data->trace_data->stepX == -1)
			tex_index = 1;
		else if (data->trace_data->side == 1 && data->trace_data->stepY == 1)
			tex_index = 3;
		else if (data->trace_data->side == 1 && data->trace_data->stepY == -1)
			tex_index = 2;

		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY]
			== 'D' && data->bonus_data->door.is_open == 0)
			tex_index = 6; // Texture de la porte
		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY]
			== 'D' && data->bonus_data->door.is_open == 1)
			tex_index = get_door_texture_animation(data); // Texture de la porte
		int collectible_index = find_collectible_at(data->bonus_data, data->trace_data->mapX, data->trace_data->mapY);
		int ennemy_index = find_ennemy_at(data->bonus_data, data->trace_data->mapX, data->trace_data->mapY);
		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY]
			== 'C' && data->bonus_data->collectibles[collectible_index].is_collected == 0)
			tex_index = 5; // Texture de l'objet
		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY]
			== 'Z' && data->bonus_data->enemies[ennemy_index].is_alive == 1)
			tex_index = 4; // Texture de l'ennemy

		render_column2(data, x/*, tex_index*/, tex_index);
		x++;
	}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//resize_buffer_to_window(data, data->trace_data->w, data->trace_data->h);



	// Affichage des buffers et effacement de l'écran
	draw_buffer(data->trace_data);
	clear_buffer(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->mlx_data->img->img, 0, 0);
	return (0);
}
