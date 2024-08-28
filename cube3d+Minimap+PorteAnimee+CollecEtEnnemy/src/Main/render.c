/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:11:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/08/28 21:49:31 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void	init_ray2(t_data *data, int x)
{
	data->trace_data->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
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

void	render_column2(t_data *data, int x, int tex_index, int tex_index2)
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


//!!!------ test avec objets et ennemies sans fond vert.
/*int	ft_render(t_data *data)
{
	int	x;
	int	y;
	int	count;
	int	collectible_index;
	int tex_index;
	int tex_index2;
	char current_tile;

	x = 0;
	count = 0;

	while (x < SCREEN_WIDTH)
	{
		if (count == SCREEN_HEIGHT)
			count = 0;

		// Calcul des rayons pour chaque colonne de l'écran
		data->trace_data->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
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




		// Boucle de DDA pour trouver la distance au mur ou à la porte
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
					// La porte fermée se comporte comme un mur
					data->trace_data->hit = 1;
				}
				else if (data->bonus_data->door.is_open == 1) // Si la porte est ouverte
				{
					// La porte ouverte doit être rendue mais le joueur peut passer à travers
					data->trace_data->hit = 1; // Rend la porte tout en permettant de traverser
				}
			}
			//!-------------------------------------------------------------------------
			else if (current_tile == 'C') // Collision avec un collectible
			{
				collectible_index = find_collectible_at(data->bonus_data, data->trace_data->mapX,
															data->trace_data->mapY);
				if (collectible_index != -1 && data->bonus_data->collectibles
								[collectible_index].is_collected == 0)// Si l'objet n'est pas collecte'
				{
					//printf("COLLEX INDEX == %d \n", collectible_index);
					// L'objet se voit comme un mur
					data->trace_data->hit = 1; //TODO pour afficher ou pas l'objet, ici 0 = pas afficher
					tex_index2 = 13;
				}
			}
			else if (current_tile == 'Z') // Collision avec un ennemy
			{
				collectible_index = find_ennemy_at(data->bonus_data, data->trace_data->mapX,
															data->trace_data->mapY);
				if (collectible_index != -1 && data->bonus_data->enemies
								[collectible_index].is_alive == 1)// Si l'ennemy est vivant'
				{
					//printf("ENEMYX INDEX == %d \n", ennemy_index);
					// L'ennemy se voit comme un mur
					data->trace_data->hit = 1; //TODO pour afficher ou pas l'objet, ici 0 = pas afficher
					tex_index2 = 10;
				}
			}
			//!-------------------------------------------------------------------------
		}




		// Calcul de la distance perpendiculaire au mur
		if (data->trace_data->side == 0)
			data->trace_data->perpWallDist = (data->trace_data->sideDistX - data->trace_data->deltaDistX);
		else
			data->trace_data->perpWallDist = (data->trace_data->sideDistY - data->trace_data->deltaDistY);

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


		// --------Dessiner le plafond--------------------
		y = 0;
		while (y < data->trace_data->drawStart)
		{
			data->trace_data->buffer[y][x] = data->map_data->F_color;
			y++;
		}
		//------------------------------------------
	//!--------------------------------------------------------------------------------------
		// Détermination de la texture à utiliser en fonction du type de case
		//int tex_index;


		if (data->trace_data->side == 0 && data->trace_data->stepX == 1)
			tex_index = 0; // Texture du 1er mur
		else if (data->trace_data->side == 0 && data->trace_data->stepX == -1)
			tex_index = 1; // Texture du 2eme mur
		else if (data->trace_data->side == 1 && data->trace_data->stepY == 1)
			tex_index = 3; // Texture du 3eme mur
		else if (data->trace_data->side == 1 && data->trace_data->stepY == -1)
		tex_index = 2; // Texture du 4eme mur


		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY] == 'D' && data->bonus_data->door.is_open == 0)
			tex_index = 6; // Texture de la porte
		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY] == 'D' && data->bonus_data->door.is_open == 1)
			tex_index = 7; // Texture de la porte



		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY] == 'C')
		{
			collectible_index = find_collectible_at(data->bonus_data, data->trace_data->mapX, data->trace_data->mapY);
			if (collectible_index != -1 && data->bonus_data->collectibles[collectible_index].is_collected == 0)
			{
				tex_index = 13;  // Texture du collectible non collecté
			}
		}

		if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY] == 'Z')
		{
			collectible_index = find_ennemy_at(data->bonus_data, data->trace_data->mapX, data->trace_data->mapY);
			if (collectible_index != -1 && data->bonus_data->enemies[collectible_index].is_alive == 1)
			{
				tex_index = 10;  // Texture de l'ennemy
			}
		}

		



		y = data->trace_data->drawStart;
		while (y < data->trace_data->drawEnd)
		{
			data->trace_data->texY = (int)data->trace_data->texPos & (TEX_HEIGHT - 1);
			data->trace_data->texPos += data->trace_data->step;
			data->trace_data->color = get_pixel(data->mlx_data->texture[tex_index], data->trace_data->texX, data->trace_data->texY);
			
			 // Vérifier si la couleur est verte (RGB = 0x00FF00)
			if (!is_near_green(data->trace_data->color, 100))
			{
				// Si la face est sur les côtés, on assombrit la couleur
				if (data->trace_data->side == 1)
				{
					data->trace_data->color = (data->trace_data->color >> 1) & 8355711; // Assombrir les côtés
				}

				// Dessiner le pixel dans le buffer
				data->trace_data->buffer[y][x] = data->trace_data->color;
			}
		//	if (data->trace_data->side == 1)
		//		data->trace_data->color = (data->trace_data->color >> 1) & 8355711; // Assombrir les côtés

		//	data->trace_data->buffer[y][x] = data->trace_data->color;
			y++;
		}
		


	//!!--------------------------------------------------------------------------------------
		// Dessiner le sol
		while (y < SCREEN_HEIGHT)
		{
			data->trace_data->buffer[y][x] = data->map_data->C_color;
			y++;
		}
		x++;
	}
	//--------------------------------------

	
	
	// Affichage des buffers et effacement de l'écran

	
	draw_buffer(data->trace_data);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			data->trace_data->buffer[y][x] = 0;
			x++;
		}
		y++;
	}

	// Appel au rendu de la minimap
	draw_minimap(data);

	// Afficher l'image sur la fenêtre
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->mlx_data->img->img, 0, 0);
	return (0);
}*/


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
	data->trace_data->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
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

void	render_column(t_data *data, int x, int tex_index, int tex_index2)
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


		render_column(data, x, tex_index, tex_index2);
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

		render_column2(data, x, tex_index, tex_index);
		x++;
	}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// Affichage des buffers et effacement de l'écran
	draw_buffer(data->trace_data);
	clear_buffer(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->mlx_data->img->img, 0, 0);
	return (0);
}
