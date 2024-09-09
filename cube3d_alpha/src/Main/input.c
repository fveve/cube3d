/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: john <john@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:27:17 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/06 16:09:49 by john             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	int		diffx;
	double	rotation_speed;

    (void)y; // On ignore le mouvement vertical

    if (!data->trace_data->mouse_initialized)
    {
        data->trace_data->prev_mouse_x = x; // On initialise la position de la souris
        data->trace_data->mouse_initialized = 1;
        return (0);
    }

    diffx = data->trace_data->prev_mouse_x - x;

    if (diffx != 0)
    {
		rotation_speed = data->trace_data->rotSpeed * (diffx / 20.0); // Ajuste la sensibilité

        // Mettre à jour la direction de la caméra (rotation gauche/droite)
        data->trace_data->oldDirX = data->trace_data->dirX;
        data->trace_data->dirX = data->trace_data->dirX
            * cos(rotation_speed) - data->trace_data->dirY
            * sin(rotation_speed);
        data->trace_data->dirY = data->trace_data->oldDirX
            * sin(rotation_speed) + data->trace_data->dirY
            * cos(rotation_speed);

        // Mettre à jour le plan de la caméra (pour le champ de vision)
        data->trace_data->oldPlaneX = data->trace_data->planeX;
        data->trace_data->planeX = data->trace_data->planeX
            * cos(rotation_speed) - data->trace_data->planeY
            * sin(rotation_speed);
        data->trace_data->planeY = data->trace_data->oldPlaneX
            * sin(rotation_speed) + data->trace_data->planeY
            * cos(rotation_speed);
    }

    // Mise à jour de la position précédente de la souris
    data->trace_data->prev_mouse_x = x;

    printf("Mouse moved to: (%d, %d)\n", x, y);
    return (0);
}

