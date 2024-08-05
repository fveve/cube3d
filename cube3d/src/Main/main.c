/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:53:40 by arafa             #+#    #+#             */
/*   Updated: 2024/08/05 14:14:26 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <sys/time.h> // need to be removed

double ft_abs(double nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}

int	get_pixel(t_img *data, int x, int y)
{
	int color;

	color = data->addr[x * y];
	return (color);
}

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int len;

	len = SCREEN_WIDTH; /* En réalité, il s'agit de la longueur de votre image. Ici, mon image et ma fenêtre font la même taille */
	/* in this part you'll see how i decompose a decimal color in a third part decimal color rgb(255, 255, 255) */
	/* Dans cette partie, voici comment je decompose une couleur decimal en une couleur décimale en trois partie rgb(255, 255, 255) */
	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	/* (x * 4) + (len * 4 * y) : cible le premier bit d'un pixel */
	data->img->addr[(x * 4) + (len * 4 * y)] = b;
	data->img->addr[(x * 4) + (len * 4 * y) + 1] = g;
	data->img->addr[(x * 4) + (len * 4 * y) + 2] = r;
	data->img->addr[(x * 4) + (len * 4 * y) + 3] = 0;
}

void	verline(t_trace_data *data, int x, unsigned int buffer[SCREEN_HEIGHT][SCREEN_WIDTH])
{
	for (int z = 0; z < data->drawStart; z++)
	{
        my_mlx_pixel_put(data->mlx_data, x, z, data->map_data->F_color);
	}
	
    for (int y = data->drawStart; y <= data->drawEnd; y++) {
        	my_mlx_pixel_put(data->mlx_data, x, y,  buffer[y][x]);
    }
	
	for (int z = data->drawEnd;  z < data->w; z++)
	{
        my_mlx_pixel_put(data->mlx_data, x, z, data->map_data->C_color);	
	}
}

int input(int key, t_data *data)
{
	printf("1\n");
	printf("key : %d\n", key);
	mlx_do_key_autorepeaton(data->mlx_data->mlx);
	if (key == KEY_UP || key == KEY_W)
    {
      if(data->map_data->map[(int)(data->map_data->pos_x + data->trace_data->dirX * data->trace_data->moveSpeed)][(int)data->map_data->pos_y] != '1') 
	  	data->map_data->pos_x += data->trace_data->dirX * data->trace_data->moveSpeed;
      if(data->map_data->map[(int)data->map_data->pos_x][(int)(data->map_data->pos_y + data->trace_data->dirY * data->trace_data->moveSpeed)] != '1')
	  	data->map_data->pos_y += data->trace_data->dirY *data->trace_data->moveSpeed;
    }
    if (key == KEY_DOWN ||  key == KEY_S)
    {
		if(data->map_data->map[(int)(data->map_data->pos_x - data->trace_data->dirX * data->trace_data->moveSpeed)][(int)data->map_data->pos_y] != '1')
			data->map_data->pos_x -= data->trace_data->dirX * data->trace_data->moveSpeed;
    	if(data->map_data->map[(int)data->map_data->pos_x][(int)(data->map_data->pos_y - data->trace_data->dirY * data->trace_data->moveSpeed)] != '1')
			data->map_data->pos_y -= data->trace_data->dirY * data->trace_data->moveSpeed;
    }
	if (key == KEY_A)
    {
			if(data->map_data->map[(int)(data->map_data->pos_x - data->trace_data->dirY * data->trace_data->moveSpeed)][(int)data->map_data->pos_y] != '1') 
	  			data->map_data->pos_x -= data->trace_data->dirY * data->trace_data->moveSpeed;
    		if(data->map_data->map[(int)data->map_data->pos_x][(int)(data->map_data->pos_y + data->trace_data->dirX *data->trace_data->moveSpeed)] != '1')
	  			data->map_data->pos_y += data->trace_data->dirX *data->trace_data->moveSpeed;	
    }
	if (key == KEY_D)
    {
			if(data->map_data->map[(int)(data->map_data->pos_x + data->trace_data->dirY * data->trace_data->moveSpeed)][(int)data->map_data->pos_y] != '1') 
				data->map_data->pos_x += data->trace_data->dirY * data->trace_data->moveSpeed;
			if(data->map_data->map[(int)data->map_data->pos_x][(int)(data->map_data->pos_y - data->trace_data->dirX *data->trace_data->moveSpeed)] != '1')
				data->map_data->pos_y -= data->trace_data->dirX *data->trace_data->moveSpeed;
    }
    if (key == KEY_RIGHT)
    {
      //both camera direction and camera plane must be rotated
		data->trace_data->oldDirX = data->trace_data->dirX;
		data->trace_data->dirX = data->trace_data->dirX * cos(-data->trace_data->rotSpeed) - data->trace_data->dirY * sin(-data->trace_data->rotSpeed);
		data->trace_data->dirY = data->trace_data->oldDirX * sin(-data->trace_data->rotSpeed) + data->trace_data->dirY * cos(-data->trace_data->rotSpeed);
		data->trace_data->oldPlaneX = data->trace_data->planeX;
		data->trace_data->planeX = data->trace_data->planeX * cos(-data->trace_data->rotSpeed) - data->trace_data->planeY * sin(-data->trace_data->rotSpeed);
    	data->trace_data->planeY = data->trace_data->oldPlaneX * sin(-data->trace_data->rotSpeed) + data->trace_data->planeY * cos(-data->trace_data->rotSpeed);
    }
    //rotate to the left
    if (key == KEY_LEFT)
    {
		//both camera direction and camera plane must be rotated
		data->trace_data->oldDirX = data->trace_data->dirX;
		data->trace_data->dirX = data->trace_data->dirX * cos(data->trace_data->rotSpeed) - data->trace_data->dirY * sin(data->trace_data->rotSpeed);
		data->trace_data->dirY = data->trace_data->oldDirX * sin(data->trace_data->rotSpeed) + data->trace_data->dirY * cos(data->trace_data->rotSpeed);
		data->trace_data->oldPlaneX = data->trace_data->planeX;
		data->trace_data->planeX = data->trace_data->planeX * cos(data->trace_data->rotSpeed) - data->trace_data->planeY * sin(data->trace_data->rotSpeed);
		data->trace_data->planeY = data->trace_data->oldPlaneX * sin(data->trace_data->rotSpeed) + data->trace_data->planeY * cos(data->trace_data->rotSpeed);
	}
	if (key == KEY_ESCAPE)
		exit_manager(data);
	return (0);
}

