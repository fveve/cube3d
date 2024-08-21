/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:33:34 by arafa             #+#    #+#             */
/*   Updated: 2024/08/19 13:35:36 by joncurci         ###   ########.fr       */
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
	printf("NO : %s\n", map_data->texture_txt[0]);
	printf("SO : %s\n", map_data->texture_txt[1]);
	printf("WE : %s\n", map_data->texture_txt[2]);
	printf("EA : %s\n", map_data->texture_txt[3]);
}
