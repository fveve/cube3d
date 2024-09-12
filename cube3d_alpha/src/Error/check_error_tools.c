/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:07:47 by arafa             #+#    #+#             */
/*   Updated: 2024/09/10 16:08:50 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_boder(char **map, int x, int y)
{
	return (!map[x][y + 1] || map[x][y + 1] == '\n'
				|| !map[x + 1][y] || map[x + 1][y] == '\n'
				|| (x != 0 && !map[x - 1][y])
				|| (x != 0 && map[x - 1][y] == '\n')
				|| (y != 0 && !map[x][y - 1])
				|| (y != 0 && map[x][y - 1] == '\n'));
}

int	check_textures(char *str)
{
	if (access(str, F_OK | O_RDONLY) == -1)
		return (1);
	return (0);
}

int	check_color(char *str)
{
	char	*temp;
	int		x;
	int		start;

	x = 0;
	start = 0;
	while (str[x])
	{
		if (str[x] >= '0' && str[x] <= '9')
		{
			start = x;
			while (str[x] >= '0' && str[x] <= '9')
				x++;
			temp = ft_substr(str, start, x - start);
			if (ft_atoi(temp) < 0 || ft_atoi(temp) > 250)
				return (1);
			free(temp);
		}
		else
			x++;
	}
	return (0);
}