int	ft_render(t_data *data)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		data->trace_data->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		data->trace_data->rayDirX = data->trace_data->dirX + data->trace_data->planeX * data->trace_data->cameraX;
		data->trace_data->rayDirY = data->trace_data->dirY + data->trace_data->planeY * data->trace_data->cameraX;
		data->trace_data->mapX = (int)data->map_data->pos_x;
		data->trace_data->mapY = (int)data->map_data->pos_y;
		data->trace_data->deltaDistX = (data->trace_data->rayDirX == 0) ? 1e30 : ft_abs(1 / data->trace_data->rayDirX);
		data->trace_data->deltaDistY = (data->trace_data->rayDirY == 0) ? 1e30 : ft_abs(1 / data->trace_data->rayDirY);
		data->trace_data->hit = 0;
		if (data->trace_data->rayDirX < 0)
    	{
    		data->trace_data->stepX = -1;
        	data->trace_data->sideDistX = (data->map_data->pos_x - data->trace_data->mapX) * data->trace_data->deltaDistX;
    	}
    	else
    	{
    		data->trace_data->stepX = 1;
    		data->trace_data->sideDistX = (data->trace_data->mapX + 1.0 - data->map_data->pos_x) * data->trace_data->deltaDistX;
    	}
    	if (data->trace_data->rayDirY < 0)
    	{
    		data->trace_data->stepY = -1;
    		data->trace_data->sideDistY = (data->map_data->pos_y - data->trace_data->mapY) * data->trace_data->deltaDistY;
    	}
    	else
    	{
    		data->trace_data->stepY = 1;
        	data->trace_data->sideDistY = (data->trace_data->mapY + 1.0 - data->map_data->pos_y) * data->trace_data->deltaDistY;
		}
		while (data->trace_data->hit == 0)
    	{
			//jump to next map square, either in x-direction, or in y-direction
			if (data->trace_data->sideDistX < data->trace_data->sideDistY)
			{
				data->trace_data->sideDistX += data->trace_data->deltaDistX;
				data->trace_data->mapX += data->trace_data->stepX;
				data->trace_data->side = 0;
			}
			else
			{
				data->trace_data->sideDistY += data->trace_data->deltaDistY;
				data->trace_data->mapY += data->trace_data->stepY;
				data->trace_data->side = 1;
			}
			//Check if ray has hit a wall
			//print_tab(data->map_data->map);
		//	printf("data->mapX : %d,  data->mapY : %d\n", data->mapX,data->mapY);
			if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY] == '1') 
			{
				//print_map_data(data->map_data);
				data->trace_data->hit = 1;
			}
     	}
		if(data->trace_data->side == 0) 
			data->trace_data->perpWallDist = (data->trace_data->sideDistX - data->trace_data->deltaDistX);
		else
			data->trace_data->perpWallDist = (data->trace_data->sideDistY - data->trace_data->deltaDistY);
		data->trace_data->lineHeight = (int)(SCREEN_HEIGHT  / data->trace_data->perpWallDist);
		data->trace_data->drawStart = (data->trace_data->lineHeight * -1) / 2 + SCREEN_HEIGHT / 2;
		if (data->trace_data->drawStart < 0)
			data->trace_data->drawStart = 0;
		data->trace_data->drawEnd = data->trace_data->lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (data->trace_data->drawEnd >= SCREEN_HEIGHT)
			data->trace_data->drawEnd = SCREEN_HEIGHT - 1;
		data->trace_data->texNum = data->map_data->map[data->trace_data->mapX][data->trace_data->mapY] - 49; //1 subtracted from it so that texture 0 can be used!
      //calculate value of wallX
       //where exactly the wall was hit
		if (data->trace_data->side == 0)
			data->trace_data->WallX = data->map_data->pos_y + data->trace_data->perpWallDist * data->trace_data->rayDirY;
		else
			data->trace_data->WallX = data->map_data->pos_x + data->trace_data->perpWallDist * data->trace_data->rayDirX;
		data->trace_data->WallX -= floor((data->trace_data->WallX));

		//x coordinate on the texture
		data->trace_data->texX = (int)(data->trace_data->WallX * (double)TEX_WIDTH);
		if(data->trace_data->side == 0 && data->trace_data->rayDirX > 0) 
			data->trace_data->texX = TEX_WIDTH - data->trace_data->texX - 1;
		if(data->trace_data->side == 1 && data->trace_data->rayDirY < 0)
			data->trace_data->texX = TEX_HEIGHT - data->trace_data->texX - 1;
		data->trace_data->step = 1.0 * TEX_HEIGHT / data->trace_data->lineHeight;
		// Starting texture coordinate
		data->trace_data->texPos = (data->trace_data->drawStart - data->trace_data->h / 2 + data->trace_data->lineHeight / 2) * data->trace_data->step;
		for(int y = data->trace_data->drawStart; y < data->trace_data->drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			data->trace_data->texY = (int)data->trace_data->texPos & (TEX_HEIGHT - 1);
			data->trace_data->texPos += data->trace_data->step;
			data->trace_data->color = get_pixel(data->mlx_data->texture, x, y);
			//printf("data->trace_data->texNum %d, TEX_HEIGHT * data->trace_data->texY + data->trace_data->texX : %d\n",data->trace_data->texNum,  TEX_HEIGHT * data->trace_data->texY + data->trace_data->texX);
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(data->trace_data->side == 1)
				data->trace_data->color = (data->trace_data->color >> 1) & 8355711;
			data->trace_data->buffer[y][x] = data->trace_data->color;
		}
		verline(data->trace_data,x,data->trace_data->buffer);
		for(int y = 0; y < data->trace_data->h; y++)
		{
			for(int x = 0; x < data->trace_data->w; x++)
			{
				data->trace_data->buffer[y][x] = 0;
			}
		}
	}
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->mlx_data->img->img, 0, 0);
	return (0);
}

int	main (int argc, char **argv)
{
	t_data data;

	if (argc != 2)
	{
		printf("Error\nWrong number of argument\n");
		exit (0);
	}
	init_data(&data, argv);
	mlx_loop_hook(data.mlx_data->mlx, ft_render, &data);
	mlx_hook(data.mlx_data->window, 2, 1L<<0, &input, &data); /* ADDED */
	mlx_key_hook(data.mlx_data->window, input, &data);
	mlx_loop(data.mlx_data->mlx);
	exit_manager(&data);
}