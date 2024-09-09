/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:53:41 by arafa             #+#    #+#             */
/*   Updated: 2024/09/09 12:53:58 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_map_data2(t_map_data *data)
{
	data->F = NULL;
	data->C = NULL;
	data->map = NULL;
}

void	init_map_data(t_map_data *data, char **argv)
{
	data->pos_x = 0.0;
	data->pos_y = 0.0;
	data->texture_txt[0] = NULL;
	data->texture_txt[1] = NULL;
	data->texture_txt[2] = NULL;
	data->texture_txt[3] = NULL;
	data->texture_txt[4] = NULL;
	data->texture_txt[5] = NULL;
	data->texture_txt[6] = NULL;
	data->texture_txt[7] = NULL;
	data->texture_txt[8] = NULL;
	data->texture_txt[9] = NULL;
	data->texture_txt[10] = NULL;
	data->texture_txt[11] = NULL;
	data->texture_txt[12] = NULL;
	data->texture_txt[13] = NULL;
	data->texture_txt[14] = NULL;
	data->texture_txt[15] = NULL;
	init_map_data2(data);
	data->num_doors = 0;
	data->num_ennemies = 0;
	data->num_collectibles = 0;
	data->num_exit = 0;
	data->exit_is_open = 0;
	parse_map(data, argv[1]);
}
