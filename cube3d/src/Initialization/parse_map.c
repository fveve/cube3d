/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:52:22 by arafa             #+#    #+#             */
/*   Updated: 2024/08/03 09:59:15 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_color(char *F, int *F_color, int trigger)
{
	int r;
	int g;
	int b;
	int	x;

	x = 0;
	r = 0;
	g = 0;
	b = 0;
	*F_color = 0;
	while (F[x])
	{
		if (F[x] && F[x] >= '0' && F[x] <= '9')
		{
			if (!trigger)
				r = (int)ft_atoi(&F[x]);
			else if (trigger == 1)
				g = (int)ft_atoi(&F[x]);
			else if (trigger == 2)
				b = (int)ft_atoi(&F[x]);
			trigger++;
			while (F[x] && F[x] != ',')
				x++;
		}
		x++;
	}
	printf("r : %d, g : %d, b : %d\n", r, g, b);
	*F_color = r;
	*F_color = (*F_color << 8) | g;
	*F_color = (*F_color << 8) | b;
	printf("map_data->F_color : %d\n", *F_color);
}

int is_removable(char *s)
{
	int x;
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

char **remove_space(char **map)//
{
	char **temp;
	int x;
	int	y;
	
	x = 0;
	y = 0;
	while (map[x] && is_removable(map[x]))
		x++;
	if (x == 0)
		return (map);
	temp = malloc(sizeof(char *) * ((ft_strlen2(map) - x)+1));
	while (x < ft_strlen2(map))
	{
		temp[y] = ft_strdup(map[x]);
		x++;
		y++;
	}
	temp[y] = NULL;
	free_tab(map);
	return (temp);
}

int	is_printable(char *s)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (!(s[x] >= 48 && s[x] <= 57)
			&& !(s[x] >= 65 && s[x] <= 90)
			&& !(s[x] >= 97 && s[x] <= 122))
			return (0);
		x++;
	}
	return (1);
}

int	file_len(char *file)
{
	char *tab;
	int		fd;
	int		x;

	x = 0;
	fd = open(file, O_RDONLY);
	while ((tab = get_next_line(fd, 0)))
	{
		free(tab);
		x++;
	}
	close(fd);
	return (x);
}

int	init_textures(t_map_data *map_data, int fd, int trigger, int x)
{
	char	*tab;

	tab = get_next_line(fd, 0);
	while (tab && trigger < 6)
	{
		if (!ft_strncmp("NO", tab, 2) && trigger < 6)
			map_data->NO = extract_str(tab);
		else if (!ft_strncmp("SO", tab, 2) && trigger < 6)
			map_data->SO = extract_str(tab);
		else if (!ft_strncmp("EA", tab, 2) && trigger <=6)
			map_data->EA = extract_str(tab);
		else if (!ft_strncmp("WE", tab, 2) && trigger < 6)
			map_data->WE = extract_str(tab);
		else if (!ft_strncmp("F", tab, 1) && trigger < 6)
			map_data->F = ft_strdup(tab);
		else if (!ft_strncmp("C", tab, 1) && trigger < 6)
			map_data->C = ft_strdup(tab);
		else
			trigger--;
		trigger++;
		if (trigger < 6)
		{
			x++;
			free(tab);
			tab = get_next_line(fd, 0);
		}
	}
	free(tab);
	return (x);
}

void	set_pos(t_map_data *map_data)
{
	int	y;
	int	x;
	
	y = 0;
	map_data->pos_x = 0;
	map_data->pos_y = 0;
	while (map_data->map[y] && !map_data->pos_x)
	{
		x = 0;
		while (map_data->map[y][x])
		{
			//printf("map[x]1 : %s\n", map_data->map[x]);
			if (is_position(map_data->map[y][x]))
			{
				map_data->pos_y = (double)x;
				map_data->pos_x = (double)y;
				//printf("data->mapX : %f,  data->mapY : %f\n", map_data->pos_x,map_data->pos_y);
				break ;
			}
			x++;
		}
		y++;
	}
	//printf("x : %d | y : %d\n", x, y);
}

void	parse_map(t_map_data *map_data, char *file)
{
	int 	fd;
	int		x;
	
	x = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		printf("Error\nFile problem\n");
		exit (0);
	}
	map_data->map = malloc(sizeof(char *) * (file_len(file) - init_textures(map_data, fd, 0 , 0) + 1));
	map_data->map[x] = get_next_line(fd, 0);
	while (map_data->map[x] && ++x)
		map_data->map[x] = get_next_line(fd, 0);
	map_data->map[x] = NULL;
	map_data->map = remove_space(map_data->map);
	set_color(map_data->F, &map_data->F_color, 0);
	set_color(map_data->C, &map_data->C_color, 0);
	print_map_data(map_data);
	//print_tab(map_data->map);
	set_pos(map_data);
	//print_tab(map_data->map);
}