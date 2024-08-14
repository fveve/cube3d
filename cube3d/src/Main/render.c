#include "cube3d.h"

int	ft_render(t_data *data)
{
	int *texture[8];
	
	for (int z = 0; z < 4; z++)
	{
		texture[z] = malloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH);
		for(int x = 0; x < TEX_WIDTH; x++)
		{
			for(int y = 0; y < TEX_HEIGHT; y++)
			{
				texture[z][TEX_HEIGHT * y + x] = get_pixel(data->mlx_data->texture[z], x, y);
			}
		}
	}
	int count = 0;
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		if (count == SCREEN_HEIGHT)
			count = 0;
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
			if (data->map_data->map[data->trace_data->mapX][data->trace_data->mapY] == '1') 
			{
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
		for(int z = 0; z < data->trace_data->drawStart - 1; z++)
		{
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"                                     
			data->trace_data->buffer[z][x] = data->map_data->F_color;
		}
		for(int y = data->trace_data->drawStart; y < data->trace_data->drawEnd; y++)
    	{

			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			data->trace_data->texY = (int)data->trace_data->texPos & (TEX_HEIGHT - 1);
			data->trace_data->texPos += data->trace_data->step;
				if (data->trace_data->side == 0 && data->trace_data->stepX == 1)
					data->trace_data->color = texture[0][TEX_HEIGHT * data->trace_data->texY + data->trace_data->texX];
				else if (data->trace_data->side == 0)
					data->trace_data->color = texture[1][TEX_HEIGHT * data->trace_data->texY + data->trace_data->texX];
				else if (data->trace_data->stepY == 1)
					data->trace_data->color = texture[3][TEX_HEIGHT * data->trace_data->texY + data->trace_data->texX];
				else if (data->trace_data->side == 1)
					data->trace_data->color = texture[2][TEX_HEIGHT * data->trace_data->texY + data->trace_data->texX];
					
			
			 if(data->trace_data->side == 1) 
			 	data->trace_data->color = (data->trace_data->color >> 1) & 8355711;
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			data->trace_data->buffer[y][x] = data->trace_data->color;
		}
				for(int z = data->trace_data->drawEnd; z < SCREEN_HEIGHT; z++)
		{
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			data->trace_data->buffer[z][x] = data->map_data->C_color;
		}
		count ++;
	}
	for(int x = 0; x < 4; x++)
		free(texture[x]);
	draw_buffer(data->trace_data);
	for(int y = 0; y < SCREEN_HEIGHT; y++) for(int x = 0; x < SCREEN_WIDTH; x++) data->trace_data->buffer[y][x] = 0;
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->mlx_data->img->img, 0, 0);
	return (0);
}