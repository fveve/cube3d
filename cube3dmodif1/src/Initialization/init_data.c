/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:46 by joncurci          #+#    #+#             */
/*   Updated: 2024/08/19 17:53:37 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_img	*init_img(void *mlx, char *texture, int trigger)
{
	t_img	*data;
	int		h;
	int		w;

	w = TEX_WIDTH;
	h = TEX_HEIGHT;
	data = malloc(sizeof(t_img));
	//data->img = (trigger == 0) ? mlx_new_image(mlx, SCREEN_HEIGHT, SCREEN_WIDTH) : mlx_xpm_file_to_image(mlx, texture, &w, &h);
	if (trigger == 0)
		data->img = mlx_new_image(mlx, SCREEN_HEIGHT, SCREEN_WIDTH);
	else
		data->img = mlx_xpm_file_to_image(mlx, texture, &w, &h);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian);
	return (data);
}

void	init_mlx_data(t_mlx_data *data, char *texture[4])
{
	int	x;

	x = 0;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, SCREEN_HEIGHT,
			SCREEN_WIDTH, "boxeo");
	while (x < 4)
	{
		data->texture[x] = init_img(data->mlx, texture[x], 1);
		x++;
	}
	data->img = init_img(data->mlx, "", 0);
}

void	init_map_data(t_map_data *data, char **argv)
{
	data->pos_x = 0.0;
	data->pos_y = 0.0;
	data->texture_txt[0] = NULL;
	data->texture_txt[1] = NULL;
	data->texture_txt[2] = NULL;
	data->texture_txt[3] = NULL;
	data->F = NULL;
	data->C = NULL;
	data->map = NULL;
	parse_map(data, argv[1]);
}

void	init_trace_data(t_map_data *map_data,
		t_trace_data *data, t_mlx_data *mlx_data)
{
	data->cameraX = 0;
	data->rayDirX = 0;
	data->rayDirY = 0;
	data->mapX = (int)map_data->pos_x;
	data->mapY = (int)map_data->pos_y;
	data->deltaDistX = 0;
	data->deltaDistY = 0;
	data->perpWallDist = 0;
	data->stepX = 0;
	data->stepY = 0;
	data->hit = 0;
	data->side = 0;
	data->lineHeight = 0;
	data->drawStart = 0;
	data->drawEnd = 0;
	data->oldDirX = 0;
	data->oldPlaneX = 0;
	data->moveSpeed = 0.09;
	data->rotSpeed = 0.05;
	data->map_data = map_data;
	data->mlx_data = mlx_data;
	data->h = 0;
	data->w = 0;
	data->texX = 0;
	data->color = 0;
	data->texY = 0;
	data->texPos = 0;
	//  |  Initialisation of the direction the player is facing   |
	//	V														  V
	if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'W')
	{
		data->dirX = 0;
		data->dirY = -1;
		data->planeX = -0.66;
		data->planeY = 0;
	}
	else if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'E')
	{
		data->dirX = 0;
		data->dirY = 1;
		data->planeX = 0.66;
		data->planeY = 0;
	}
	else if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'N')
	{
		data->dirX = -1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = 0.66;
	}
	else
	{
		data->dirX = 1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = -0.66;
	}
}

void	init_data(t_data *data, char **argv)
{
	data->map_data = (t_map_data *)malloc(sizeof(t_map_data));
	data->trace_data = (t_trace_data *)malloc(sizeof(t_trace_data));
	data->mlx_data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	init_map_data(data->map_data, argv);//initalize the structure containing all the map information
	check_error(data, *data->map_data);//check if the .cub file is correct
	init_trace_data(data->map_data, data->trace_data, data->mlx_data);//initalize the structure containing
												//all the render info , all the variables necessary for the calculations
												// and the textures
	init_mlx_data(data->mlx_data, data->map_data->texture_txt);//initalize the structure containing all the mlx related infos
																//and the textures path

	//!----------------------------TEEEST

	calculate_map_size(data);
	printf("h = %d\n", data->trace_data->h);//! TEEEST
	printf("w = %d\n", data->trace_data->w);//! TEEEST
	//!----------------------------TEEEST
}
