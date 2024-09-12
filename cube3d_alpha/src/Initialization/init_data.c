/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:46 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/12 11:30:46 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_bonus_data(t_data *data);

void	init_doors(t_map_data *map_data, t_bonus_data *bonus_data);

void	init_enemies(t_map_data *map_data, t_bonus_data *bonus_data);

void	init_collectibles(t_map_data *map_data, t_bonus_data *bonus_data);

t_img	*init_img(void *mlx, char *texture, int trigger)
{
	t_img	*data;
	int		h;
	int		w;

	w = TEX_WIDTH;
	h = TEX_HEIGHT;
	data = malloc(sizeof(t_img));
	if (trigger == 0)
		data->img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	else
		data->img = mlx_xpm_file_to_image(mlx, texture, &w, &h);
	if (!data->img)
	{
		free (data);
		return (NULL);
	}
	if (data->img)
		data->addr = mlx_get_data_addr(data->img,
				&data->bits_per_pixel,
				&data->line_length,
				&data->endian);
	return (data);
}

void	init_data(t_data *data, char **argv)
{
	int	x;

	x = 0;
	data->map_data = NULL;
	data->trace_data = NULL;
	data->mlx_data = NULL;
	data->bonus_data = NULL;
	data->map_data = (t_map_data *)malloc(sizeof(t_map_data));
	data->mlx_data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	data->bonus_data = (t_bonus_data *)malloc(sizeof(t_bonus_data));
	data->bonus_data->cinematic = NULL;
	data->bonus_data->collectibles = NULL;
	data->bonus_data->enemies = NULL;
	data->mlx_data->mlx = NULL;
	init_map_data(data, data->map_data, argv);
	init_doors(data->map_data, data->bonus_data);
	init_enemies(data->map_data, data->bonus_data);
	init_collectibles(data->map_data, data->bonus_data);
	check_error(data, *data->map_data);
	data->trace_data = (t_trace_data *)malloc(sizeof(t_trace_data));
	init_trace_data(data->map_data, data->trace_data, data->mlx_data);
	init_bonus_data(data);
	init_mlx_data(data, data->mlx_data, data->map_data->texture_txt);
	calculate_map_size(data);
}
