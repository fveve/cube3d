/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:52:22 by arafa             #+#    #+#             */
/*   Updated: 2024/09/09 14:28:23 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
		if (F[x])
			x++;
	}
	*F_color = r;
	*F_color = (*F_color << 8) | g;
	*F_color = (*F_color << 8) | b;
}

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

char	**remove_space(char **map)
{
	char	**temp;
	int		y;
	int		map_start;
	int		map_end;

	map_start = 0;
	while (map[map_start] && is_removable(map[map_start]))
		map_start++;
	if (!map[map_start])
		return (map);
	map_end = ft_strlen2(map) - 1;
	while (map_end > map_start && is_removable(map[map_end]))
		map_end--;
	temp = malloc(sizeof(char *) * (map_end - map_start + 2));
	y = 0;
	while (map_start <= map_end)
	{
		temp[y] = ft_strdup(map[map_start]);
		map_start++;
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
	char	*tab;
	int		fd;
	int		x;

	x = 0;
	fd = open(file, O_RDONLY);
	tab = get_next_line(fd/*, 0*/);// Appel initial à get_next_line
	while (tab) // Condition de boucle vérifiant si tab n'est pas NULL
	{
		free(tab);
		x++;
		tab = get_next_line(fd/*, 0*/);// Appel à get_next_line à l'intérieur de la boucle
	}
	close(fd);
	return (x);
}

int	init_textures(t_map_data *map_data, int fd, int trigger, int x)
{
	char	*tab;

	tab = get_next_line(fd/*, 0*/);
	while (tab && trigger < 6)
	{
		if (!ft_strncmp("NO", tab, 2) && trigger < 6)
			map_data->texture_txt[0] = extract_str(tab);
		else if (!ft_strncmp("SO", tab, 2) && trigger < 6)
			map_data->texture_txt[1] = extract_str(tab);
		else if (!ft_strncmp("WE", tab, 2) && trigger < 6)
			map_data->texture_txt[2] = extract_str(tab);
		else if (!ft_strncmp("EA", tab, 2) && trigger < 6)
			map_data->texture_txt[3] = extract_str(tab);
		else if (!ft_strncmp("F", tab, 1) && trigger < 6)
			map_data->f = ft_strdup(tab);
		else if (!ft_strncmp("C", tab, 1) && trigger < 6)
			map_data->c = ft_strdup(tab);
		else
			trigger--;
		trigger++;
		if (trigger < 6)
		{
			x++;
			free(tab);
			tab = get_next_line(fd/*, 0*/);
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

void	set_map_informations(t_data *data)
{
	char	**tab;
	int		x;
	int		y;

	tab = data->map_data->map;
	y = 0;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x])
		{
			if (tab[y][x] == 'Z')
				data->map_data->num_ennemies++;
			else if (tab[y][x] == 'C')
				data->map_data->num_collectibles++;
			else if (tab[y][x] == 'D')
				data->map_data->num_doors++;
			/*else if (tab[y][x] != '1' && tab[y][x] != '0' && tab[y][x] != 'N' 
				&& tab[y][x] != 'S' && tab[y][x] != 'E' && tab[y][x] != 'W' 
				&& tab[y][x] != ' ' && tab[y][x] != '\n')
			{	
				printf("tab[y][x] ==> >>%c<< \n", tab[y][x]);
				exit_error_message(data, "Unknown Character in Your Map File");
				}*/
		// if you want to add something different on the map.
			x++;
		}
		y++;
	}
}

void	parse_map(t_data *data, char *file)
{
	int	fd;
	int	x;

	x = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFile problem\n");
		exit (0);
	}
	data->map_data->map = malloc(sizeof(char *) * (file_len(file)
				- init_textures(data->map_data, fd, 0, 0) + 1));
	data->map_data->map[x] = get_next_line(fd/*, 0*/);
	while (data->map_data->map[x] && ++x)
		data->map_data->map[x] = get_next_line(fd/*, 0*/);
	data->map_data->map[x] = NULL;
	data->map_data->map = remove_space(data->map_data->map);
	set_color(data->map_data->f, &data->map_data->f_color, 0); // Couleur du sol
	set_color(data->map_data->c, &data->map_data->c_color, 0); // Couleur du plafond
	set_pos(data->map_data);
	set_map_informations(data);
}
