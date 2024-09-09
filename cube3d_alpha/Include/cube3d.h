/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:41:24 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/09 15:55:21 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H

# define CUBE3D_H
//			   _______			  //
//------------/Include\----------//
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h> // Pour gettimeofday
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
# define SCREEN_HEIGHT 980

# define SCREEN_WIDTH 1820

//size of each texture
# define TEX_HEIGHT	256

# define TEX_WIDTH	256

# define PI 3.14159265358979323846

# define BUFFER_SIZE 42

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
// Title Pictures (in table cinematic1) #0 -> #4
# define TITLE1				"./texture/title_screen/title_screen.xpm"
# define TITLE2				"./texture/title_screen/title_text.xpm"
# define TITLE3				"./texture/title_screen/title_commands.xpm"
# define TITLE4				"./texture/title_screen/victory.xpm"
# define TITLE5				"./texture/title_screen/game_over.xpm"
// Loading Bar Pictures (in table cinematic1) #5 -> #13
# define LOADING1			"./texture/title_screen/loading1.xpm"
# define LOADING2			"./texture/title_screen/loading2.xpm"
# define LOADING3			"./texture/title_screen/loading3.xpm"
# define LOADING4			"./texture/title_screen/loading4.xpm"
# define LOADING5			"./texture/title_screen/loading5.xpm"
# define LOADING6			"./texture/title_screen/loading6.xpm"
# define LOADING7			"./texture/title_screen/loading7.xpm"
# define LOADING8			"./texture/title_screen/loading8.xpm"
# define LOADING9			"./texture/title_screen/loading9.xpm"

//			   __________			 //
//------------/Structures\----------//

typedef struct s_map_data
{
	double	pos_x;
	double	pos_y;
	char	*texture_txt[37];//all the texture paths stored in order
	char	*f;
	char	*c;
	char	**map;
	int		f_color;//final floor color
	int		c_color;//final ceailing color
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
	t_img	*texture[37];// all the texture stored in an array
	int		texture_count;// Total number of textures in the array
}	t_mlx_data;

typedef struct s_trace_data
{
	double			dirx;//direction of the player, meaning where is the player looking
	double			diry;//direction of the player
	double			planex;//camera plane of the player, meaning how much do the player see
	double			planey;//camera plane of the player
	double			sidedistx;//the distance the ray has to travel form our current position to the fist x side (vertical side)
	double			sidedisty;//the distance the ray has to travel form our current position to the fist y side (horizontal side)
	double			camerax;//x coordinate in camera space, meaning the x position in the camera plane
	double			raydirx;//current x coordinates + the position inside the square we're in
	double			raydiry;//current y coordinates + the position inside the square we're in
	double			movespeed;
	double			rotspeed;
	double			olddirx;//used to rotate the y direction vector  
	double			oldplanex;//used to rotate the y plane vector  
	double			deltadistx;//distance the ray has to travel to go form our x side position to the next x side (meaning the side of the square in front of our position), calculated using Pythagoras formula A^2 + B^2 = C^2
	double			deltadisty;//distance the ray has to travel to go form our y side position to the next y side (meaning the side of the square in front of our position)
	double			perpwalldist;//length of the ray (which extend until it hit a wall)
	double			wallx;//the exact value of where the wall was hit
	double			step;//how much to increase the textiure coordinate per pixels
	double			texpos;//starting texture coordinates
	int				color;//color of the pixel
	int				mapx;//current x coordinates
	int				mapy;//current y coordinates
	int				stepx;//what x direction to step in : in front of (+1) or behind (-1)
	int				stepy;//what y direction to step in : in front of (+1) or behind (-1)
	int				hit;//is there a wall hit ?
	int				side;//was it a west side (like Tupac lmao) or East side wall hit 
	int				lineheight;//height of the line to draw on the screen
	int				drawstart;//where the wall drawing start
	int				drawend;//where the wall drawing end
	int				h;//useless variable, might replace or delete later
	int				w;//useless variable, might replace or delete later
	int				texy;//x coordinate of the texture
	int				texx;//y coordinate of the texture
	int				prev_mouse_x;
	int				mouse_initialized;
	unsigned int	buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	//unsigned int	**buffer;
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
	int				texture_id;
	int				flag_incr_decr;
}	t_door;

