/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:46 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/09 14:32:48 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_img	*init_img(void *mlx, char *texture, int trigger)
{
	t_img	*data;
	int		h;
	int		w;

	w = TEX_WIDTH;
	h = TEX_HEIGHT;
	data = malloc(sizeof(t_img));
	if (trigger == 0)
		data->img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	else
		data->img = mlx_xpm_file_to_image(mlx, texture, &w, &h);
	if (!data->img)
	{
		free (data);
		return (NULL);
	}
	if (data->img)
		data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian);
	return (data);
}

int	init_mlx_data(t_mlx_data *data, char *texture[37])
{
	int	x;

	x = 0;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "boxeo");
	while (x < 4)
	{
		data->texture[x] = init_img(data->mlx, texture[x], 1);
		x++;
	}

	// Charger les 12 nouvelles textures supplémentaires (ciel, sol, portes, ennemis, collectibles, etc.)
    data->texture[x++] = init_img(data->mlx, TEX_ENEMY, 1);
    data->texture[x++] = init_img(data->mlx, TEX_COLLECTIBLE, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_CLOSED, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_CHEVRON1, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_CHEVRON2, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_CHEVRON3, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_CHEVRON4, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_CHEVRON5, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_CHEVRON6, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_CHEVRON7, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING1, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING2, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING3, 1);
	data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING4, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING5, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING6, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING7, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING8, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING9, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING10, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING11, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING12, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING13, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING14, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING15, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPENING16, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN1, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN2, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN3, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN4, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN5, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN6, 1);
    data->texture[x++] = init_img(data->mlx, TEX_DOOR_OPEN7, 1);
    
	
	data->img = init_img(data->mlx, "", 0);
    // Vérifier si toutes les textures ont été chargées
	x = 0;
    while (x < 37)
    {
        if (!data->texture[x])
        {
            printf("Error loading texture at index %d\n", x);
			//free_tab_text_error(data->texture, x);
            return (1);
        }
        x++;
    }
	
	return (0);
}

void	init_map_data(t_data *data, char **argv)
{
	data->map_data->pos_x = 0.0;
	data->map_data->pos_y = 0.0;
	data->map_data->texture_txt[0] = NULL;
	data->map_data->texture_txt[1] = NULL;
	data->map_data->texture_txt[2] = NULL;
	data->map_data->texture_txt[3] = NULL;
	/*data->map_data->texture_txt[4] = NULL;
	data->map_data->texture_txt[5] = NULL;
	data->map_data->texture_txt[6] = NULL;
	data->map_data->texture_txt[7] = NULL;
	data->map_data->texture_txt[8] = NULL;
	data->map_data->texture_txt[9] = NULL;
	data->map_data->texture_txt[10] = NULL;
	data->map_data->texture_txt[11] = NULL;
	data->map_data->texture_txt[12] = NULL;
	data->map_data->texture_txt[13] = NULL;
	data->map_data->texture_txt[14] = NULL;
	data->map_data->texture_txt[15] = NULL;*/
	data->map_data->f = NULL;
	data->map_data->c = NULL;
	data->map_data->map = NULL;
	data->map_data->num_doors = 0;
	data->map_data->num_ennemies = 0;
	data->map_data->num_collectibles = 0;
	data->map_data->num_exit = 0;
	data->map_data->exit_is_open = 0;
	parse_map(data, argv[1]);
}

void	init_trace_data(t_map_data *map_data,
		t_trace_data *data, t_mlx_data *mlx_data)
{
	data->camerax = 0;
	data->raydirx = 0;
	data->raydiry = 0;
	data->mapx = (int)map_data->pos_x;
	data->mapy = (int)map_data->pos_y;
	data->deltadistx = 0;
	data->deltadisty = 0;
	data->perpwalldist = 0;
	data->stepx = 0;
	data->stepy = 0;
	data->hit = 0;
	data->side = 0;
	data->lineheight = 0;
	data->drawstart = 0;
	data->drawend = 0;
	data->olddirx = 0;
	data->oldplanex = 0;
	data->movespeed = 0.09;
	data->rotspeed = 0.05;
	data->map_data = map_data;
	data->mlx_data = mlx_data;
	data->h = 0;
	data->w = 0;
	data->texx = 0;
	data->color = 0;
	data->texy = 0;
	data->texpos = 0;
	data->prev_mouse_x = SCREEN_WIDTH / 2;
    data->mouse_initialized = 0;
	//  |  Initialisation of the direction the player is facing   |
	//	V														  V
	if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'W')
	{
		data->dirx = 0;
		data->diry = -1;
		data->planex = -0.55;
		data->planey = 0;
	}
	else if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'E')
	{
		data->dirx = 0;
		data->diry = 1;
		data->planex = 0.55;
		data->planey = 0;
	}
	else if (map_data->map[(int)map_data->pos_x][(int)map_data->pos_y] == 'N')
	{
		data->dirx = -1;
		data->diry = 0;
		data->planex = 0;
		data->planey = 0.55;
	}
	else
	{
		data->dirx = 1;
		data->diry = 0;
		data->planex = 0;
		data->planey = -0.55;
	}
}

