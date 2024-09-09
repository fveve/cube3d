/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:53:40 by arafa             #+#    #+#             */
/*   Updated: 2024/09/09 14:34:13 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*int	title_sequence(int key, t_data *data)
{
	static int	flag;

	flag = 0;
	if (key == KEY_ESCAPE)
	{
		if (flag == 0)
		{
			mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->titles[1], 0, 0);
			flag = 1;
		}
		else if (flag == 1)
		{
			mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->titles[2], 0, 0);
			flag = 2;
		}
		else if (flag == 2)
		{
			data->mlx_data->window = resize_window(data, data->trace_data->w, data->trace_data->h);
			return (0);
		}
	}
	return (0);
}*/

void	play_title(t_data *data)
{
	data->mlx_data->window = resize_window(data, 1920, 1080);
	//usleep(500 * 1000); // Convertir ms en microsecondes pour usleep
	//mlx_do_sync(data->mlx_data->mlx);
	//data->mlx_data->window = resize_window(data, 1920, 1080);
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic[0], 0, 0);
	usleep(6000 * 1000); // Convertir ms en microsecondes pour usleep
	mlx_do_sync(data->mlx_data->mlx);
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic[1], 0, 0);
	usleep(10000 * 1000); // Convertir ms en microsecondes pour usleep
	mlx_do_sync(data->mlx_data->mlx);
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic[2], 0, 0);
	usleep(5000 * 1000); // Convertir ms en microsecondes pour usleep
	mlx_do_sync(data->mlx_data->mlx);
	//data->mlx_data->window = resize_window(data, SCREEN_WIDTH, SCREEN_HEIGHT);
	//mlx_hook(data->mlx_data->window, 2, 1L << 0, &title_sequence, &data);//handle input
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Error\nWrong number of argument\n");
		exit (0);
	}
	init_data(&data, argv);
	
	playsound("cub3d_intro", 0, 1, 0);
	load_cinematic_images(&data, "./texture/vortex_cinematic", (&data)->bonus_data->num_cinematic1);
	play_title(&data);
	(&data)->mlx_data->window = resize_window(&data, SCREEN_WIDTH, SCREEN_HEIGHT);

	playsound("cub3d_tablet_sound_intro", 0, 0, 0);

	mlx_loop_hook(data.mlx_data->mlx, ft_render, &data);//loop hook : render each frame
	mlx_hook(data.mlx_data->window, 2, 1L << 0, &input, &data);//handle input
	mlx_hook(data.mlx_data->window, 6, 1L<<6, &mouse_move, &data);
	mlx_hook(data.mlx_data->window, 17, 1L << 0, exit_manager, &data);//handle closing the window
	mlx_loop(data.mlx_data->mlx);
	exit_manager(&data);
}
