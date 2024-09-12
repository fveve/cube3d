/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:19:22 by arafa             #+#    #+#             */
/*   Updated: 2024/09/12 11:32:28 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_removable(char *s);

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
	tab = get_next_line(fd);
	while (tab)
	{
		free(tab);
		x++;
		tab = get_next_line(fd);
	}
	close(fd);
	return (x);
}

void	init_textures2(t_map_data *map_data, char *tab, int *trigger)
{
	if (!ft_strncmp("WE", tab, 2) && *trigger < 6)
		map_data->texture_txt[2] = extract_str(tab);
	else if (!ft_strncmp("EA", tab, 2) && *trigger < 6)
		map_data->texture_txt[3] = extract_str(tab);
	else if (!ft_strncmp("F", tab, 1) && *trigger < 6)
		map_data->f = ft_strdup(tab);
	else if (!ft_strncmp("C", tab, 1) && *trigger < 6)
		map_data->c = ft_strdup(tab);
	else
		(*trigger)--;
}

int	init_textures(t_data *data, int fd, int trigger, int x)
{
	char	*tab;

	tab = get_next_line(fd);
	while (tab && trigger < 6)
	{
		if (!ft_strncmp("NO", tab, 2) && trigger < 6)
			data->map_data->texture_txt[0] = extract_str(tab);
		else if (!ft_strncmp("SO", tab, 2) && trigger < 6)
			data->map_data->texture_txt[1] = extract_str(tab);
		else
			init_textures2(data->map_data, tab, &trigger);
		trigger++;
		if (trigger < 6)
		{
			x++;
			free(tab);
			tab = get_next_line(fd);
		}
	}
	if (trigger < 6)
		exit_error_message(data, "Error\nTextureProblem\n");
	free(tab);
	return (x);
}