int	input(int key, t_data *data)
{
	/*char	nextx;
	char	nexty;

	nextx = data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirX
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y];
	nexty = data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirY
				* data->trace_data->moveSpeed)];*/
	mlx_do_key_autorepeaton(data->mlx_data->mlx);
	if (key == KEY_UP || key == KEY_W)
	{
		/*printf("KEYMOVE pos_x: %f, pos_y: %f\n",data->map_data->pos_x, data->map_data->pos_y);
		printf("KEYMOVE dirX: %f, dirY: %f\n",data->trace_data->dirX, data->trace_data->dirY);
		printf("KEYMOVE moovspeed: %f\n",data->trace_data->moveSpeed);*/
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirX
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] != '1' && 
				(data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirX
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] != 'D'
				|| (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirX
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_x += data->trace_data->dirX
				* data->trace_data->moveSpeed;
		if (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirY
				* data->trace_data->moveSpeed)] != '1'
				&& (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirY
				* data->trace_data->moveSpeed)] != 'D'
				|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirY
				* data->trace_data->moveSpeed)] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_y += data->trace_data->dirY
				*data->trace_data->moveSpeed;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//printf("KEYMOVE pos_x: %f, pos_y: %f\n",data->map_data->pos_x, data->map_data->pos_y);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		collect_item(data);
		ft_check_if_ennemy(data);
		enter_the_vortex(data);
	}
	if (key == KEY_DOWN || key == KEY_S)
	{
		if (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->dirX
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] != '1'
				&& (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->dirX
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] != 'D'
				|| (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->dirX
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_x -= data->trace_data->dirX
				* data->trace_data->moveSpeed;
		if (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->dirY
				* data->trace_data->moveSpeed)] != '1'
				&& (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->dirY
				* data->trace_data->moveSpeed)] != 'D'
				|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->dirY
				* data->trace_data->moveSpeed)] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_y -= data->trace_data->dirY
				* data->trace_data->moveSpeed;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//printf("KEYMOVE pos_x: %f, pos_y: %f\n",data->map_data->pos_x, data->map_data->pos_y);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		collect_item(data);
		ft_check_if_ennemy(data);
	}
	if (key == KEY_A)
	{
		if (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->dirY
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] != '1'
				&& (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->dirY
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] != 'D'
				|| (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->dirY
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_x -= data->trace_data->dirY
				* data->trace_data->moveSpeed;
		if (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirX
				*data->trace_data->moveSpeed)] != '1'
				&& (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirX
				*data->trace_data->moveSpeed)] != 'D'
				|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirX
				*data->trace_data->moveSpeed)] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_y += data->trace_data->dirX
				* data->trace_data->moveSpeed;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//printf("KEYMOVE pos_x: %f, pos_y: %f\n",data->map_data->pos_x, data->map_data->pos_y);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		collect_item(data);
		ft_check_if_ennemy(data);
	}
	if (key == KEY_D)
	{
		if (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirY
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] != '1'
				&& (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirY
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] != 'D'
				|| (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirY
				* data->trace_data->moveSpeed)]
				[(int)data->map_data->pos_y] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_x += data->trace_data->dirY
				* data->trace_data->moveSpeed;
		if (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->dirX
				* data->trace_data->moveSpeed)] != '1'
				&& (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->dirX * data->trace_data->moveSpeed)] != 'D'
				|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->dirX * data->trace_data->moveSpeed)] == 'D'
				&& data->bonus_data->door.is_open == 1 )))
			data->map_data->pos_y -= data->trace_data->dirX
				*data->trace_data->moveSpeed;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//printf("KEYMOVE pos_x: %f, pos_y: %f\n",data->map_data->pos_x, data->map_data->pos_y);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		collect_item(data);
		ft_check_if_ennemy(data);
	}
	if (key == KEY_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		data->trace_data->oldDirX = data->trace_data->dirX;
		data->trace_data->dirX = data->trace_data->dirX
			* cos(-data->trace_data->rotSpeed)
			- data->trace_data->dirY
			* sin(-data->trace_data->rotSpeed);
		data->trace_data->dirY = data->trace_data->oldDirX
			* sin(-data->trace_data->rotSpeed)
			+ data->trace_data->dirY * cos(-data->trace_data->rotSpeed);
		data->trace_data->oldPlaneX = data->trace_data->planeX;
		data->trace_data->planeX = data->trace_data->planeX
			* cos(-data->trace_data->rotSpeed)
			- data->trace_data->planeY * sin(-data->trace_data->rotSpeed);
		data->trace_data->planeY = data->trace_data->oldPlaneX
			* sin(-data->trace_data->rotSpeed)
			+ data->trace_data->planeY * cos(-data->trace_data->rotSpeed);
	}
	//rotate to the left
	if (key == KEY_LEFT)
	{
		//both camera direction and camera plane must be rotated
		data->trace_data->oldDirX = data->trace_data->dirX;
		data->trace_data->dirX = data->trace_data->dirX
			* cos(data->trace_data->rotSpeed) - data->trace_data->dirY
			* sin(data->trace_data->rotSpeed);
		data->trace_data->dirY = data->trace_data->oldDirX
			* sin(data->trace_data->rotSpeed) + data->trace_data->dirY
			* cos(data->trace_data->rotSpeed);
		data->trace_data->oldPlaneX = data->trace_data->planeX;
		data->trace_data->planeX = data->trace_data->planeX
			* cos(data->trace_data->rotSpeed) - data->trace_data->planeY
			* sin(data->trace_data->rotSpeed);
		data->trace_data->planeY = data->trace_data->oldPlaneX
			* sin(data->trace_data->rotSpeed) + data->trace_data->planeY
			* cos(data->trace_data->rotSpeed);
	}
	if (key == KEY_ESCAPE)
		exit_manager(data);
	if (key == 32)
		open_close_thedoor(data);
	return (0);
}