typedef struct s_enemy
{
	double			pos_x;
	double			pos_y;
	int				hp;// Health points
	int				is_alive;// Is the enemy still alive?
	int				is_moving;// Is the enemy currently moving?
	double			speed;// Speed of the enemy
}	t_enemy;

typedef struct s_projectile
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	int				is_active;// Is the projectile currently active?
	double			speed;// Speed of the projectile
}	t_projectile;

typedef struct s_collectible
{
	double			c_x;
	double			c_y;
	int				is_collected;// 0 if not collected, 1 if collected
}	t_collectible;

typedef struct s_minimap
{
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;
	int	b2;
	int	r;
	int	g;
	int	b;
}	t_minimap;

typedef struct s_bonus_data
{
	//---------/ Minimap Part \-----------//
	t_minimap		*minimap;
	//---------/ Door Part \-----------//
	int				num_doors;
	t_door			door;// Array of doors
	//---------/ Enemy Part \-----------//
	int				num_enemies;
	t_enemy			*enemies;// Array of enemies
	//---------/ Projectiles Part \-----------//
	int				num_projectiles;
	t_projectile	*projectiles;// Array of projectiles
	//---------/ Collectibles Part \-----------//
	int				num_collectibles;
	int				collected_count;// Counter for collected items
	t_collectible	*collectibles;// Array of collectibles
	//---------/ Cinematic Part \-----------//
	int				num_cinematic1;
	int				cinematic_w;
	int				cinematic_h;
	char			**cinematic;//Array of textures images
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
//			   _________			//
//------------/Functions\----------//

//				Main
void	init_data(t_data *data, char **argv);
int		ft_render(t_data *data);
int		input(int key, t_data *data);

//				parsing
int		is_printable(char *s);
void	parse_map(t_data *map_data, char *file);

//			get_next_line
char	*get_next_line(int fd);

//				tools
long	ft_atoi(char *nptr);
char	*extract_str(char *str);
char	*ft_substr(char const *s, int start, int len);
int		ft_strncmp(const char *s1, char *s2, size_t n);
int		ft_strlen2(char **tab);

//			render	 tools
double	ft_abs(double nb);
int		get_pixel(t_img *data, int x, int y);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_buffer(t_trace_data *data);

//				gnl_tools
int		ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_strcpy(char *dest, const char *src);

//				debug
void	print_tab(char **tab);
void	print_map_data(t_map_data *map_data);

//			exit_manager
void	free_tab(char **tab);
int		exit_manager(t_data *data);
int		exit_error_message(t_data *data, char *message);

//				Error
int		is_position(char c);
int		check_error(t_data *data, t_map_data map_data);
void	free_tab_text_error(t_img **tab, int i);
int		exit_error_text(t_data *data);

//				Bonuses
void	draw_minimap(t_data *data);
void	calculate_map_size(t_data *data);
void	draw_minimap_player(t_data *data);
int		find_collectible_at(t_bonus_data *bonus_data, int map_x, int map_y);
void	collect_item(t_data *data);
void	open_close_thedoor(t_data *data);
int		find_ennemy_at(t_bonus_data *bonus_data, int map_y, int map_x);
void	ft_check_if_ennemy(t_data *data);
int		is_near_green(int color, int tolerance);
int		render_collec_ennemies(t_data *data, int tex_index2);
void	init_trace_data(t_map_data *map_data,
			t_trace_data *data, t_mlx_data *mlx_data);
int		get_door_texture_animation(t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	cinematic(t_data *data, int num_images, int delay_ms);
void	enter_the_vortex(t_data *data);
void	load_cinematic_images(t_data *data, char *folder_path, int num_images);
void	playsound(char *file, int wait, int stop, int attenued);
void	pkill_paplay(void);
void	*resize_window(t_data *data, int new_width, int new_height);
long	get_elapsed_time_ms(struct timeval start_time);
void	free_cinematic_images(t_data *data, int num_images);

//------------\_________/----------//
#endif
