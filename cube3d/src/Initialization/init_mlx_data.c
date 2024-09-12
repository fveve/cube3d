/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:53:43 by arafa             #+#    #+#             */
/*   Updated: 2024/09/09 12:54:00 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_mlx_data3(t_mlx_data *data, int *x)
{
	data->texture[(*x)++] = init_img(data->mlx, TEX_ENEMY, 1);
	data->texture[(*x)++] = init_img(data->mlx, TEX_COLLECTIBLE, 1);
	data->texture[(*x)++] = init_img(data->mlx, TEX_DOOR_CLOSED, 1);
	data->texture[(*x)++] = init_img(data->mlx, TEX_DOOR_CHEVRON1, 1);
	data->texture[(*x)++] = init_img(data->mlx, TEX_DOOR_CHEVRON2, 1);
	data->texture[(*x)++] = init_img(data->mlx, TEX_DOOR_CHEVRON3, 1);
	data->texture[(*x)++] = init_img(data->mlx, TEX_DOOR_CHEVRON4, 1);
	data->texture[(*x)++] = init_img(data->mlx, TEX_DOOR_CHEVRON5, 1);
	data->texture[(*x)++] = init_img(data->mlx, TEX_DOOR_CHEVRON6, 1);
}

void	init_mlx_data2(t_mlx_data *data, int x)
{
	init_mlx_data3(data, &x);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_CHEVRON7, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING1, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING2, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING3, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING4, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING5, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING6, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING7, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING8, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING9, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING10, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING11, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING12, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING13, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING14, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING15, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING16, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN1, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN2, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN3, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN4, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN5, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN6, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN7, 1);
}

void	init_mlx_data(t_data *_data, t_mlx_data *data, char *texture[37])
{
	int	x;

	x = 0;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "boxeo");
	while (x < 4)
	{
		data->texture[x] = init_img(data->mlx, texture[x], 1);
		x++;
	}
	// Charger les 12 nouvelles textures supplémentaires (ciel, sol, portes, ennemis, collectibles, etc.)
	init_mlx_data2(data, x);
	x = 0;
	while (x < 37)
	{
		if (!data->texture[x])
		{
			printf("Error loading texture at index %d\n", x);
			exit_manager(_data);
		}
		x++;
	}
	data->img = init_img(data->mlx, "", 0);
}