void	init_bonus_data(t_data *data)
{
	data->bonus_data->num_doors = data->map_data->num_doors;
	data->bonus_data->num_cinematic1 = 173;
	data->bonus_data->cinematic_w = 1920;
	data->bonus_data->cinematic_h = 1080;
	data->bonus_data->cinematic = NULL;
}

void init_collectibles(t_map_data *map_data, t_bonus_data *bonus_data)
{
    int collectible_index;
    int y;
	
	collectible_index = 0;
    bonus_data->num_collectibles = map_data->num_collectibles;
    bonus_data->collectibles = (t_collectible *)malloc(sizeof(t_collectible) * bonus_data->num_collectibles);

	y = 0;
    while (map_data->map[y])
    {
        int x = 0;
        while (map_data->map[y][x])
        {
            if (map_data->map[y][x] == 'C') // 'C' représente un collectible sur la carte
            {
                bonus_data->collectibles[collectible_index].c_x = (double)x;
                bonus_data->collectibles[collectible_index].c_y = (double)y;
                bonus_data->collectibles[collectible_index].is_collected = 0; // Pas encore ramassé
                collectible_index++;
            }
            x++;
        }
        y++;
    }

    // Initialiser le compteur de collectibles ramassés à 0
    bonus_data->collected_count = 0;
}

void init_enemies(t_map_data *map_data, t_bonus_data *bonus_data)
{
    int enemy_index;
    int y;
    // Allocation du tableau d'ennemis
    bonus_data->num_enemies = map_data->num_ennemies;
    bonus_data->enemies = (t_enemy *)malloc(sizeof(t_enemy) * bonus_data->num_enemies);

	enemy_index = 0;
    y = 0;
    while (map_data->map[y])
    {
        int x = 0;
        while (map_data->map[y][x])
        {
            if (map_data->map[y][x] == 'Z') // 'Z' représente un ennemi sur la carte
            {
                bonus_data->enemies[enemy_index].pos_x = (double)x;
                bonus_data->enemies[enemy_index].pos_y = (double)y;
                bonus_data->enemies[enemy_index].hp = 100; // Exemple : 100 points de vie
                bonus_data->enemies[enemy_index].is_alive = 1;
                bonus_data->enemies[enemy_index].is_moving = 0;
                bonus_data->enemies[enemy_index].speed = 0.05; // Exemple de vitesse
                enemy_index++;
            }
            x++;
        }
        y++;
    }
}

void init_doors(t_map_data *map_data, t_bonus_data *bonus_data)
{
    int y;

    y = 0;
    while (map_data->map[y])
    {
        int x = 0;
        while (map_data->map[y][x])
        {
            if (map_data->map[y][x] == 'D') // 'D' représente une porte sur la carte
            {
                bonus_data->door.x = x;
                bonus_data->door.y = y;
                bonus_data->door.is_open = 0; // Initialement fermée
				bonus_data->door.last_time_texture = 0;
				bonus_data->door.time_to_change = 0;
				bonus_data->door.texture_id = 6;
				bonus_data->door.flag_incr_decr = 0;
               // bonus_data->door.slide_pos = 0.0; // Position de glissement initiale
               // bonus_data->door.is_sliding = 0; // Pas en train de coulisser
				break ;
            }
            x++;
        }
        y++;
    }
}



void init_projectiles(t_bonus_data *bonus_data)
{
	int i; 
    int num_projectiles; // Exemple : 10 projectiles disponibles

	num_projectiles = 10; // Exemple : 10 projectiles disponibles
	i = 0;
    bonus_data->num_projectiles = num_projectiles;
    bonus_data->projectiles = (t_projectile *)malloc(sizeof(t_projectile) * num_projectiles);

    while (i < num_projectiles)
    {
        bonus_data->projectiles[i].pos_x = 0;
        bonus_data->projectiles[i].pos_y = 0;
        bonus_data->projectiles[i].dir_x = 0;
        bonus_data->projectiles[i].dir_y = 0;
        bonus_data->projectiles[i].is_active = 0;
        bonus_data->projectiles[i].speed = 0.1; // Exemple de vitesse
		i++;
    }
}

void	init_data(t_data *data, char **argv)
{
	data->map_data = (t_map_data *)malloc(sizeof(t_map_data));
	data->trace_data = (t_trace_data *)malloc(sizeof(t_trace_data));
	data->mlx_data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	data->bonus_data = (t_bonus_data *)malloc(sizeof(t_bonus_data));
	init_map_data(data, argv);//initalize the structure containing all the map information
	
	//------------------------------
	data->mlx_data->mlx = NULL;
	//------------------------------
	// Allocation et initialisation des portes, ennemis, collectibles
	init_doors(data->map_data, data->bonus_data);
    init_enemies(data->map_data, data->bonus_data);
    init_collectibles(data->map_data, data->bonus_data);
 	// Initialisation des projectiles
    // Initialisation de l'environnement (ciel et sol)
	init_bonus_data(data);
	check_error(data, *data->map_data);//check if the .cub file is correct
	//------------------------------
	//check_error(data, *data->map_data);//check if the .cub file is correct
	init_trace_data(data->map_data, data->trace_data, data->mlx_data);
	if (init_mlx_data(data->mlx_data, data->map_data->texture_txt) == 1)
		exit_manager(data);
	calculate_map_size(data);
}
