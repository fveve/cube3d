/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:11:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/09 14:54:29 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void	init_ray2(t_data *data, int x)
{
	data->trace_data->camerax = (2 * x / (double)SCREEN_WIDTH - 1) * (SCREEN_WIDTH / (double)SCREEN_HEIGHT); //TODO TTTTEESSTT
	//data->trace_data->camerax = 2 * x / (double)SCREEN_WIDTH - 1;
	data->trace_data->raydirx = data->trace_data->dirx + data->trace_data->planex * data->trace_data->camerax;
	data->trace_data->raydiry = data->trace_data->diry + data->trace_data->planey * data->trace_data->camerax;
	data->trace_data->mapx = (int)data->map_data->pos_x;
	data->trace_data->mapy = (int)data->map_data->pos_y;

	// Initialisation des distances
	if (data->trace_data->raydirx == 0)
		data->trace_data->deltadistx = 1e30;
	else
		data->trace_data->deltadistx = ft_abs(1 / data->trace_data->raydirx);

	if (data->trace_data->raydiry == 0)
		data->trace_data->deltadisty = 1e30;
	else
		data->trace_data->deltadisty = ft_abs(1 / data->trace_data->raydiry);

	data->trace_data->hit = 0;

	// Calcul des steps et sideDist
	if (data->trace_data->raydirx < 0)
	{
		data->trace_data->stepx = -1;
		data->trace_data->sidedistx = (data->map_data->pos_x - data->trace_data->mapx) * data->trace_data->deltadistx;
	}
	else
	{
		data->trace_data->stepx = 1;
		data->trace_data->sidedistx = (data->trace_data->mapx + 1.0 - data->map_data->pos_x) * data->trace_data->deltadistx;
	}
	if (data->trace_data->raydiry < 0)
	{
		data->trace_data->stepy = -1;
		data->trace_data->sidedisty = (data->map_data->pos_y - data->trace_data->mapy) * data->trace_data->deltadisty;
	}
	else
	{
		data->trace_data->stepy = 1;
		data->trace_data->sidedisty = (data->trace_data->mapy + 1.0 - data->map_data->pos_y) * data->trace_data->deltadisty;
	}
}


void	dda_loop2(t_data *data, int *tex_index2)
{
	char	current_tile;
	int		collectible_index;

	while (data->trace_data->hit == 0)
	{
		if (data->trace_data->sidedistx < data->trace_data->sidedisty)
		{
			data->trace_data->sidedistx += data->trace_data->deltadistx;
			data->trace_data->mapx += data->trace_data->stepx;
			data->trace_data->side = 0;
		}
		else
		{
			data->trace_data->sidedisty += data->trace_data->deltadisty;
			data->trace_data->mapy += data->trace_data->stepy;
			data->trace_data->side = 1;
		}

		current_tile = data->map_data->map[data->trace_data->mapx][data->trace_data->mapy];

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
			collectible_index = find_collectible_at(data->bonus_data, data->trace_data->mapx, data->trace_data->mapy);
			if (collectible_index != -1 && data->bonus_data->collectibles[collectible_index].is_collected == 0)
			{
				*tex_index2 = 5; // Texture du collectible
				data->trace_data->hit = 1; // Permet l'affichage du collectible
			}
		}
		else if (current_tile == 'Z') // Collision avec un ennemi
		{
			collectible_index = find_ennemy_at(data->bonus_data, data->trace_data->mapx, data->trace_data->mapy);
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
		data->trace_data->perpwalldist = (data->trace_data->sidedistx - data->trace_data->deltadistx);
	else
		data->trace_data->perpwalldist = (data->trace_data->sidedisty - data->trace_data->deltadisty);

	//--------------------------------------------
	//double aspect_ratio = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	//data->trace_data->lineheight = (int)((SCREEN_HEIGHT / data->trace_data->perpwalldist) * aspect_ratio);
	data->trace_data->lineheight = (int)(SCREEN_HEIGHT / data->trace_data->perpwalldist);

	data->trace_data->drawstart = -data->trace_data->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawstart < 0)
		data->trace_data->drawstart = 0;

	data->trace_data->drawend = data->trace_data->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawend >= SCREEN_HEIGHT)
		data->trace_data->drawend = SCREEN_HEIGHT - 1;


	// Calcul de wallx pour déterminer quelle partie de la texture utiliser
	if (data->trace_data->side == 0)
		data->trace_data->wallx = data->map_data->pos_y + data->trace_data->perpwalldist * data->trace_data->raydiry;
	else
		data->trace_data->wallx = data->map_data->pos_x + data->trace_data->perpwalldist * data->trace_data->raydirx;
	data->trace_data->wallx -= floor(data->trace_data->wallx);

	// Calcul de la position X de la texture
	data->trace_data->texx = (int)(data->trace_data->wallx * (double)TEX_WIDTH);
	if (data->trace_data->side == 0 && data->trace_data->raydirx > 0)
		data->trace_data->texx = TEX_WIDTH - data->trace_data->texx - 1;
	if (data->trace_data->side == 1 && data->trace_data->raydiry < 0)
		data->trace_data->texx = TEX_HEIGHT - data->trace_data->texx - 1;

	data->trace_data->step = 1.0 * TEX_HEIGHT / data->trace_data->lineheight;
	data->trace_data->texpos = (data->trace_data->drawstart - SCREEN_HEIGHT / 2 + data->trace_data->lineheight / 2) * data->trace_data->step;
}


