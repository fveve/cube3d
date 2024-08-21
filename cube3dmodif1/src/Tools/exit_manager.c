/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:39:23 by joncurci          #+#    #+#             */
/*   Updated: 2024/08/19 13:39:27 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_tab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	if (tab)
		free(tab);
}

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
	while (x < 4)
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
	if (map_data->C)
		free(map_data->C);
	if (map_data->F)
		free(map_data->F);
	while (x < 4)
	{
		free(map_data->texture_txt[x]);
		x++;
	}
	free(map_data);
}

int	exit_manager(t_data *data)
{
	free_map_data(data->map_data);
	free_mlx_data(data->mlx_data);
	free(data->trace_data);
	exit(0);
	return (0);
}
