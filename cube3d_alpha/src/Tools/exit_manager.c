/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:39:23 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/09 14:33:48 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_tab_text_error(t_img **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

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
	if (data->img != NULL)
	{
		mlx_destroy_image(mlx, data->img);
	}
	free(data);
}

void	free_mlx_data(t_mlx_data *data)
{
	int	x;

	x = 0;
	free_img_data(data->mlx, data->img);
	while (x < 37)
	{
		if (data->texture[x])
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
	while (x < 4)   //!! (16) !!!??????????????
	{
		free(map_data->texture_txt[x]);
		x++;
	}
	free(map_data);
}

void	free_bonus_data(t_bonus_data *bonus_data)
{
	//if (bonus_data->door)
	//	free(bonus_data->door);  // Libère la mémoire allouée pour les portes
	if (bonus_data->enemies)
		free(bonus_data->enemies);  // Libère la mémoire allouée pour les ennemis
	//if (bonus_data->projectiles)
	//	free(bonus_data->projectiles);  // Libère la mémoire allouée pour les projectiles
	if (bonus_data->collectibles)
		free(bonus_data->collectibles);  // Libère la mémoire allouée pour les collectibles
	
	free(bonus_data);  // Libère la structure bonus_data elle-même
}

int	exit_error_message(t_data *data, char *message)
{
	printf("%s\n", message);
	exit_manager(data);
	return (1);
}

int	exit_error_text(t_data *data)
{
	if (data->bonus_data->cinematic)
		free_cinematic_images(data, data->bonus_data->num_cinematic1);

	free_map_data(data->map_data);
	free(data->mlx_data->mlx);
	free(data->mlx_data);
	free_bonus_data(data->bonus_data);
	free(data->trace_data);
	//free(data);//!!!
	pkill_paplay();
	exit(0);
	return (0);
}

int	exit_manager(t_data *data)
{
	if (data->bonus_data->cinematic)
		free_cinematic_images(data, data->bonus_data->num_cinematic1);

	free_map_data(data->map_data);
	free_mlx_data(data->mlx_data);
	free_bonus_data(data->bonus_data);
	free(data->trace_data);
	//free(data);//!!!
	pkill_paplay();
	exit(0);
	return (0);
}
