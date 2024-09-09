/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:48:42 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/03 17:39:47 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	ft_abs(double nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}

int	get_pixel(t_img *data, int x, int y)
{
	char	*dst;
	int		color;

	dst = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*void	draw_buffer(t_trace_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(data->mlx_data->img, x, y, data->buffer[y][x]);
			y++;
		}
		x++;
	}
}*/

void	draw_buffer(t_trace_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			// Placement du pixel dans l'image selon les dimensions
			my_mlx_pixel_put(data->mlx_data->img, x, y, data->buffer[y][x]);
			y++;
		}
		x++;
	}
}