/*int	input(int key, t_data *data)
{
	mlx_do_key_autorepeaton(data->mlx_data->mlx);

	// Avancer
	if (key == KEY_UP || key == KEY_W)
	{
		// Mise à jour de pos_y avec dirY (verticalement)
		if (data->map_data->map[(int)data->map_data->pos_y
			+ (int)(data->trace_data->dirY * data->trace_data->moveSpeed)]
			[(int)data->map_data->pos_x] != '1')
		{
			data->map_data->pos_y += data->trace_data->dirY * data->trace_data->moveSpeed;
		}
		
		// Mise à jour de pos_x avec dirX (horizontalement)
		if (data->map_data->map[(int)data->map_data->pos_y]
			[(int)(data->map_data->pos_x + data->trace_data->dirX * data->trace_data->moveSpeed)] != '1')
		{
			data->map_data->pos_x += data->trace_data->dirX * data->trace_data->moveSpeed;
		}

		printf("KEYMOVE pos_x: %f, pos_y: %f\n", data->map_data->pos_x, data->map_data->pos_y);
	}

	// Reculer
	if (key == KEY_DOWN || key == KEY_S)
	{
		// Mise à jour de pos_y avec dirY (recul)
		if (data->map_data->map[(int)(data->map_data->pos_y - data->trace_data->dirY * data->trace_data->moveSpeed)]
			[(int)data->map_data->pos_x] != '1')
		{
			data->map_data->pos_y -= data->trace_data->dirY * data->trace_data->moveSpeed;
		}

		// Mise à jour de pos_x avec dirX (recul)
		if (data->map_data->map[(int)data->map_data->pos_y]
			[(int)(data->map_data->pos_x - data->trace_data->dirX * data->trace_data->moveSpeed)] != '1')
		{
			data->map_data->pos_x -= data->trace_data->dirX * data->trace_data->moveSpeed;
		}

		printf("KEYMOVE pos_x: %f, pos_y: %f\n", data->map_data->pos_x, data->map_data->pos_y);
	}

	// Déplacement à gauche
	if (key == KEY_A)
	{
		// Mise à jour de pos_x avec dirY (perpendiculairement)
		if (data->map_data->map[(int)data->map_data->pos_y]
			[(int)(data->map_data->pos_x - data->trace_data->dirY * data->trace_data->moveSpeed)] != '1')
		{
			data->map_data->pos_x -= data->trace_data->dirY * data->trace_data->moveSpeed;
		}

		// Mise à jour de pos_y avec dirX (perpendiculairement)
		if (data->map_data->map[(int)(data->map_data->pos_y + data->trace_data->dirX * data->trace_data->moveSpeed)]
			[(int)data->map_data->pos_x] != '1')
		{
			data->map_data->pos_y += data->trace_data->dirX * data->trace_data->moveSpeed;
		}

		printf("KEYMOVE pos_x: %f, pos_y: %f\n", data->map_data->pos_x, data->map_data->pos_y);
	}

	// Déplacement à droite
	if (key == KEY_D)
	{
		// Mise à jour de pos_x avec dirY (perpendiculairement)
		if (data->map_data->map[(int)data->map_data->pos_y]
			[(int)(data->map_data->pos_x + data->trace_data->dirY * data->trace_data->moveSpeed)] != '1')
		{
			data->map_data->pos_x += data->trace_data->dirY * data->trace_data->moveSpeed;
		}

		// Mise à jour de pos_y avec dirX (perpendiculairement)
		if (data->map_data->map[(int)(data->map_data->pos_y - data->trace_data->dirX * data->trace_data->moveSpeed)]
			[(int)data->map_data->pos_x] != '1')
		{
			data->map_data->pos_y -= data->trace_data->dirX * data->trace_data->moveSpeed;
		}

		printf("KEYMOVE pos_x: %f, pos_y: %f\n", data->map_data->pos_x, data->map_data->pos_y);
	}

	// Rotation à droite
	if (key == KEY_RIGHT)
	{
		data->trace_data->oldDirX = data->trace_data->dirX;
		data->trace_data->dirX = data->trace_data->dirX * cos(-data->trace_data->rotSpeed)
			- data->trace_data->dirY * sin(-data->trace_data->rotSpeed);
		data->trace_data->dirY = data->trace_data->oldDirX * sin(-data->trace_data->rotSpeed)
			+ data->trace_data->dirY * cos(-data->trace_data->rotSpeed);

		data->trace_data->oldPlaneX = data->trace_data->planeX;
		data->trace_data->planeX = data->trace_data->planeX * cos(-data->trace_data->rotSpeed)
			- data->trace_data->planeY * sin(-data->trace_data->rotSpeed);
		data->trace_data->planeY = data->trace_data->oldPlaneX * sin(-data->trace_data->rotSpeed)
			+ data->trace_data->planeY * cos(-data->trace_data->rotSpeed);
	}

	// Rotation à gauche
	if (key == KEY_LEFT)
	{
		data->trace_data->oldDirX = data->trace_data->dirX;
		data->trace_data->dirX = data->trace_data->dirX * cos(data->trace_data->rotSpeed)
			- data->trace_data->dirY * sin(data->trace_data->rotSpeed);
		data->trace_data->dirY = data->trace_data->oldDirX * sin(data->trace_data->rotSpeed)
			+ data->trace_data->dirY * cos(data->trace_data->rotSpeed);

		data->trace_data->oldPlaneX = data->trace_data->planeX;
		data->trace_data->planeX = data->trace_data->planeX * cos(data->trace_data->rotSpeed)
			- data->trace_data->planeY * sin(data->trace_data->rotSpeed);
		data->trace_data->planeY = data->trace_data->oldPlaneX * sin(data->trace_data->rotSpeed)
			+ data->trace_data->planeY * cos(data->trace_data->rotSpeed);
	}

	if (key == KEY_ESCAPE)
		exit_manager(data);

	return (0);
}*/


