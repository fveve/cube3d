/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:37:43 by arafa             #+#    #+#             */
/*   Updated: 2024/09/09 14:53:36 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_removable(char *s)
{
	int	x;
	int	trigger;

	x = 0;
	trigger = 0;
	while (s[x])
	{
		if (s[x] == '1' || s[x] == '0')
			trigger++;
		x++;
	}
	if (!trigger)
		return (1);
	return (0);
}
