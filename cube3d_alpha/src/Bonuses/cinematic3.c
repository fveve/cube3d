/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematic3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:57:43 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 15:44:01 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	load_image1(t_data *data)
{
	data->bonus_data->cinematic[0] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/title_screen.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[1] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/title_text.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[2] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/title_commands.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[3] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/victory.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[4] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/game_over.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[5] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading1.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[6] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading2.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[7] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading3.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
}

void	load_image2(t_data *data)
{
	data->bonus_data->cinematic[8] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading4.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[9] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading5.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[10] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading6.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[11] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading7.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[12] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading8.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[13] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading9.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
}

char	*finish_the_path(t_data *data, char *folder_path,
	char *file_name, char *file_path)
{
	char	*tmp_path;

	file_path = ft_strjoin(folder_path, "/");
	if (!file_path)
	{
		free(file_name);
		exit_manager(data);
	}
	tmp_path = file_path;
	file_path = ft_strjoin(file_path, file_name);
	free(tmp_path);
	free(file_name);
	tmp_path = file_path;
	file_path = ft_strjoin(file_path, ").jpg.xpm");
	free(tmp_path);
	if (!file_path)
		exit_manager(data);
	return (file_path);
}

char	*create_the_path(t_data *data, int i, char *file_name)
{
	char	*index_str;

	index_str = NULL;
	index_str = ft_itoa(i + 1 - 14);
	if (!index_str)
	{
		free_cinematic_images(data, i);
		exit_manager(data);
	}
	if (i + 1 - 14 < 10)
		file_name = ft_strjoin("vortex_cinematic(00", index_str);
	else if (i + 1 - 14 < 100)
		file_name = ft_strjoin("vortex_cinematic(0", index_str);
	else
		file_name = ft_strjoin("vortex_cinematic(", index_str);
	free(index_str);
	if (!file_name)
		exit_manager(data);
	return (file_name);
}

int	load_part1(t_data *data, char **file_name, char **file_path, int num_images)
{
	int	i;

	data->mlx_data->window = resize_window(data, 1920, 1080);
	file_name = NULL;
	file_path = NULL;
	i = 0;
	data->bonus_data->cinematic = malloc(sizeof(void *) * (num_images));
	if (!data->bonus_data->cinematic)
		exit_manager(data);
	while (i < num_images)
	{
		data->bonus_data->cinematic[i] = NULL;
		i++;
	}
	i = 0;
	load_image1(data);
	load_image2(data);
	return (i);
}
