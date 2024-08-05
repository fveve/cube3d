/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:06:00 by arafa             #+#    #+#             */
/*   Updated: 2024/08/03 09:25:26 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_strlen2(char **tab)
{
	int x;

	x = 0;
	while (tab[x])
		x++;
	return (x);
}

char **tab_dup(char **tab)
{
	char **temp;
	int x;
	
	x = 0;
	temp = malloc(sizeof(char *) * (ft_strlen2(tab) + 1));
	while (tab[x])
	{
		temp[x] = ft_strdup(tab[x]);
		x++;
	}
	temp[x] = NULL;
	return (temp);
}

int	is_position(char c)
{
	return ((c == 'W' || c == 'N' || c == 'S' || c == 'E'));
}

int	check_boder(char **map, int x, int y)
{
	return(!map[x][y + 1] || map[x][y + 1] == '\n' || !map[x + 1][y] || map[x + 1][y] == '\n' || (x != 0 && !map[x - 1][y]) || (x != 0 && map[x - 1][y] == '\n') || (y != 0 && !map[x][y - 1]) || (y != 0 && map[x][y - 1] == '\n'));
}

int	check_textures(char *str)
{
	if (access(str, O_RDONLY) == -1)
	{
		free(str);
		return (1);
	}
	free(str);
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
			y++;
		}
		x++;
	}
	if (count != 1)
		return (1);
	return (0);
}

int	check_map(char **temp, int start, int x, int y)
{
	//printf("x : %d | y : %d \n", x, y);
	//print_tab(temp);
	if ((temp[x][y] == '0' ||  is_position(temp[x][y])) && check_boder(temp, x,y))
		return (1);
	else if (temp[x][y] == '0' || is_position(temp[x][y]))
		temp[x][y] = '2';
	if (y >= ft_strlen(temp[x]) - 1)
		y = 0;
	if (x != start && temp[x - 1][y] != '1' && temp[x - 1][y] != '2')
		if (check_map(temp, start,  x - 1, y))
			return (1);
	if (y != 0 &&  temp[x][y - 1] != '1' && temp[x][y - 1] != '2')
		if (check_map(temp, start,  x, y - 1))
			return (1);
	if (temp[x][y + 1] && temp[x][y + 1] != '1' && temp[x][y + 1] != '2')
		if (check_map(temp, start,  x, y + 1))
			return (1);
	if (temp[x + 1][y] && temp[x + 1][y] != '1' && temp[x + 1][y] != '2')
		if (check_map(temp, start,  x + 1, y))
			return (1);
	return (0);
}

int	check_error(t_map_data map_data)
{
	char **temp;
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	/*if (check_textures(map_data.WE) || check_textures(map_data.SO)
			|| check_textures(map_data.NO) || check_textures(map_data.EA))
	{
		printf("Error\nTexture problem\n");
		exit_manager(map_data);
	}*/
	//printf("x : %d\n\n",x);
	temp = tab_dup((map_data.map));
	if (check_position(temp))
	{
		free_tab(temp);
		printf("Error\nPosition problem\n");
	}
	if (check_map(temp,x ,  map_data.pos_x, map_data.pos_y))
	{
		free_tab(temp);
		printf("Error\nMap must be close\n");
	}
	/*if (check_color(map_data.C) || check_color(map_data.F))
	{
		free_tab(temp);
		printf("Error\nWrong color number\n");
	}*/
	else
		free_tab(temp);
	return (0);
}