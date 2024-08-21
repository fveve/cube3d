/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:11:06 by joncurci          #+#    #+#             */
/*   Updated: 2024/08/20 16:51:03 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_render(t_data *data)
{
	int	*texture[8];
	int	z;
	int	x;
	int	y;
	int	count;

	z = 0;
	while (z < 4)
	{
		texture[z] = malloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH);
		x = 0;
		while (x < TEX_WIDTH)
		{
			y = 0;
			while (y < TEX_HEIGHT)
			{
				texture[z][TEX_HEIGHT * y + x]
					= get_pixel(data->mlx_data->texture[z], x, y);
				y++;
			}
			x++;
		}
		z++;
	}
	count = 0;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		if (count == SCREEN_HEIGHT)
			count = 0;
		data->trace_data->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		data->trace_data->rayDirX = data->trace_data->dirX
			+ data->trace_data->planeX * data->trace_data->cameraX;
		data->trace_data->rayDirY = data->trace_data->dirY
			+ data->trace_data->planeY * data->trace_data->cameraX;
		data->trace_data->mapX = (int)data->map_data->pos_x;
		data->trace_data->mapY = (int)data->map_data->pos_y;
		// Remplacement des ternaires
		if (data->trace_data->rayDirX == 0)
			data->trace_data->deltaDistX = 1e30;
		else
			data->trace_data->deltaDistX = ft_abs(1
					/ data->trace_data->rayDirX);
		if (data->trace_data->rayDirY == 0)
			data->trace_data->deltaDistY = 1e30;
		else
			data->trace_data->deltaDistY = ft_abs(1
					/ data->trace_data->rayDirY);
		data->trace_data->hit = 0;
		// Initialisation des steps et sideDist
		if (data->trace_data->rayDirX < 0)
		{
			data->trace_data->stepX = -1;
			data->trace_data->sideDistX = (data->map_data->pos_x
					- data->trace_data->mapX) * data->trace_data->deltaDistX;
		}
		else
		{
			data->trace_data->stepX = 1;
			data->trace_data->sideDistX = (data->trace_data->mapX + 1.0
					- data->map_data->pos_x) * data->trace_data->deltaDistX;
		}
		if (data->trace_data->rayDirY < 0)
		{
			data->trace_data->stepY = -1;
			data->trace_data->sideDistY = (data->map_data->pos_y
					- data->trace_data->mapY) * data->trace_data->deltaDistY;
		}
		else
		{
			data->trace_data->stepY = 1;
			data->trace_data->sideDistY = (data->trace_data->mapY + 1.0
					- data->map_data->pos_y) * data->trace_data->deltaDistY;
		}
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
			if (data->map_data->map[data->trace_data->mapX]
				[data->trace_data->mapY] == '1')
				data->trace_data->hit = 1;
		}
		// Remplacement des ternaires pour perpWallDist
		if (data->trace_data->side == 0)
			data->trace_data->perpWallDist = (data->trace_data->sideDistX
					- data->trace_data->deltaDistX);
		else
			data->trace_data->perpWallDist = (data->trace_data->sideDistY
					- data->trace_data->deltaDistY);
		data->trace_data->lineHeight = (int)(SCREEN_HEIGHT
				/ data->trace_data->perpWallDist);
		data->trace_data->drawStart = (data->trace_data->lineHeight * -1)
			/ 2 + SCREEN_HEIGHT / 2;
		if (data->trace_data->drawStart < 0)
			data->trace_data->drawStart = 0;
		data->trace_data->drawEnd = data->trace_data->lineHeight
			/ 2 + SCREEN_HEIGHT / 2;
		if (data->trace_data->drawEnd >= SCREEN_HEIGHT)
			data->trace_data->drawEnd = SCREEN_HEIGHT - 1;
		// Calcul de WallX
		if (data->trace_data->side == 0)
			data->trace_data->WallX = data->map_data->pos_y
				+ data->trace_data->perpWallDist * data->trace_data->rayDirY;
		else
			data->trace_data->WallX = data->map_data->pos_x
				+ data->trace_data->perpWallDist * data->trace_data->rayDirX;
		data->trace_data->WallX -= floor(data->trace_data->WallX);
		data->trace_data->texX = (int)(data->trace_data->WallX
				* (double)TEX_WIDTH);
		if (data->trace_data->side == 0 && data->trace_data->rayDirX > 0)
			data->trace_data->texX = TEX_WIDTH - data->trace_data->texX - 1;
		if (data->trace_data->side == 1 && data->trace_data->rayDirY < 0)
			data->trace_data->texX = TEX_HEIGHT - data->trace_data->texX - 1;
		data->trace_data->step = 1.0 * TEX_HEIGHT
			/ data->trace_data->lineHeight;
		data->trace_data->texPos = (data->trace_data->drawStart
				- SCREEN_HEIGHT / 2 + data->trace_data->lineHeight
				/ 2) * data->trace_data->step;
		// Dessin de la texture sur l'écran
		y = 0;
		while (y < data->trace_data->drawStart)
		{
			data->trace_data->buffer[y][x] = data->map_data->F_color;
			y++;
		}
		while (y < data->trace_data->drawEnd)
		{
			data->trace_data->texY = (int)data->trace_data->texPos
				& (TEX_HEIGHT - 1);
			data->trace_data->texPos += data->trace_data->step;
			if (data->trace_data->side == 0 && data->trace_data->stepX == 1)
				data->trace_data->color = texture[0][TEX_HEIGHT
					* data->trace_data->texY + data->trace_data->texX];
			else if (data->trace_data->side == 0)
				data->trace_data->color = texture[1][TEX_HEIGHT
					* data->trace_data->texY + data->trace_data->texX];
			else if (data->trace_data->stepY == 1)
				data->trace_data->color = texture[3][TEX_HEIGHT
					* data->trace_data->texY + data->trace_data->texX];
			else
				data->trace_data->color = texture[2][TEX_HEIGHT
					* data->trace_data->texY + data->trace_data->texX];
			if (data->trace_data->side == 1)
				data->trace_data->color = (data->trace_data->color >> 1)
					& 8355711;
			data->trace_data->buffer[y][x] = data->trace_data->color;
			y++;
		}
		while (y < SCREEN_HEIGHT)
		{
			data->trace_data->buffer[y][x] = data->map_data->C_color;
			y++;
		}
		count++;
		x++;
	}
	z = 0;
	while (z < 4)
	{
		free(texture[z]);
		z++;
	}
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

	draw_minimap(data);//! TESSSTTTT
	//draw_minimap_player(data);//! TESSSTTTT

	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
		data->mlx_data->img->img, 0, 0);
	return (0);
}
