/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:53:40 by arafa             #+#    #+#             */
/*   Updated: 2024/08/14 14:39:48 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"



int	main (int argc, char **argv)
{
	t_data data;

	if (argc != 2)
	{
		printf("Error\nWrong number of argument\n");
		exit (0);
	}
	init_data(&data, argv);
	mlx_loop_hook(data.mlx_data->mlx, ft_render, &data);//loop hook : render each frame
	mlx_hook(data.mlx_data->window, 2, 1L<<0, &input, &data);//handle input
	mlx_hook(data.mlx_data->window, 17, 1L<<0, exit_manager, &data);//handle closing the window
	mlx_loop(data.mlx_data->mlx);
	exit_manager(&data);
}