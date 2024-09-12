/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:06:00 by arafa             #+#    #+#             */
/*   Updated: 2024/09/12 11:35:11 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_position(char **map)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	count = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (is_position(map[x][y]))
				count++;
			if (map[x][y] != '\r' && map[x][y] != 32 && map[x][y] != '\n'
				&& map[x][y] != '0' && map[x][y] != '1' && map[x][y] != 'D'
				&& map[x][y] != 'Z' && map[x][y] != 'C'
				&& !is_position(map[x][y]))
				return (1);
			y++;
		}
		x++;
	}
	if (count != 1)
		return (1);
	return (0);
}

int	check_map2(char **temp, int start, int x, int y)
{
	if (x == 0 && temp[x][y] != '1')
		return (1);
	if (y != 0 && temp[x][y - 1] != '1' && temp[x][y - 1] != '2'
		&& temp[x][y - 1] != 'Z' && temp[x][y - 1] != 'C'
		&& temp[x][y - 1] != 'D')
		if (check_map(temp, start, x, y - 1))
			return (1);
	if (temp[x][y + 1] && temp[x][y + 1] != '1'
		&& temp[x][y + 1] != '2'
		&& temp[x][y + 1] != 'Z' && temp[x][y + 1] != 'C'
		&& temp[x][y + 1] != 'D')
		if (check_map(temp, start, x, y + 1))
			return (1);
	if (temp[x + 1][y] && temp[x + 1][y] != '1'
		&& temp[x + 1][y] != '2' && temp[x + 1][y] != 'Z'
		&& temp[x + 1][y] != 'C' && temp[x + 1][y] != 'D')
		if (check_map(temp, start, x + 1, y))
			return (1);
	return (0);
}

int	check_map(char **temp, int start, int x, int y)
{
	if ((x != 0 && y > ft_strlen(temp[x - 1]) && temp[x][y] != '1')
		|| (temp[x + 1][y] == ' ' && temp[x][y] != '1'))
		return (1);
	if ((temp[x][y] == '0' || is_position(temp[x][y]))
		&& check_boder(temp, x, y))
		return (1);
	else if (temp[x][y] == '0' || is_position(temp[x][y]))
		temp[x][y] = '2';
	if (y >= ft_strlen(temp[x]) - 1)
		y = 0;
	if (x != start && temp[x - 1][y] != '1' && temp[x - 1][y] != '2'
			&& temp[x - 1][y] != 'Z' && temp[x - 1][y] != 'C'
			&& temp[x - 1][y] != 'D')
		if (check_map(temp, start, x - 1, y))
			return (1);
	if (check_map2(temp, start, x, y))
		return (1);
	return (0);
}

void	check_error2(t_data *data, t_map_data map_data, char **temp, int x)
{
	if (check_map(temp, x, map_data.pos_x, map_data.pos_y))
	{
		free_tab(temp);
		printf("Error\nMap must be close\n");
		exit_error_text(data);
	}
	if (check_color(map_data.c) || check_color(map_data.f))
	{
		free_tab(temp);
		printf("Error\nWrong color number\n");
		exit_error_text(data);
	}
}

int	check_error(t_data *data, t_map_data map_data)
{
	char	**temp;
	int		x;

	x = 0;
	if (check_textures(map_data.texture_txt[0])
		|| check_textures(map_data.texture_txt[1])
		|| check_textures(map_data.texture_txt[2])
		|| check_textures(map_data.texture_txt[3]))
	{
		printf("Error\nWall Texture problem\n");
		exit_error_text(data);
	}
	temp = tab_dup((map_data.map));
	if (check_position(temp))
	{
		free_tab(temp);
		printf("Error\nPosition problem\n");
		exit_error_text(data);
	}
	check_error2(data, map_data, temp, x);
	free_tab(temp);
	return (0);
}
