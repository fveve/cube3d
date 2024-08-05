/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:33:34 by arafa             #+#    #+#             */
/*   Updated: 2024/07/30 09:55:28 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	printf("%s\n", map_data->NO);
	printf("%s\n", map_data->SO);
	printf("%s\n", map_data->EA);
	printf("%s\n", map_data->WE);
}