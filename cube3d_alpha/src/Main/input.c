/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:27:17 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/09 14:56:55 by joncurci         ###   ########.fr       */
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
		rotation_speed = data->trace_data->rotspeed * (diffx / 20.0); // Ajuste la sensibilité

        // Mettre à jour la direction de la caméra (rotation gauche/droite)
        data->trace_data->olddirx = data->trace_data->dirx;
        data->trace_data->dirx = data->trace_data->dirx
            * cos(rotation_speed) - data->trace_data->diry
            * sin(rotation_speed);
        data->trace_data->diry = data->trace_data->olddirx
            * sin(rotation_speed) + data->trace_data->diry
            * cos(rotation_speed);

        // Mettre à jour le plan de la caméra (pour le champ de vision)
        data->trace_data->oldplanex = data->trace_data->planex;
        data->trace_data->planex = data->trace_data->planex
            * cos(rotation_speed) - data->trace_data->planey
            * sin(rotation_speed);
        data->trace_data->planey = data->trace_data->oldplanex
            * sin(rotation_speed) + data->trace_data->planey
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
				+ data->trace_data->dirx
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y];
	nexty = data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->diry
				* data->trace_data->movespeed)];*/
	mlx_do_key_autorepeaton(data->mlx_data->mlx);
	if (key == KEY_UP || key == KEY_W)
	{
		/*printf("KEYMOVE pos_x: %f, pos_y: %f\n",data->map_data->pos_x, data->map_data->pos_y);
		printf("KEYMOVE dirx: %f, diry: %f\n",data->trace_data->dirx, data->trace_data->diry);
		printf("KEYMOVE moovspeed: %f\n",data->trace_data->movespeed);*/
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirx
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] != '1' && 
				(data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirx
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] != 'D'
				|| (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->dirx
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_x += data->trace_data->dirx
				* data->trace_data->movespeed;
		if (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->diry
				* data->trace_data->movespeed)] != '1'
				&& (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->diry
				* data->trace_data->movespeed)] != 'D'
				|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->diry
				* data->trace_data->movespeed)] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_y += data->trace_data->diry
				*data->trace_data->movespeed;
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
				- data->trace_data->dirx
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] != '1'
				&& (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->dirx
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] != 'D'
				|| (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->dirx
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_x -= data->trace_data->dirx
				* data->trace_data->movespeed;
		if (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->diry
				* data->trace_data->movespeed)] != '1'
				&& (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->diry
				* data->trace_data->movespeed)] != 'D'
				|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->diry
				* data->trace_data->movespeed)] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_y -= data->trace_data->diry
				* data->trace_data->movespeed;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//printf("KEYMOVE pos_x: %f, pos_y: %f\n",data->map_data->pos_x, data->map_data->pos_y);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		collect_item(data);
		ft_check_if_ennemy(data);
	}
	if (key == KEY_A)
	{
		if (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->diry
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] != '1'
				&& (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->diry
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] != 'D'
				|| (data->map_data->map[(int)(data->map_data->pos_x
				- data->trace_data->diry
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_x -= data->trace_data->diry
				* data->trace_data->movespeed;
		if (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirx
				*data->trace_data->movespeed)] != '1'
				&& (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirx
				*data->trace_data->movespeed)] != 'D'
				|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				+ data->trace_data->dirx
				*data->trace_data->movespeed)] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_y += data->trace_data->dirx
				* data->trace_data->movespeed;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//printf("KEYMOVE pos_x: %f, pos_y: %f\n",data->map_data->pos_x, data->map_data->pos_y);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		collect_item(data);
		ft_check_if_ennemy(data);
	}
	if (key == KEY_D)
	{
		if (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->diry
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] != '1'
				&& (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->diry
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] != 'D'
				|| (data->map_data->map[(int)(data->map_data->pos_x
				+ data->trace_data->diry
				* data->trace_data->movespeed)]
				[(int)data->map_data->pos_y] == 'D'
				&& data->bonus_data->door.is_open == 1)))
			data->map_data->pos_x += data->trace_data->diry
				* data->trace_data->movespeed;
		if (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->dirx
				* data->trace_data->movespeed)] != '1'
				&& (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->dirx * data->trace_data->movespeed)] != 'D'
				|| (data->map_data->map[(int)data->map_data->pos_x]
			[(int)(data->map_data->pos_y
				- data->trace_data->dirx * data->trace_data->movespeed)] == 'D'
				&& data->bonus_data->door.is_open == 1 )))
			data->map_data->pos_y -= data->trace_data->dirx
				*data->trace_data->movespeed;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//printf("KEYMOVE pos_x: %f, pos_y: %f\n",data->map_data->pos_x, data->map_data->pos_y);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		collect_item(data);
		ft_check_if_ennemy(data);
	}
	if (key == KEY_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		data->trace_data->olddirx = data->trace_data->dirx;
		data->trace_data->dirx = data->trace_data->dirx
			* cos(-data->trace_data->rotspeed)
			- data->trace_data->diry
			* sin(-data->trace_data->rotspeed);
		data->trace_data->diry = data->trace_data->olddirx
			* sin(-data->trace_data->rotspeed)
			+ data->trace_data->diry * cos(-data->trace_data->rotspeed);
		data->trace_data->oldplanex = data->trace_data->planex;
		data->trace_data->planex = data->trace_data->planex
			* cos(-data->trace_data->rotspeed)
			- data->trace_data->planey * sin(-data->trace_data->rotspeed);
		data->trace_data->planey = data->trace_data->oldplanex
			* sin(-data->trace_data->rotspeed)
			+ data->trace_data->planey * cos(-data->trace_data->rotspeed);
	}
	//rotate to the left
	if (key == KEY_LEFT)
	{
		//both camera direction and camera plane must be rotated
		data->trace_data->olddirx = data->trace_data->dirx;
		data->trace_data->dirx = data->trace_data->dirx
			* cos(data->trace_data->rotspeed) - data->trace_data->diry
			* sin(data->trace_data->rotspeed);
		data->trace_data->diry = data->trace_data->olddirx
			* sin(data->trace_data->rotspeed) + data->trace_data->diry
			* cos(data->trace_data->rotspeed);
		data->trace_data->oldplanex = data->trace_data->planex;
		data->trace_data->planex = data->trace_data->planex
			* cos(data->trace_data->rotspeed) - data->trace_data->planey
			* sin(data->trace_data->rotspeed);
		data->trace_data->planey = data->trace_data->oldplanex
			* sin(data->trace_data->rotspeed) + data->trace_data->planey
			* cos(data->trace_data->rotspeed);
	}
	if (key == KEY_ESCAPE)
		exit_manager(data);
	if (key == 32)
		open_close_thedoor(data);
	return (0);
}
