/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:13:53 by joncurci          #+#    #+#             */
/*   Updated: 2024/08/28 22:40:59 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H

# define CUBE3D_H
//			   _______			  //
//------------/Include\----------//
# include	<mlx.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<stdio.h>
# include	<math.h>
# include	<sys/time.h> // Pour gettimeofday
//------------\_______/----------//

# define RGB_RED "\e[0;31m"

# define RGB_BLUE	"\e[0;34m"

# define KEY_RIGHT 65363

# define KEY_LEFT 65361

# define KEY_UP 65362

# define KEY_DOWN 65364

# define KEY_W 119

# define KEY_S 115

# define KEY_D 100

# define KEY_A 97

# define KEY_ESCAPE 65307

//size of the screen

# define SCREEN_HEIGHT 1300

# define SCREEN_WIDTH 1300

//size of each texture
# define TEX_HEIGHT	256

# define TEX_WIDTH	256

# define PI 3.14159265358979323846


// Textures #0 -> #3 ==> Les 4 textures de murs
// Enemy textures #4
# define TEX_ENEMY				"./texture/guard_256.xpm"
// Collectible texture #5
# define TEX_COLLECTIBLE		"./texture/tablet3_256.xpm"
// Door Closed textures #6 
# define TEX_DOOR_CLOSED		"./texture/door_opening/door_closed1_256.xpm"
// Door Chevrons textures #7 -> #13
# define TEX_DOOR_CHEVRON1		"./texture/door_opening/door_chevron1_256.xpm"
# define TEX_DOOR_CHEVRON2		"./texture/door_opening/door_chevron2_256.xpm"
# define TEX_DOOR_CHEVRON3		"./texture/door_opening/door_chevron3_256.xpm"
# define TEX_DOOR_CHEVRON4		"./texture/door_opening/door_chevron4_256.xpm"
# define TEX_DOOR_CHEVRON5		"./texture/door_opening/door_chevron5_256.xpm"
# define TEX_DOOR_CHEVRON6		"./texture/door_opening/door_chevron6_256.xpm"
# define TEX_DOOR_CHEVRON7		"./texture/door_opening/door_chevron7_256.xpm"
// Door Opening #14 -> #29
# define TEX_DOOR_OPENING1		"./texture/door_opening/door_opening1_256.xpm"
# define TEX_DOOR_OPENING2		"./texture/door_opening/door_opening2_256.xpm"
# define TEX_DOOR_OPENING3		"./texture/door_opening/door_opening3_256.xpm"
# define TEX_DOOR_OPENING4		"./texture/door_opening/door_opening4_256.xpm"
# define TEX_DOOR_OPENING5		"./texture/door_opening/door_opening5_256.xpm"
# define TEX_DOOR_OPENING6		"./texture/door_opening/door_opening6_256.xpm"
# define TEX_DOOR_OPENING7		"./texture/door_opening/door_opening7_256.xpm"
# define TEX_DOOR_OPENING8		"./texture/door_opening/door_opening8_256.xpm"
# define TEX_DOOR_OPENING9		"./texture/door_opening/door_opening9_256.xpm"
# define TEX_DOOR_OPENING10		"./texture/door_opening/door_opening10_256.xpm"
# define TEX_DOOR_OPENING11		"./texture/door_opening/door_opening11_256.xpm"
# define TEX_DOOR_OPENING12		"./texture/door_opening/door_opening12_256.xpm"
# define TEX_DOOR_OPENING13		"./texture/door_opening/door_opening13_256.xpm"
# define TEX_DOOR_OPENING14		"./texture/door_opening/door_opening14_256.xpm"
# define TEX_DOOR_OPENING15		"./texture/door_opening/door_opening15_256.xpm"
# define TEX_DOOR_OPENING16		"./texture/door_opening/door_opening16_256.xpm"
// Door Open #30 -> 36
# define TEX_DOOR_OPEN1			"./texture/door_opening/door_open1_256.xpm"
# define TEX_DOOR_OPEN2			"./texture/door_opening/door_open2_256.xpm"
# define TEX_DOOR_OPEN3			"./texture/door_opening/door_open3_256.xpm"
# define TEX_DOOR_OPEN4			"./texture/door_opening/door_open4_256.xpm"
# define TEX_DOOR_OPEN5			"./texture/door_opening/door_open5_256.xpm"
# define TEX_DOOR_OPEN6			"./texture/door_opening/door_open6_256.xpm"
# define TEX_DOOR_OPEN7			"./texture/door_opening/door_open7_256.xpm"
// Door textures #37 -> #39
# define TEX_TITLE1				"./texture/ciel3_256.xpm"
# define TEX_TITLE2				"./texture/ciel3_256.xpm"
# define TEX_TITLE3				"./texture/ciel3_256.xpm"




//			   __________		     //
//------------/Structures\----------//

typedef struct s_map_data
{
	double	pos_x;
	double	pos_y;

	char	*texture_txt[40];//all the texture paths stored in order
	char	*F;
	char	*C;
	char	**map;

	int		F_color;//final floor color
	int		C_color;//final ceailing color

	int		num_collectibles;
	int		num_ennemies;
	int		num_doors;
	int		num_exit;
	int		exit_is_open;
}	t_map_data;

typedef struct s_img
{
	void	*img;

	int		bits_per_pixel;
	int		line_length;
	int		endian;

	char	*addr;
}	t_img;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*window;
	t_img	*img;//current frame which is  redrawn each time
	char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
	t_img	*texture[40];// all the texture stored in an array
	int		texture_count;  // Total number of textures in the array
}	t_mlx_data;

typedef struct s_trace_data
{
	double			dirX;//direction of the player, meaning where is the player looking
	double			dirY;//direction of the player
	double			planeX;//camera plane of the player, meaning how much do the player see
	double			planeY;//camera plane of the player
	double			sideDistX;//the distance the ray has to travel form our current position to the fist x side (vertical side)
	double			sideDistY;//the distance the ray has to travel form our current position to the fist y side (horizontal side)
	double			cameraX;//x coordinate in camera space, meaning the x position in the camera plane
	double			rayDirX;//current x coordinates + the position inside the square we're in
	double			rayDirY;//current y coordinates + the position inside the square we're in
	double			moveSpeed;
	double			rotSpeed;
	double			oldDirX;//used to rotate the y direction vector  
	double			oldPlaneX;//used to rotate the y plane vector  
	double			deltaDistX;//distance the ray has to travel to go form our x side position to the next x side (meaning the side of the square in front of our position), calculated using Pythagoras formula A^2 + B^2 = C^2
	double			deltaDistY;//distance the ray has to travel to go form our y side position to the next y side (meaning the side of the square in front of our position)
	double			perpWallDist;//length of the ray (which extend until it hit a wall)
	double			WallX;//the exact value of where the wall was hit
	double			step;//how much to increase the textiure coordinate per pixels
	double			texPos;//starting texture coordinates
	int				color;//color of the pixel
	int				mapX;//current x coordinates
	int				mapY;//current y coordinates
	int				stepX;//what x direction to step in : in front of (+1) or behind (-1)
	int				stepY;//what y direction to step in : in front of (+1) or behind (-1)
	int				hit;//is there a wall hit ?
	int				side;//was it a west side (like Tupac lmao) or East side wall hit 
	int				lineHeight;//height of the line to draw on the screen
	int				drawStart;//where the wall drawing start
	int				drawEnd;//where the wall drawing end
	int				h;//useless variable, might replace or delete later
	int				w;//useless variable, might replace or delete later
	int				texY;//x coordinate of the texture
	int				texX;//y coordinate of the texture
	unsigned int	buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	t_map_data		*map_data;
	t_mlx_data		*mlx_data;
}	t_trace_data;

//!!!!!!!!!!!!!!!!!!!!!
typedef struct s_door
{
    int				x;
    int				y;
    int				is_open;
	double			last_time_texture;
	double			time_to_change;
	int             texture_id;
	int				flag_incr_decr;
 //   double			open_time;  // Temps d'ouverture pour fermer après un certain temps.
//	double			slide_pos;  // Position for sliding (from 0 to 1)
 //   int				is_sliding;    // Is the door currently sliding?
}	t_door;

typedef struct s_enemy
{
    double			pos_x;
    double			pos_y;
    int				hp;              // Health points
    int				is_alive;        // Is the enemy still alive?
    int				is_moving;       // Is the enemy currently moving?
    double			speed;        // Speed of the enemy
}	t_enemy;

typedef struct s_projectile
{
    double			pos_x;
    double			pos_y;
    double			dir_x;
    double			dir_y;
    int				is_active;       // Is the projectile currently active?
    double			speed;        // Speed of the projectile
}	t_projectile;

typedef struct s_collectible
{
    double			c_x;
    double			c_y;
    int				is_collected;  // 0 if not collected, 1 if collected
}	t_collectible;

typedef struct s_bonus_data
{
	//---------/ Minimap Part \-----------//


	//---------/ Door Part \-----------//
    int				num_doors;
    t_door			door;        // Array of doors
    
	//---------/ Enemy Part \-----------//
    int				num_enemies;
    t_enemy			*enemies;    // Array of enemies
    
	//---------/ Projectiles Part \-----------//
    int num_projectiles;
    t_projectile	*projectiles;  // Array of projectiles

	//---------/ Collectibles Part \-----------//
	int				num_collectibles;
    int				collected_count;  // Counter for collected items
    t_collectible	*collectibles; // Array of collectibles
}	t_bonus_data;

//!!!!!!!!!!!!!!!!!!!!!

typedef struct s_data
{
	t_trace_data	*trace_data;
	t_mlx_data		*mlx_data;
	t_map_data		*map_data;
	t_bonus_data	*bonus_data;
}	t_data;

//------------\__________/----------//

//			   _________		    //
//------------/Functions\----------//

//				Main
void	init_data(t_data *data, char **argv);
int		ft_render(t_data *data);
int		input(int key, t_data *data);

//				parsing
int		is_printable(char *s);
void	parse_map(t_map_data *map_data, char *file);

//			get_next_line
char	*get_next_line(int fd, int copy);

//				tools
long	ft_atoi(char *nptr);
char	*extract_str(char *str);
char	*ft_substr(char const *s, int start, int len);
int		ft_strncmp(const char *s1, char *s2, size_t n);
int		ft_strlen2(char **tab);

//			render     tools
double	ft_abs(double nb);
int		get_pixel(t_img *data, int x, int y);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_buffer(t_trace_data *data);

//				gnl_tools
int		ft_strlen(const char *s);
char	*ft_strdup(char *src);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strcpy(char *dest, const char *src);

//				debug
void	print_tab(char **tab);
void	print_map_data(t_map_data *map_data);

//			exit_manager
void	free_tab(char **tab);
int		exit_manager(t_data *data);

//				Error
int		is_position(char c);
int		check_error(t_data *data, t_map_data map_data);

//				Error
void	draw_minimap(t_data *data);
void	calculate_map_size(t_data *data);
void	draw_minimap_player(t_data *data);
int		find_collectible_at(t_bonus_data *bonus_data, int map_x, int map_y);
void	collect_item(t_data *data);
void	open_close_thedoor(t_data *data);
int		find_ennemy_at(t_bonus_data *bonus_data, int map_y, int map_x);
int		is_near_green(int color, int tolerance);
int		render_collec_ennemies(t_data *data, int tex_index2);
void	init_trace_data(t_map_data *map_data,
		t_trace_data *data, t_mlx_data *mlx_data);
int		get_door_texture_animation(t_data *data);

//------------\_________/----------//
#endif