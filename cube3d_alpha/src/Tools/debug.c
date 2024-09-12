/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:33:34 by arafa             #+#    #+#             */
/*   Updated: 2024/09/12 11:32:41 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_map_data(t_map_data *map_data);

void	free_bonus_data(t_bonus_data *bonus_data);

void	print_tab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		printf("%s\n", tab[x]);
		x++;
	}
	printf("\n");
}

void	print_map_data(t_map_data *map_data)
{
	printf("NO : %s\n", map_data->texture_txt[0]);
	printf("SO : %s\n", map_data->texture_txt[1]);
	printf("WE : %s\n", map_data->texture_txt[2]);
	printf("EA : %s\n", map_data->texture_txt[3]);
}

int	exit_error_message(t_data *data, char *message)
{
	printf("%s\n", message);
	exit_error_text(data);
	return (1);
}

int	exit_error_text(t_data *data)
{
	if (data->bonus_data->cinematic)
	{
		free_bonus_data(data->bonus_data);
		free_cinematic_images(data, data->bonus_data->num_cinematic1);
	}
	if (data->map_data)
		free_map_data(data->map_data);
	if (data->mlx_data->mlx)
		free(data->mlx_data->mlx);
	if (data->mlx_data)
		free(data->mlx_data);
	if (data->bonus_data)
		free(data->bonus_data);
	if (data->trace_data)
		free(data->trace_data);
	pkill_paplay();
	exit(0);
	return (0);
}
