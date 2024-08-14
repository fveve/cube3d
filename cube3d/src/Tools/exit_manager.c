#include "cube3d.h"

void	free_tab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	if (tab)
		free(tab);
}

void	free_img_data(void *mlx, t_img *data)
{
	mlx_destroy_image(mlx,data->img);
	free(data);
}

void	free_mlx_data(t_mlx_data *data)
{
	free_img_data(data->mlx, data->img);
	for(int x = 0; x < 4; x++)
		free_img_data(data->mlx, data->texture[x]);
    mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
}

void	free_map_data(t_map_data *map_data)
{
	if (map_data->map)
		free_tab(map_data->map);
	if (map_data->C)
		free(map_data->C);
	if (map_data->F)
		free(map_data->F);
	free(map_data);
}

int	exit_manager(t_data *data)
{
	free_map_data(data->map_data);
	free_mlx_data(data->mlx_data);
	free(data->trace_data);
	exit(0);
	return (0);
}