void	render_column2(t_data *data, int x/*, int tex_index*/, int tex_index2)
{
	int	y;

	//!!!!!!------> Affichage des objets et ennemis si présents
	if (tex_index2 != -1)
	{
		y = data->trace_data->drawstart;
		while (y < data->trace_data->drawend)
		{
			data->trace_data->texy = (int)data->trace_data->texpos & (TEX_HEIGHT - 1);
			data->trace_data->texpos += data->trace_data->step;
			data->trace_data->color = get_pixel(data->mlx_data->texture[tex_index2], data->trace_data->texx, data->trace_data->texy);

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
	data->trace_data->camerax = (2 * x / (double)SCREEN_WIDTH - 1) * (SCREEN_WIDTH / (double)SCREEN_HEIGHT); //TODO TTTTEESSTT
	//data->trace_data->camerax = 2 * x / (double)SCREEN_WIDTH - 1;
	data->trace_data->raydirx = data->trace_data->dirx + data->trace_data->planex * data->trace_data->camerax;
	data->trace_data->raydiry = data->trace_data->diry + data->trace_data->planey * data->trace_data->camerax;
	data->trace_data->mapx = (int)data->map_data->pos_x;
	data->trace_data->mapy = (int)data->map_data->pos_y;

	// Initialisation des distances
	if (data->trace_data->raydirx == 0)
		data->trace_data->deltadistx = 1e30;
	else
		data->trace_data->deltadistx = ft_abs(1 / data->trace_data->raydirx);

	if (data->trace_data->raydiry == 0)
		data->trace_data->deltadisty = 1e30;
	else
		data->trace_data->deltadisty = ft_abs(1 / data->trace_data->raydiry);

	data->trace_data->hit = 0;

	// Calcul des steps et sideDist
	if (data->trace_data->raydirx < 0)
	{
		data->trace_data->stepx = -1;
		data->trace_data->sidedistx = (data->map_data->pos_x - data->trace_data->mapx) * data->trace_data->deltadistx;
	}
	else
	{
		data->trace_data->stepx = 1;
		data->trace_data->sidedistx = (data->trace_data->mapx + 1.0 - data->map_data->pos_x) * data->trace_data->deltadistx;
	}
	if (data->trace_data->raydiry < 0)
	{
		data->trace_data->stepy = -1;
		data->trace_data->sidedisty = (data->map_data->pos_y - data->trace_data->mapy) * data->trace_data->deltadisty;
	}
	else
	{
		data->trace_data->stepy = 1;
		data->trace_data->sidedisty = (data->trace_data->mapy + 1.0 - data->map_data->pos_y) * data->trace_data->deltadisty;
	}
}

void	dda_loop(t_data *data, int *tex_index2)
{
	char	current_tile;
	int		collectible_index;

	while (data->trace_data->hit == 0)
	{
		if (data->trace_data->sidedistx < data->trace_data->sidedisty)
		{
			data->trace_data->sidedistx += data->trace_data->deltadistx;
			data->trace_data->mapx += data->trace_data->stepx;
			data->trace_data->side = 0;
		}
		else
		{
			data->trace_data->sidedisty += data->trace_data->deltadisty;
			data->trace_data->mapy += data->trace_data->stepy;
			data->trace_data->side = 1;
		}

		current_tile = data->map_data->map[data->trace_data->mapx][data->trace_data->mapy];

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
			collectible_index = find_collectible_at(data->bonus_data, data->trace_data->mapx, data->trace_data->mapy);
			if (collectible_index != -1 && data->bonus_data->collectibles[collectible_index].is_collected == 0)
			{
				*tex_index2 = 5; // Texture du collectible
				data->trace_data->hit = 0; // Permet l'affichage du collectible
			}
		}
		else if (current_tile == 'Z') // Collision avec un ennemi
		{
			collectible_index = find_ennemy_at(data->bonus_data, data->trace_data->mapx, data->trace_data->mapy);
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
		data->trace_data->perpwalldist = (data->trace_data->sidedistx - data->trace_data->deltadistx);
	else
		data->trace_data->perpwalldist = (data->trace_data->sidedisty - data->trace_data->deltadisty);

	//--------------------
	//double aspect_ratio = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	//data->trace_data->lineheight = (int)((SCREEN_HEIGHT / data->trace_data->perpwalldist) * aspect_ratio);
	data->trace_data->lineheight = (int)(SCREEN_HEIGHT / data->trace_data->perpwalldist);

	data->trace_data->drawstart = -data->trace_data->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawstart < 0)
		data->trace_data->drawstart = 0;

	data->trace_data->drawend = data->trace_data->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (data->trace_data->drawend >= SCREEN_HEIGHT)
		data->trace_data->drawend = SCREEN_HEIGHT - 1;



	// Calcul de wallx pour déterminer quelle partie de la texture utiliser
	if (data->trace_data->side == 0)
		data->trace_data->wallx = data->map_data->pos_y + data->trace_data->perpwalldist * data->trace_data->raydiry;
	else
		data->trace_data->wallx = data->map_data->pos_x + data->trace_data->perpwalldist * data->trace_data->raydirx;
	data->trace_data->wallx -= floor(data->trace_data->wallx);

	// Calcul de la position X de la texture
	data->trace_data->texx = (int)(data->trace_data->wallx * (double)TEX_WIDTH);
	if (data->trace_data->side == 0 && data->trace_data->raydirx > 0)
		data->trace_data->texx = TEX_WIDTH - data->trace_data->texx - 1;
	if (data->trace_data->side == 1 && data->trace_data->raydiry < 0)
		data->trace_data->texx = TEX_HEIGHT - data->trace_data->texx - 1;

	data->trace_data->step = 1.0 * TEX_HEIGHT / data->trace_data->lineheight;
	data->trace_data->texpos = (data->trace_data->drawstart - SCREEN_HEIGHT / 2 + data->trace_data->lineheight / 2) * data->trace_data->step;
}

void	render_column(t_data *data, int x, int tex_index/*, int tex_index2*/)
{
	int	y;

	// Dessiner le plafond
	y = 0;
	while (y < data->trace_data->drawstart)
	{
		data->trace_data->buffer[y][x] = data->map_data->f_color;
		y++;
	}

	// Rendu des pixels pour chaque colonne
	y = data->trace_data->drawstart;
	while (y < data->trace_data->drawend)
	{
		data->trace_data->texy = (int)data->trace_data->texpos & (TEX_HEIGHT - 1);
		data->trace_data->texpos += data->trace_data->step;
		data->trace_data->color = get_pixel(data->mlx_data->texture[tex_index], data->trace_data->texx, data->trace_data->texy);

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
		data->trace_data->buffer[y][x] = data->map_data->c_color;
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
		if (data->trace_data->side == 0 && data->trace_data->stepx == 1)
			tex_index = 0;
		else if (data->trace_data->side == 0 && data->trace_data->stepx == -1)
			tex_index = 1;
		else if (data->trace_data->side == 1 && data->trace_data->stepy == 1)
			tex_index = 3;
		else if (data->trace_data->side == 1 && data->trace_data->stepy == -1)
			tex_index = 2;
		if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
			== 'D' && data->bonus_data->door.is_open == 0)
			tex_index = 6;
		if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
			== 'D' && data->bonus_data->door.is_open == 1)
			tex_index = get_door_texture_animation(data);
		render_column(data, x, tex_index);
		x++;
	}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray2(data, x);
		dda_loop2(data, &tex_index2);
		calculate_distance2(data);
		if (data->trace_data->side == 0 && data->trace_data->stepx == 1)
			tex_index = 0;
		else if (data->trace_data->side == 0 && data->trace_data->stepx == -1)
			tex_index = 1;
		else if (data->trace_data->side == 1 && data->trace_data->stepy == 1)
			tex_index = 3;
		else if (data->trace_data->side == 1 && data->trace_data->stepy == -1)
			tex_index = 2;
		if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
			== 'D' && data->bonus_data->door.is_open == 0)
			tex_index = 6;
		if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
			== 'D' && data->bonus_data->door.is_open == 1)
			tex_index = get_door_texture_animation(data);
		int collectible_index = find_collectible_at(data->bonus_data,
			data->trace_data->mapx, data->trace_data->mapy);
		int ennemy_index = find_ennemy_at(data->bonus_data,
			data->trace_data->mapx, data->trace_data->mapy);
		if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
			== 'C' && data->bonus_data->collectibles
			[collectible_index].is_collected == 0)
			tex_index = 5;
		if (data->map_data->map[data->trace_data->mapx][data->trace_data->mapy]
			== 'Z' && data->bonus_data->enemies[ennemy_index].is_alive == 1)
			tex_index = 4;
		render_column2(data, x, tex_index);
		x++;
	}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	draw_buffer(data->trace_data);
	clear_buffer(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->mlx_data->img->img, 0, 0);
	return (0);
}
