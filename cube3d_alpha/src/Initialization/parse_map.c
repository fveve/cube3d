/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:52:22 by arafa             #+#    #+#             */
/*   Updated: 2024/09/12 16:36:27 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	**remove_space(char **map);

int		file_len(char *file);

int		is_printable(char *s);

int		init_textures(t_data *data, int fd, int trigger, int x);

void	set_color2(int *F_color, int r, int g, int b)
{
	*F_color = r;
	*F_color = (*F_color << 8) | g;
	*F_color = (*F_color << 8) | b;
}

void	set_color(char *F, int *F_color, int trigger)
{
	int	r;
	int	g;
	int	b;
	int	x;

	x = 0;
	r = 0;
	g = 0;
	b = 0;
	while (F[x] && x++ >= 0)
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
	}
	set_color2(F_color, r, g, b);
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
			if (is_position(map_data->map[y][x]))
			{
				map_data->pos_y = (double)x;
				map_data->pos_x = (double)y;
				break ;
			}
			x++;
		}
		y++;
	}
}

void	set_map_informations(t_map_data *map_data)
{
	char	**tab;
	int		x;
	int		y;

	tab = map_data->map;
	y = 0;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x])
		{
			if (tab[y][x] == 'Z')
				map_data->num_ennemies++;
			else if (tab[y][x] == 'C')
				map_data->num_collectibles++;
			else if (tab[y][x] == 'D')
				map_data->num_doors++;
			x++;
		}
		y++;
	}
}

void	parse_map(t_data *data, t_map_data *map_data, char *file)
{
	int	fd;
	int	x;
	int	len;

	x = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFile problem\n");
		exit (0);
	}
	len = (file_len(file)
			- init_textures(data, fd, 0, 0)) + 1;
	map_data->map = malloc(sizeof(char *) * len);
	map_data->map[x] = get_next_line(fd);
	while (map_data->map[x] && x++ < len)
		map_data->map[x] = get_next_line(fd);
	map_data->map[x] = NULL;
	map_data->map = remove_space(map_data->map);
	if (ft_strlen2(map_data->map) < 3)
		exit_error_message(data, "Error\nMap Error\n");
	set_color(map_data->f, &map_data->f_color, 0);
	set_color(map_data->c, &map_data->c_color, 0);
	set_pos(map_data);
	set_map_informations(map_data);
}
