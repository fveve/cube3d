/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:39:23 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/12 11:29:10 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_img_data(void *mlx, t_img *data)
{
	mlx_destroy_image(mlx, data->img);
	free(data);
}

void	free_mlx_data(t_mlx_data *data)
{
	int	x;

	x = 0;
	free_img_data(data->mlx, data->img);
	while (x < 37)
	{
		free_img_data(data->mlx, data->texture[x]);
		x++;
	}
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
}

void	free_map_data(t_map_data *map_data)
{
	int	x;

	x = 0;
	if (map_data->map)
		free_tab(map_data->map);
	if (map_data->c)
		free(map_data->c);
	if (map_data->f)
		free(map_data->f);
	while (x < 16)
	{
		free(map_data->texture_txt[x]);
		x++;
	}
	free(map_data);
}

void	free_bonus_data(t_bonus_data *bonus_data)
{
	if (bonus_data->enemies)
		free(bonus_data->enemies);
	if (bonus_data->collectibles)
		free(bonus_data->collectibles);
	free(bonus_data);
}

int	exit_manager(t_data *data)
{
	if (data->bonus_data->cinematic)
		free_cinematic_images(data, data->bonus_data->num_cinematic1);
	free_map_data(data->map_data);
	free_mlx_data(data->mlx_data);
	free_bonus_data(data->bonus_data);
	free(data->trace_data);
	pkill_paplay();
	exit(0);
	return (0);
}
