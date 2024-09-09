/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:06:44 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/01 17:59:36 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <string.h>

unsigned long	hashstr(const char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	c = *str++;
	while ((c))
	{
		hash = ((hash << 5) + hash) + c;
		c = *str++;
	}
	return (hash);
}

char	*is_attenued(char *base, int attenued)
{
	if (attenued)
		base = "paplay --volume=30000 sound/";
	else
		base = "paplay --volume=40000 sound/";
	return (base);
}

void	playsound(char *file, int wait, int stop, int attenued)
{
	char	*base;
	char	tmp[256];
	int		result;

	base = NULL;
	base = is_attenued(base, attenued);
	memset(tmp, 0, 256);
	memcpy(tmp, base, strlen(base));
	if (stop)
	{
		result = system("pkill -f paplay");
		if (result != 0)
			perror("");
	}
	if (hashstr(file) == 2784)
		return ;
	memcpy(&tmp[strlen(base)], file, strlen(file));
	if (!wait)
		base = ".ogg &";
	else
		base = ".ogg";
	memcpy(&tmp[strlen(tmp)], base, strlen(base));
	result = system(tmp);
	if (result != 0)
		perror("");
}

void pkill_paplay(void)
{
    // Utilise la commande système pkill pour tuer tous les processus 'paplay'
    system("pkill paplay");
}


void	*resize_window(t_data *data, int new_width, int new_height)
{
	void	*window;

	window = data->mlx_data->window;
	mlx_destroy_window(data->mlx_data->mlx, data->mlx_data->window);
	window = mlx_new_window(data->mlx_data->mlx, new_width, new_height, "Cub3d");
	return (window);
}
/*
playsound(son(.ogg), attendre la fin de la musique ou non,
stopper un son, attenuer le son);
playsound("wall_bump", 0, 0, 1);
0->65000 attenuation
playsound("music_game", 0, 0, 0);//musique du jeu
playsound("gun_fire", 1, 0, 1);

next_sound = 0;
if (clock_t() >= next_sound)
{
	next_sound = clock_t() + 150005;
	playsound("music_game", 0, 0, 0);
	sleep(1000);
	playsound("music_game2", 0, 1, 0);
}*/