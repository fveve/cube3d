#include "cube3d.h"

double ft_abs(double nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}

int	get_pixel(t_img *data, int x, int y)
{
	char *dst;
	int	color;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel /8) ) ;
	color = *(unsigned int *)dst;
	return (color);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;

}

void	draw_buffer(t_trace_data *data)
{
	for (int x = 0; x < SCREEN_HEIGHT; x++)
	{
		for (int y = 0; y < SCREEN_WIDTH; y++)
		{
			my_mlx_pixel_put(data->mlx_data->img, x, y, data->buffer[y][x]);
		}
	}	
}