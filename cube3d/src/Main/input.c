#include "cube3d.h"

int input(int key, t_data *data)
{
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