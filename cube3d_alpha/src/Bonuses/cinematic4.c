/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematic4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:57:43 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 16:02:35 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_part2(t_data *data, int i)
{
	while (i < 14)
	{
		if (!data->bonus_data->cinematic[i])
		{
			printf("Error loading texture at index %d\n", i);
			exit_manager(data);
		}
		i++;
	}
	return (i);
}

void	load_cinematic_images(t_data *data, char *folder_path, int num_images)
{
	char	*file_name;
	char	*file_path;
	int		i;

	i = load_part1(data, &file_name, &file_path, num_images);
	i = load_part2(data, i);
	while (i < num_images)
	{
		file_name = create_the_path(data, i, file_name);
		file_path = finish_the_path(data, folder_path, file_name, file_path);
		data->bonus_data->cinematic[i] = mlx_xpm_file_to_image(
				data->mlx_data->mlx, file_path,
				&(data->bonus_data->cinematic_w),
				&(data->bonus_data->cinematic_h));
		if (!data->bonus_data->cinematic[i])
		{
			printf("Erreur lors du chargement de l'image : %s\n", file_path);
			free(file_path);
			exit_manager(data);
		}
		free(file_path);
		play_loading_bar(data, i);
		i++;
	}
}

long	get_elapsed_time_ms(struct timeval start_time)
{
	struct timeval	current_time;
	long			elapsed_time_ms;

	gettimeofday(&current_time, NULL);
	elapsed_time_ms = (current_time.tv_sec * 1000 + current_time.tv_usec
			/ 1000) - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	return (elapsed_time_ms);
}

void	play_cinematic(t_data *data, int num_images, int delay_ms)
{
	int				i;
	struct timeval	start_time;
	long			elapsed_time;

	i = 14;
	while (i < num_images)
	{
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[i], 0, 0);
		usleep(delay_ms * 1000);
		mlx_do_sync(data->mlx_data->mlx);
		i++;
	}
	gettimeofday(&start_time, NULL);
	while (1)
	{
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[3], 0, 0);
		elapsed_time = get_elapsed_time_ms(start_time);
		if (elapsed_time >= 8000)
			break ;
	}
}

void	cinematic(t_data *data, int num_images, int delay_ms)
{
	if (data->bonus_data->cinematic != NULL)
	{
		data->mlx_data->window = resize_window(data, 1920, 1080);
		playsound("cub3d_victory_sound", 0, 1, 0);
		play_cinematic(data, num_images, delay_ms);
		free_cinematic_images(data, num_images);
	}
}
